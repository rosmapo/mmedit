#include "ColorPickerDialog.h"
#include "ScintillaNext.h"

#include <QColorDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QSlider>
#include <QSpinBox>
#include <QPainter>
#include <QPixmap>
#include <QApplication>
#include <QRegularExpression>
#include <QSettings>
#include <QShowEvent>
#include <QCloseEvent>

static constexpr int kCustomColorCount = 16;
static constexpr char kSettingsGroup[] = "ColorPicker";
static constexpr char kCustomColorsKey[] = "CustomColors";

ColorPickerDialog::ColorPickerDialog(QWidget *parent)
    : QDialog(parent, Qt::Tool | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
    setWindowTitle(tr("Color Picker"));
    setSizeGripEnabled(false);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(6);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // ── Embedded QColorDialog ────────────────────────────────────────────────
    m_picker = new QColorDialog(this);
    m_picker->setWindowFlags(Qt::Widget);
    m_picker->setOptions(QColorDialog::NoButtons | QColorDialog::DontUseNativeDialog);

    // Skryjeme eye-dropper tlačidlo
    for (auto *btn : m_picker->findChildren<QPushButton *>()) {
        const QString t = btn->text().simplified().toLower();
        if (t.contains("pick") || t.contains("screen") || t.contains("dropper"))
            btn->hide();
    }

    // Skryjeme pravý panel (HSV/RGB spinboxy) – je to druhý QWidget na úrovni
    // priameho potomka, ktorý obsahuje QLabel "Hue:" ako vnorený widget.
    // Spoľahlivejší prístup: skryjeme všetky QLabel+QSpinBox skupiny vpravo
    // tým, že nájdeme kontajner obsahujúci label "Hue:".
    for (auto *lbl : m_picker->findChildren<QLabel *>()) {
        const QString t = lbl->text().simplified().toLower();
        if (t == "hue:" || t == "hue") {
            // Rodič tohto labelu je pravý panel – skryjeme ho
            if (QWidget *rightPanel = lbl->parentWidget())
                rightPanel->hide();
            break;
        }
    }

    mainLayout->addWidget(m_picker);

    // ── Checkerboard pixmap pre náhľad ───────────────────────────────────────
    QPixmap checkerPm(16, 16);
    checkerPm.fill(Qt::white);
    {
        QPainter pt(&checkerPm);
        pt.fillRect(0, 0, 8, 8, QColor(204, 204, 204));
        pt.fillRect(8, 8, 8, 8, QColor(204, 204, 204));
    }

    // ── Preview – plná šírka, vyššia, so šachovnicovým pozadím ──────────────
    auto *previewContainer = new QWidget(this);
    previewContainer->setFixedHeight(32);
    QPalette previewPal = previewContainer->palette();
    previewPal.setBrush(QPalette::Window, QBrush(checkerPm));
    previewContainer->setPalette(previewPal);
    previewContainer->setAutoFillBackground(true);

    auto *previewInner = new QVBoxLayout(previewContainer);
    previewInner->setContentsMargins(0, 0, 0, 0);
    m_preview = new QFrame(previewContainer);
    m_preview->setFrameShape(QFrame::NoFrame);
    previewInner->addWidget(m_preview);
    mainLayout->addWidget(previewContainer);

    // ── Alpha row ────────────────────────────────────────────────────────────
    auto *alphaRow = new QHBoxLayout;
    alphaRow->addWidget(new QLabel(tr("Alpha:"), this));
    m_alphaSlider = new QSlider(Qt::Horizontal, this);
    m_alphaSlider->setRange(0, 255);
    m_alphaSlider->setValue(255);
    alphaRow->addWidget(m_alphaSlider, 1);
    m_alphaSpin = new QSpinBox(this);
    m_alphaSpin->setRange(0, 255);
    m_alphaSpin->setValue(255);
    m_alphaSpin->setFixedWidth(55);
    m_alphaSpin->setButtonSymbols(QAbstractSpinBox::NoButtons);
    alphaRow->addWidget(m_alphaSpin);
    mainLayout->addLayout(alphaRow);

    // ── Code rows – RGB vľavo, HEX vpravo (jeden riadok) ────────────────────
    auto *grid = new QGridLayout;
    grid->setSpacing(4);

    grid->addWidget(new QLabel(tr("RGB:"), this), 0, 0);
    m_rgbEdit = new QLineEdit(this);
    m_rgbEdit->setPlaceholderText("rgb(r, g, b)");
    grid->addWidget(m_rgbEdit, 0, 1);
    auto *rgbInsert = new QPushButton(tr("Insert"), this);
    grid->addWidget(rgbInsert, 0, 2);

    grid->addWidget(new QLabel(tr("HEX:"), this), 0, 3);
    m_hexEdit = new QLineEdit(this);
    m_hexEdit->setPlaceholderText("#RRGGBB");
    grid->addWidget(m_hexEdit, 0, 4);
    auto *hexInsert = new QPushButton(tr("Insert"), this);
    grid->addWidget(hexInsert, 0, 5);

    // Obe edit polia sa rovnomerne roztiahnu
    grid->setColumnStretch(1, 1);
    grid->setColumnStretch(4, 1);

    mainLayout->addLayout(grid);

    auto *closeBtn = new QPushButton(tr("Close"), this);
    mainLayout->addWidget(closeBtn, 0, Qt::AlignRight);

    // ── Connections ──────────────────────────────────────────────────────────
    connect(m_picker, &QColorDialog::currentColorChanged,
            this, &ColorPickerDialog::onPickerColorChanged);

    connect(m_alphaSlider, &QSlider::valueChanged, m_alphaSpin, &QSpinBox::setValue);
    connect(m_alphaSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            m_alphaSlider, &QSlider::setValue);
    connect(m_alphaSlider, &QSlider::valueChanged,
            this, &ColorPickerDialog::onAlphaChanged);

    connect(m_hexEdit, &QLineEdit::editingFinished, this, &ColorPickerDialog::onHexEdited);
    connect(m_rgbEdit, &QLineEdit::editingFinished, this, &ColorPickerDialog::onRgbEdited);

    connect(hexInsert, &QPushButton::clicked, this, [this] { insertText(m_hexEdit->text()); });
    connect(rgbInsert, &QPushButton::clicked, this, [this] { insertText(m_rgbEdit->text()); });
    connect(closeBtn,  &QPushButton::clicked, this, &QDialog::close);

    m_color = Qt::white;
    updateCodes(m_color);
    updatePreview();
}

