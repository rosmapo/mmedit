#include "MarkdownPreviewDock.h"

#include <QScrollBar>
#include <QTextBrowser>
#include <QTextDocument>
#include <QVBoxLayout>
#include <QWidget>

#include "ScintillaNext.h"

MarkdownPreviewDock::MarkdownPreviewDock(QWidget *parent)
    : QDockWidget(tr("Markdown Preview"), parent)
{
    setObjectName("MarkdownPreviewDock");

    QWidget *container = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->setContentsMargins(0, 0, 0, 0);

    browser = new QTextBrowser(container);
    browser->setOpenExternalLinks(true);
    layout->addWidget(browser);

    setWidget(container);
}

void MarkdownPreviewDock::setEditor(ScintillaNext *editor)
{
    if (currentEditor) {
        disconnect(currentEditor, nullptr, this, nullptr);
    }

    currentEditor = editor;

    if (currentEditor) {
        connect(currentEditor, &ScintillaNext::updateUi, this, &MarkdownPreviewDock::updatePreview);
        updatePreview();
    } else {
        browser->clear();
    }
}

void MarkdownPreviewDock::updatePreview()
{
    if (!isVisible() || !currentEditor)
        return;

    const int len = static_cast<int>(currentEditor->textLength());
    const QString text = QString::fromUtf8(currentEditor->getText(len + 1).left(len));

    QTextDocument doc;
    doc.setMarkdown(text);

    // Preserve scroll position
    const int scrollPos = browser->verticalScrollBar()
        ? browser->verticalScrollBar()->value() : 0;

    browser->setDocument(new QTextDocument(browser));
    browser->document()->setMarkdown(text);

    if (browser->verticalScrollBar())
        browser->verticalScrollBar()->setValue(scrollPos);
}
