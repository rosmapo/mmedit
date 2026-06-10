#pragma once

#include <QDialog>

class ScintillaNext;
class QLabel;

class WordCountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WordCountDialog(QWidget *parent = nullptr);
    void setEditor(ScintillaNext *editor);

private:
    struct Stats {
        int words    = 0;
        int chars    = 0;
        int charsNoSpace = 0;
        int lines    = 0;
    };

    Stats computeStats(const QString &text) const;
    void  refresh();

    ScintillaNext *m_editor = nullptr;

    QLabel *m_docWords        = nullptr;
    QLabel *m_docChars        = nullptr;
    QLabel *m_docCharsNoSpace = nullptr;
    QLabel *m_docLines        = nullptr;

    QLabel *m_selWords        = nullptr;
    QLabel *m_selChars        = nullptr;
    QLabel *m_selCharsNoSpace = nullptr;
    QLabel *m_selLines        = nullptr;
};