void ColorPickerDialog::setEditor(ScintillaNext *editor)
{
    m_editor = editor;
}

// ── Persist custom colors ────────────────────────────────────────────────────

void ColorPickerDialog::loadCustomColors()
{
    QSettings s;
    s.beginGroup(kSettingsGroup);
    const QStringList saved = s.value(kCustomColorsKey).toStringList();
    s.endGroup();
    for (int i = 0; i < qMin(saved.size(), kCustomColorCount); ++i) {
        bool ok;
        const uint rgb = saved[i].toUInt(&ok, 16);
        if (ok)
            QColorDialog::setCustomColor(i, QColor::fromRgba(rgb));
    }
}

void ColorPickerDialog::saveCustomColors()
{
    QStringList list;
    list.reserve(kCustomColorCount);
    for (int i = 0; i < kCustomColorCount; ++i)
        list << QString::number(QColorDialog::customColor(i).rgba(), 16);
    QSettings s;
    s.beginGroup(kSettingsGroup);
    s.setValue(kCustomColorsKey, list);
    s.endGroup();
}

void ColorPickerDialog::showEvent(QShowEvent *event)
{
    loadCustomColors();
    QDialog::showEvent(event);
}

void ColorPickerDialog::closeEvent(QCloseEvent *event)
{
    saveCustomColors();
    QDialog::closeEvent(event);
}

// ── Slots ────────────────────────────────────────────────────────────────────

void ColorPickerDialog::onPickerColorChanged(const QColor &color)
{
    if (m_updating) return;
    m_updating = true;
    m_color.setRed(color.red());
    m_color.setGreen(color.green());
    m_color.setBlue(color.blue());
    updateCodes(m_color);
    updatePreview();
    m_updating = false;
}

void ColorPickerDialog::onAlphaChanged(int alpha)
{
    if (m_updating) return;
    m_updating = true;
    m_color.setAlpha(alpha);
    updateCodes(m_color);
    updatePreview();
    m_updating = false;
}

void ColorPickerDialog::onHexEdited()
{
    if (m_updating) return;
    QColor c;
    if (!parseHex(m_hexEdit->text().trimmed(), c)) return;
    m_updating = true;
    m_color = c;
    m_picker->setCurrentColor(QColor(c.red(), c.green(), c.blue()));
    m_alphaSlider->setValue(c.alpha());
    m_alphaSpin->setValue(c.alpha());
    updateCodes(m_color);
    updatePreview();
    m_updating = false;
}

