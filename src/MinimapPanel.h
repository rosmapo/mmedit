#ifndef MINIMAPPANEL_H
#define MINIMAPPANEL_H

#include <QWidget>
#include <QRect>
#include "ScintillaEdit.h"

class ScintillaNext;
class MinimapOverlay;

class MinimapPanel : public QWidget
{
    Q_OBJECT
    friend class MinimapOverlay;

public:
    explicit MinimapPanel(QWidget *parent = nullptr);
    void setEditor(ScintillaNext *editor);
    void refreshStyles();

    QSize sizeHint() const override { return QSize(120, 0); }
    QSize minimumSizeHint() const override { return QSize(80, 0); }

    QRect viewportRect() const;
    void  overlayPress(const QPoint &pos);
    void  overlayMove(const QPoint &pos);
    void  overlayRelease();
    void  overlayWheel(QWheelEvent *e);

protected:
    void resizeEvent(QResizeEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;

private:
    void syncFromEditor();
    void syncStyles();
    void applyDarkDefault();
    int  yToEditorFirst(int y) const;

    ScintillaEdit  *map     = nullptr;
    MinimapOverlay *overlay = nullptr;
    ScintillaNext  *mainEditor = nullptr;
    sptr_t sharedDoc  = 0;
    bool   syncing    = false;
    bool   dragging   = false;
    int    dragStartY    = 0;
    int    dragStartLine = 0;
};

#endif
