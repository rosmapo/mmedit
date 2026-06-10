#include "WordCountDialog.h"

#include <QDialogButtonBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>

#include "ScintillaNext.h"

WordCountDialog::WordCountDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Word Count"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setMinimumWidth(280);

    auto *mainLayout = new QVBoxLayout(this);

    // Helper to build a stats group box
    auto makeGroup = [&](const QString &title,
                         QLabel *&words, QLabel *&chars,
                         QLabel *&charsNoSpace, QLabel *&lines) -> QGroupBox *
    {
        auto *box    = new QGroupBox(title, this);
        auto *grid   = new QGridLayout(box);

        auto addRow = [&](int row, const QString &labelText, QLabel *&valueLabel) {
            grid->addWidget(new QLabel(labelText, box), row, 0);
            valueLabel = new QLabel("0", box);
            valueLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
            grid->addWidget(valueLabel, row, 1);
        };

        addRow(0, tr("Words:"),                words);
        addRow(1, tr("Characters:"),           chars);
        addRow(2, tr("Characters (no spaces):"), charsNoSpace);
        addRow(3, tr("Lines:"),                lines);

        grid->setColumnStretch(0, 1);
        return box;
    };

    mainLayout->addWidget(makeGroup(tr("Document"),
        m_docWords, m_docChars, m_docCharsNoSpace, m_docLines));

    mainLayout->addWidget(makeGroup(tr("Selection"),
        m_selWords, m_selChars, m_selCharsNoSpace, m_selLines));

    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Close, this);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::accept);
    mainLayout->addWidget(buttons);
}

void WordCountDialog::setEditor(ScintillaNext *editor)
{
    m_editor = editor;
    refresh();
}

WordCountDialog::Stats WordCountDialog::computeStats(const QString &text) const
{
    Stats s;
    s.chars        = text.length();
    s.charsNoSpace = 0;
    s.lines        = text.isEmpty() ? 0 : text.count('\n') + 1;
    s.words        = 0;

    bool inWord = false;
    for (const QChar &c : text) {
        if (!c.isSpace()) {
            s.charsNoSpace++;
            if (!inWord) { s.words++; inWord = true; }
        } else {
            inWord = false;
        }
    }

    return s;
}

void WordCountDialog::refresh()
{
    if (!m_editor) return;

    // Full document
    const int docLen      = static_cast<int>(m_editor->textLength());
    const QString docText = QString::fromUtf8(m_editor->getText(docLen + 1).left(docLen));
    const Stats   doc     = computeStats(docText);

    m_docWords->setText(QString::number(doc.words));
    m_docChars->setText(QString::number(doc.chars));
    m_docCharsNoSpace->setText(QString::number(doc.charsNoSpace));
    m_docLines->setText(QString::number(doc.lines));

    // Selection
    const QByteArray selRaw = m_editor->getSelText();
    // getSelText() includes a trailing NUL — strip it
    const QString selText = selRaw.isEmpty()
        ? QString()
        : QString::fromUtf8(selRaw.constData(), selRaw.size() - 1);
    const Stats sel = computeStats(selText);

    m_selWords->setText(QString::number(sel.words));
    m_selChars->setText(QString::number(sel.chars));
    m_selCharsNoSpace->setText(QString::number(sel.charsNoSpace));
    m_selLines->setText(QString::number(sel.lines));
}