void ColorPickerDialog::onRgbEdited()
{
    if (m_updating) return;
    QColor c;
    if (!parseRgb(m_rgbEdit->text().trimmed(), c)) return;
    m_updating = true;
    m_color = c;
    m_picker->setCurrentColor(QColor(c.red(), c.green(), c.blue()));
    m_alphaSlider->setValue(c.alpha());
    m_alphaSpin->setValue(c.alpha());
    updateCodes(m_color);
    updatePreview();
    m_updating = false;
}

// ── Helpers ──────────────────────────────────────────────────────────────────

void ColorPickerDialog::updateCodes(const QColor &color)
{
    m_hexEdit->blockSignals(true);
    m_rgbEdit->blockSignals(true);
    m_hexEdit->setText(hexCode(color));
    m_rgbEdit->setText(rgbCode(color));
    m_hexEdit->blockSignals(false);
    m_rgbEdit->blockSignals(false);
}

void ColorPickerDialog::updatePreview()
{
    m_preview->setStyleSheet(
        QStringLiteral("background-color: rgba(%1,%2,%3,%4);")
        .arg(m_color.red()).arg(m_color.green())
        .arg(m_color.blue()).arg(m_color.alpha()));
}

QString ColorPickerDialog::hexCode(const QColor &color) const
{
    if (color.alpha() == 255)
        return QStringLiteral("#%1%2%3")
            .arg(color.red(),   2, 16, QChar('0'))
            .arg(color.green(), 2, 16, QChar('0'))
            .arg(color.blue(),  2, 16, QChar('0'))
            .toUpper();
    return QStringLiteral("#%1%2%3%4")
        .arg(color.red(),   2, 16, QChar('0'))
        .arg(color.green(), 2, 16, QChar('0'))
        .arg(color.blue(),  2, 16, QChar('0'))
        .arg(color.alpha(), 2, 16, QChar('0'))
        .toUpper();
}

QString ColorPickerDialog::rgbCode(const QColor &color) const
{
    if (color.alpha() == 255)
        return QStringLiteral("rgb(%1, %2, %3)")
            .arg(color.red()).arg(color.green()).arg(color.blue());
    return QStringLiteral("rgba(%1, %2, %3, %4)")
        .arg(color.red()).arg(color.green()).arg(color.blue())
        .arg(QString::number(color.alpha() / 255.0, 'f', 3));
}

bool ColorPickerDialog::parseHex(const QString &s, QColor &out) const
{
    static const QRegularExpression re(
        QStringLiteral("^#?([0-9a-fA-F]{3}|[0-9a-fA-F]{6}|[0-9a-fA-F]{8})$"));
    const auto m = re.match(s.startsWith('#') ? s : '#' + s);
    if (!m.hasMatch()) return false;
    QString hex = m.captured(1);
    if (hex.length() == 3)
        hex = QString("%1%1%2%2%3%3").arg(hex[0]).arg(hex[1]).arg(hex[2]);
    if (hex.length() == 8) {
        out = QColor(hex.mid(0,2).toInt(nullptr,16), hex.mid(2,2).toInt(nullptr,16),
                     hex.mid(4,2).toInt(nullptr,16), hex.mid(6,2).toInt(nullptr,16));
    } else {
        out = QColor(hex.mid(0,2).toInt(nullptr,16), hex.mid(2,2).toInt(nullptr,16),
                     hex.mid(4,2).toInt(nullptr,16), 255);
    }
    return out.isValid();
}

bool ColorPickerDialog::parseRgb(const QString &s, QColor &out) const
{
    static const QRegularExpression re(
        QStringLiteral("^rgba?\\(\\s*(\\d+)\\s*,\\s*(\\d+)\\s*,\\s*(\\d+)"
                        "(?:\\s*,\\s*([\\d.]+))?\\s*\\)$"),
        QRegularExpression::CaseInsensitiveOption);
    const auto m = re.match(s);
    if (!m.hasMatch()) return false;
    int r = m.captured(1).toInt(), g = m.captured(2).toInt(), b = m.captured(3).toInt();
    int a = 255;
    if (!m.captured(4).isEmpty()) {
        double av = m.captured(4).toDouble();
        a = (av <= 1.0) ? qRound(av * 255) : qRound(av);
    }
    out = QColor(qBound(0,r,255), qBound(0,g,255), qBound(0,b,255), qBound(0,a,255));
    return out.isValid();
}

void ColorPickerDialog::insertText(const QString &text)
{
    if (!m_editor) return;
    m_editor->replaceSel(text.toUtf8().constData());
}
