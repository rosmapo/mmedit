#include "MinimapPanel.h"
#include "ScintillaNext.h"
#include <Scintilla.h>

#include <QMouseEvent>
#include <QWheelEvent>
#include <QApplication>
#include <QPainter>
#include <QPaintEvent>

// ── Overlay ──────────────────────────────────────────────────────────────────
class MinimapOverlay : public QWidget
{
public:
    MinimapOverlay(MinimapPanel *p) : QWidget(p), panel(p)
    {
        setAttribute(Qt::WA_TranslucentBackground);
        setMouseTracking(true);
        setCursor(Qt::PointingHandCursor);
    }
protected:
    void paintEvent(QPaintEvent *) override
    {
        QRect vr = panel->viewportRect();
        if (!vr.isValid() || vr.height() < 2) return;
        QPainter p(this);
        p.fillRect(vr, QColor(255, 255, 255, 45));
        p.setPen(QColor(255, 255, 255, 140));
        p.drawLine(0, vr.top(),    width()-1, vr.top());
        p.drawLine(0, vr.bottom(), width()-1, vr.bottom());
    }
    void mousePressEvent(QMouseEvent *e) override
    {
        if (e->button() == Qt::LeftButton) { panel->overlayPress(e->pos()); e->accept(); }
    }
    void mouseMoveEvent(QMouseEvent *e) override
    {
        if (e->buttons() & Qt::LeftButton) { panel->overlayMove(e->pos()); e->accept(); }
    }
    void mouseReleaseEvent(QMouseEvent *e) override { panel->overlayRelease(); e->accept(); }
    void wheelEvent(QWheelEvent *e) override { panel->overlayWheel(e); }
private:
    MinimapPanel *panel;
};

// ── MinimapPanel ──────────────────────────────────────────────────────────────
MinimapPanel::MinimapPanel(QWidget *parent) : QWidget(parent)
{
    setFixedWidth(120);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    map = new ScintillaEdit(this);
    map->setReadOnly(true);
    for (int i = 0; i < 5; ++i) map->setMarginWidthN(i, 0);
    map->setZoom(-10);
    map->setHScrollBar(false);
    map->setVScrollBar(false);
    map->setCaretLineVisible(false);
    map->setCaretPeriod(0);
    map->setMouseDownCaptures(false);
    applyDarkDefault();

    overlay = new MinimapOverlay(this);
}

void MinimapPanel::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    map->setGeometry(rect());
    overlay->setGeometry(rect());
    syncFromEditor();
}

// ── Editor connection ─────────────────────────────────────────────────────────
void MinimapPanel::setEditor(ScintillaNext *editor)
{
    if (mainEditor) { disconnect(mainEditor, nullptr, this, nullptr); mainEditor = nullptr; }
    if (sharedDoc) {
        sptr_t empty = map->createDocument(0, SC_DOCUMENTOPTION_DEFAULT);
        map->setDocPointer(empty);
        map->releaseDocument(sharedDoc);
        sharedDoc = 0;
    }
    if (!editor) { applyDarkDefault(); overlay->update(); return; }

    mainEditor = editor;
    sharedDoc  = editor->docPointer();
    map->addRefDocument(sharedDoc);
    map->setDocPointer(sharedDoc);
    syncStyles();

    connect(editor, &ScintillaNext::closed, this, [this]() {
        sptr_t doc = sharedDoc; mainEditor = nullptr; sharedDoc = 0;
        sptr_t empty = map->createDocument(0, SC_DOCUMENTOPTION_DEFAULT);
        map->setDocPointer(empty);
        if (doc) map->releaseDocument(doc);
        applyDarkDefault(); overlay->update();
    });
    connect(editor, &ScintillaNext::verticalScrolled, this, [this](int) { syncFromEditor(); });
    connect(editor, &ScintillaNext::updateUi, this, [this](Scintilla::Update u) {
        if ((int)u & ((int)Scintilla::Update::VScroll | (int)Scintilla::Update::Content))
            syncFromEditor();
    });
    connect(editor, &ScintillaNext::lexerChanged, this, [this]() { syncStyles(); });
    syncFromEditor();
}

