#pragma once

#include <QDialog>
#include <QColor>

class QColorDialog;
class QLineEdit;
class QPushButton;
class QFrame;
class QSlider;
class QSpinBox;
class ScintillaNext;

class ColorPickerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorPickerDialog(QWidget *parent = nullptr);
    void setEditor(ScintillaNext *editor);

protected:
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private:
    void onPickerColorChanged(const QColor &color);
    void onAlphaChanged(int alpha);
    void onHexEdited();
    void onRgbEdited();
    void updateCodes(const QColor &color);
    void updatePreview();
    void insertText(const QString &text);
    QString hexCode(const QColor &color) const;
    QString rgbCode(const QColor &color) const;
    bool parseHex(const QString &s, QColor &out) const;
    bool parseRgb(const QString &s, QColor &out) const;
    void loadCustomColors();
    void saveCustomColors();

    QColorDialog  *m_picker      = nullptr;
    QFrame        *m_preview     = nullptr;
    QSlider       *m_alphaSlider = nullptr;
    QSpinBox      *m_alphaSpin   = nullptr;
    QLineEdit     *m_hexEdit     = nullptr;
    QLineEdit     *m_rgbEdit     = nullptr;

    QColor         m_color;
    bool           m_updating = false;
    ScintillaNext *m_editor   = nullptr;
};
