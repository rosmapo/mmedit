#pragma once

#include <QDockWidget>

class QTextBrowser;
class ScintillaNext;

class MarkdownPreviewDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit MarkdownPreviewDock(QWidget *parent = nullptr);

public slots:
    void setEditor(ScintillaNext *editor);
    void updatePreview();

private:
    QTextBrowser *browser = nullptr;
    ScintillaNext *currentEditor = nullptr;
};