void MinimapPanel::applyDarkDefault()
{
    map->styleSetBack(STYLE_DEFAULT, 0x252525);
    map->styleSetFore(STYLE_DEFAULT, 0x858585);
    map->styleClearAll();
}

void MinimapPanel::syncStyles()
{
    if (!mainEditor) return;
    for (int s = 0; s <= STYLE_DEFAULT; ++s) {
        map->styleSetFore(s, (int)mainEditor->send(SCI_STYLEGETFORE, s, 0));
        map->styleSetBack(s, (int)mainEditor->send(SCI_STYLEGETBACK, s, 0));
    }
    map->colourise(0, -1);
}

void MinimapPanel::syncFromEditor()
{
    if (!mainEditor || syncing) return;
    syncing = true;

    int editorFirst   = (int)mainEditor->firstVisibleLine();
    int editorVisible = (int)mainEditor->linesOnScreen();
    int mapVisible    = (int)map->linesOnScreen();
    int tl            = (int)mainEditor->lineCount();

    // Center map around editor's visible area
    int mapFirst = editorFirst + editorVisible / 2 - mapVisible / 2;
    mapFirst = qBound(0, mapFirst, qMax(0, tl - mapVisible));
    map->setFirstVisibleLine(mapFirst);

    overlay->update();
    syncing = false;
}

// ── Viewport rect — relative to map scroll position ──────────────────────────
QRect MinimapPanel::viewportRect() const
{
    if (!mainEditor) return QRect();

    int mapFirst      = (int)map->firstVisibleLine();
    int mapVisible    = (int)map->linesOnScreen();
    int editorFirst   = (int)mainEditor->firstVisibleLine();
    int editorVisible = (int)mainEditor->linesOnScreen();
    int h = height();
    if (mapVisible <= 0) return QRect();

    double lineH = (double)h / mapVisible;
    int y1 = (int)((editorFirst - mapFirst) * lineH);
    int y2 = (int)((editorFirst + editorVisible - mapFirst) * lineH);
    y1 = qBound(0, y1, h - 1);
    y2 = qBound(y1 + 4, y2, h);
    return QRect(0, y1, width(), y2 - y1);
}

// ── Click / drag ──────────────────────────────────────────────────────────────
int MinimapPanel::yToEditorFirst(int y) const
{
    if (!mainEditor) return 0;
    int tl  = (int)mainEditor->lineCount();
    int vis = (int)mainEditor->linesOnScreen();
    int h   = height();
    if (h <= 0 || tl <= 0) return 0;
    int clicked = (int)((double)y / h * tl);
    int first   = clicked - vis / 2;
    return qBound(0, first, qMax(0, tl - vis));
}

void MinimapPanel::overlayPress(const QPoint &pos)
{
    if (!mainEditor) return;
    dragging      = true;
    dragStartY    = pos.y();
    dragStartLine = (int)mainEditor->firstVisibleLine();

    if (!viewportRect().contains(pos)) {
        mainEditor->setFirstVisibleLine(yToEditorFirst(pos.y()));
        dragStartLine = (int)mainEditor->firstVisibleLine();
        dragStartY    = pos.y();
    }
}

void MinimapPanel::overlayMove(const QPoint &pos)
{
    if (!mainEditor || !dragging) return;
    int tl = (int)mainEditor->lineCount();
    int h  = height();
    if (h <= 0 || tl <= 0) return;

    int dy        = pos.y() - dragStartY;
    int lineDelta = (int)((double)dy / h * tl);
    int newFirst  = qBound(0, dragStartLine + lineDelta,
                           qMax(0, tl - (int)mainEditor->linesOnScreen()));
    mainEditor->setFirstVisibleLine(newFirst);
}

void MinimapPanel::overlayRelease() { dragging = false; }

void MinimapPanel::overlayWheel(QWheelEvent *e)
{
    if (mainEditor) QApplication::sendEvent(mainEditor, e);
}

void MinimapPanel::wheelEvent(QWheelEvent *e)
{
    if (mainEditor) QApplication::sendEvent(mainEditor, e);
}
