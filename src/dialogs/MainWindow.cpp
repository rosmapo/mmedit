/*
 * This file is part of Notepad Next.
 * Copyright 2019 Justin Dailey
 *
 * Notepad Next is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Notepad Next is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Notepad Next.  If not, see <https://www.gnu.org/licenses/>.
 */


#include "MainWindow.h"
#include "BookMarkDecorator.h"
#include "DefaultDirectoryManager.h"
#include "MarkerAppDecorator.h"
#include "ScintillaSorter.h"
#include "URLFinder.h"
#include "SessionManager.h"
#include "UndoAction.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <QClipboard>
#include <algorithm>
#include <QStandardPaths>
#include <QDesktopServices>
#include <QWindow>
#include <QPushButton>
#include <QDateTime>
#include <QLocale>
#include <QTimer>
#include <QRegularExpression>
#include <QInputDialog>
#include "ColorPickerDialog.h"
#include "WordCountDialog.h"
#include "MarkdownPreviewDock.h"
#include "SpellChecker.h"
#include "ShortcutEditorDialog.h"
#include <QPrintPreviewDialog>
#include <QPrinter>
#include <QDirIterator>
#include <QProcess>
#include <QScreen>
#include <QFontDatabase>

#ifdef Q_OS_WIN
#include <QSimpleUpdater.h>
#include <Windows.h>
#endif

#include "DockAreaWidget.h"

#include "NotepadNextApplication.h"
#include "ApplicationSettings.h"

#include "ScintillaNext.h"

#include "RecentFilesListManager.h"
#include "RecentFilesListMenuBuilder.h"
#include "EditorManager.h"

#include "FolderAsWorkspaceDock.h"
#include "SearchResultsDock.h"
#include "FileListDock.h"
#include "MinimapPanel.h"

#include "FindReplaceDialog.h"
#include "MacroRunDialog.h"
#include "MacroSaveDialog.h"
#include "PreferencesDialog.h"
#include "ColumnEditorDialog.h"

#include "TabsQuickActionsBar.h"

#include "QuickFindWidget.h"

#include "EditorPrintPreviewRenderer.h"
#include "MacroEditorDialog.h"

#include "ZoomEventWatcher.h"
#include "FileDialogHelpers.h"

#include "HtmlConverter.h"
#include "RtfConverter.h"

#include "FadingIndicator.h"

#include "ActionUtils.h"


MainWindow::MainWindow(NotepadNextApplication *app) :
    ui(new Ui::MainWindow),
    app(app),
    zoomEventWatcher(new ZoomEventWatcher(this))
{
    qInfo(Q_FUNC_INFO);

    setAttribute(Qt::WA_DeleteOnClose);

    ui->setupUi(this);

    // Encoding menu - fully implemented
    // ui->menuEncodings->menuAction()->setVisible(false); -- removed, now implemented

    // Helper: map action name to charset string
    auto actionToCharset = [](const QString &name) -> QString {
        if (name == "actionEncSetUTF8"       || name == "actionEncConvUTF8")       return "UTF-8";
        if (name == "actionEncSetUTF8BOM"    || name == "actionEncConvUTF8BOM")    return "UTF-8 BOM";
        if (name == "actionEncSetUTF16LE"    || name == "actionEncConvUTF16LE")    return "UTF-16 LE BOM";
        if (name == "actionEncSetUTF16BE"    || name == "actionEncConvUTF16BE")    return "UTF-16 BE BOM";
        if (name == "actionEncSetUTF16LEno"  || name == "actionEncConvUTF16LEno")  return "UTF-16 LE";
        if (name == "actionEncSetUTF16BEno"  || name == "actionEncConvUTF16BEno")  return "UTF-16 BE";
        // Western Europe
        if (name == "actionEncSetISO88591"   || name == "actionEncConvISO88591")   return "ISO-8859-1";
        if (name == "actionEncSetISO885915"  || name == "actionEncConvISO885915")  return "ISO-8859-15";
        if (name == "actionEncSetWin1252"    || name == "actionEncConvWin1252")    return "Windows-1252";
        // Central Europe
        if (name == "actionEncSetISO88592"   || name == "actionEncConvISO88592")   return "ISO-8859-2";
        if (name == "actionEncSetISO885916"  || name == "actionEncConvISO885916")  return "ISO-8859-16";
        if (name == "actionEncSetWin1250"    || name == "actionEncConvWin1250")    return "Windows-1250";
        // Baltic
        if (name == "actionEncSetISO88594"   || name == "actionEncConvISO88594")   return "ISO-8859-4";
        if (name == "actionEncSetISO885913"  || name == "actionEncConvISO885913")  return "ISO-8859-13";
        if (name == "actionEncSetWin1257"    || name == "actionEncConvWin1257")    return "Windows-1257";
        // Cyrillic
        if (name == "actionEncSetISO88595"   || name == "actionEncConvISO88595")   return "ISO-8859-5";
        if (name == "actionEncSetKOI8R"      || name == "actionEncConvKOI8R")      return "KOI8-R";
        if (name == "actionEncSetKOI8U"      || name == "actionEncConvKOI8U")      return "KOI8-U";
        if (name == "actionEncSetWin1251"    || name == "actionEncConvWin1251")    return "Windows-1251";
        // Greek
        if (name == "actionEncSetISO88597"   || name == "actionEncConvISO88597")   return "ISO-8859-7";
        if (name == "actionEncSetWin1253"    || name == "actionEncConvWin1253")    return "Windows-1253";
        // Turkish
        if (name == "actionEncSetISO88599"   || name == "actionEncConvISO88599")   return "ISO-8859-9";
        if (name == "actionEncSetWin1254"    || name == "actionEncConvWin1254")    return "Windows-1254";
        // Hebrew
        if (name == "actionEncSetISO88598"   || name == "actionEncConvISO88598")   return "ISO-8859-8";
        if (name == "actionEncSetWin1255"    || name == "actionEncConvWin1255")    return "Windows-1255";
        // Arabic
        if (name == "actionEncSetISO88596"   || name == "actionEncConvISO88596")   return "ISO-8859-6";
        if (name == "actionEncSetWin1256"    || name == "actionEncConvWin1256")    return "Windows-1256";
        return "UTF-8";
    };

    // "Set Encoding" actions — change charset and reload from disk
    QList<QAction*> setEncActions = {
        ui->actionEncSetUTF8, ui->actionEncSetUTF8BOM,
        ui->actionEncSetUTF16LE, ui->actionEncSetUTF16BE,
        ui->actionEncSetUTF16LEno, ui->actionEncSetUTF16BEno,
        // Western Europe
        ui->actionEncSetISO88591, ui->actionEncSetISO885915, ui->actionEncSetWin1252,
        // Central Europe
        ui->actionEncSetISO88592, ui->actionEncSetISO885916, ui->actionEncSetWin1250,
        // Baltic
        ui->actionEncSetISO88594, ui->actionEncSetISO885913, ui->actionEncSetWin1257,
        // Cyrillic
        ui->actionEncSetISO88595, ui->actionEncSetKOI8R, ui->actionEncSetKOI8U, ui->actionEncSetWin1251,
        // Greek
        ui->actionEncSetISO88597, ui->actionEncSetWin1253,
        // Turkish
        ui->actionEncSetISO88599, ui->actionEncSetWin1254,
        // Hebrew
        ui->actionEncSetISO88598, ui->actionEncSetWin1255,
        // Arabic
        ui->actionEncSetISO88596, ui->actionEncSetWin1256
    };
    for (QAction *action : setEncActions) {
        connect(action, &QAction::triggered, this, [=, this]() {
            ScintillaNext *editor = currentEditor();
            if (!editor || !editor->isFile()) {
                QMessageBox::information(this, tr("Encoding"),
                    tr("Please save the file first before changing encoding."));
                return;
            }
            QString charset = actionToCharset(action->objectName());
            auto reply = QMessageBox::question(this, tr("Set Encoding"),
                tr("Reload <b>%1</b> as <b>%2</b>?<br><br>"
                   "Unsaved changes will be lost.")
                .arg(editor->getName()).arg(charset),
                QMessageBox::Yes | QMessageBox::No);
            if (reply != QMessageBox::Yes) return;

            editor->setCharset(charset);
            // Set BOM type based on charset
            if (charset == "UTF-8 BOM")
                editor->setBomType(ScintillaNext::BomType::Utf8);
            else if (charset == "UTF-16 LE BOM")
                editor->setBomType(ScintillaNext::BomType::Utf16LE);
            else if (charset == "UTF-16 BE BOM")
                editor->setBomType(ScintillaNext::BomType::Utf16BE);
            else
                editor->setBomType(ScintillaNext::BomType::None);

            // Refresh status bar after reload completes (reload is async via signals)
            connect(editor, &ScintillaNext::reloaded, this, [this, editor]() {
                ui->statusBar->refresh(editor);
            }, Qt::SingleShotConnection);
            editor->reload();
        });
    }

    // "Convert to" actions — re-encode content in memory, change charset, mark modified
    QList<QAction*> convEncActions = {
        ui->actionEncConvUTF8, ui->actionEncConvUTF8BOM,
        ui->actionEncConvUTF16LE, ui->actionEncConvUTF16BE,
        ui->actionEncConvUTF16LEno, ui->actionEncConvUTF16BEno,
        // Western Europe
        ui->actionEncConvISO88591, ui->actionEncConvISO885915, ui->actionEncConvWin1252,
        // Central Europe
        ui->actionEncConvISO88592, ui->actionEncConvISO885916, ui->actionEncConvWin1250,
        // Baltic
        ui->actionEncConvISO88594, ui->actionEncConvISO885913, ui->actionEncConvWin1257,
        // Cyrillic
        ui->actionEncConvISO88595, ui->actionEncConvKOI8R, ui->actionEncConvKOI8U, ui->actionEncConvWin1251,
        // Greek
        ui->actionEncConvISO88597, ui->actionEncConvWin1253,
        // Turkish
        ui->actionEncConvISO88599, ui->actionEncConvWin1254,
        // Hebrew
        ui->actionEncConvISO88598, ui->actionEncConvWin1255,
        // Arabic
        ui->actionEncConvISO88596, ui->actionEncConvWin1256
    };
    for (QAction *action : convEncActions) {
        connect(action, &QAction::triggered, this, [=, this]() {
            ScintillaNext *editor = currentEditor();
            if (!editor) return;
            QString newCharset = actionToCharset(action->objectName());
            if (newCharset == editor->charset()) return;

            // Content is already UTF-8 in Scintilla — just change the charset
            // The conversion happens on next save via writeToDiskWithCharset
            editor->setCharset(newCharset);

            if (newCharset == "UTF-8 BOM")
                editor->setBomType(ScintillaNext::BomType::Utf8);
            else if (newCharset == "UTF-16 LE BOM")
                editor->setBomType(ScintillaNext::BomType::Utf16LE);
            else if (newCharset == "UTF-16 BE BOM")
                editor->setBomType(ScintillaNext::BomType::Utf16BE);
            else
                editor->setBomType(ScintillaNext::BomType::None);

            // Mark as modified so user knows to save
            // Insert and immediately delete a char to trigger the modified flag
            editor->insertText(0, " ");
            editor->deleteRange(0, 1);

            ui->statusBar->refresh(editor);
        });
    }

    // Snapshot every action's "designer"/code default shortcut *before* any
    // custom shortcuts from the config are applied. A few actions get their
    // real default shortcut assigned by code further below (actionExit,
    // actionNextTab/actionPreviousTab, actionAboutNotepadNext); those are
    // re-recorded right after that code runs.
    captureDefaultShortcuts();

    applyCustomShortcuts();

    qInfo("setupUi Completed");

    defaultDirectoryManager = new DefaultDirectoryManager(this, app->getSettings());

    connect(this, &MainWindow::aboutToClose, this, &MainWindow::saveSettings);

    // Create and set up the connections to the docked editor
    dockedEditor = new DockedEditor(this);
    connect(dockedEditor, &DockedEditor::editorCloseRequested, this, &MainWindow::closeFile);

    connect(dockedEditor, &DockedEditor::lastEditorClosed, this, [=, this]() {
        close();
    });
    connect(dockedEditor, &DockedEditor::editorActivated, this, &MainWindow::activateEditor);
    connect(dockedEditor, &DockedEditor::contextMenuRequestedForEditor, this, &MainWindow::tabBarRightClicked);

    // Color preview calltip on mouse hover over hex/rgb color values.
    // Uses Scintilla callTipShow + callTipSetBack — same approach as Geany's addons plugin.
    connect(dockedEditor, &DockedEditor::editorAdded, this, [](ScintillaNext *editor) {
        editor->setMouseDwellTime(500);
        QObject::connect(editor, &ScintillaNext::dwellStart, editor, [editor](int x, int y) {
            const int pos = editor->positionFromPoint(x, y);
            if (pos < 0) return;
            static const QRegularExpression colorRe(
                QStringLiteral("(#[0-9a-fA-F]{3,8}|rgb\\(\\s*\\d+\\s*,\\s*\\d+\\s*,\\s*\\d+\\s*\\))"));
            const int start = std::max(0, pos - 30);
            const int end   = std::min((int)editor->length(), pos + 30);
            const QString window = QString::fromUtf8(
                QByteArray(editor->textRange(start, end)));
            const int relPos = pos - start;
            const auto match = colorRe.match(window);
            if (!match.hasMatch()) return;
            if (relPos < match.capturedStart() || relPos > match.capturedEnd()) return;
            const QString token = match.captured(0);
            QColor color;
            if (token.startsWith('#')) {
                color = QColor(token.left(7));
            } else {
                auto parts = token.mid(4, token.length() - 5).split(',');
                if (parts.size() == 3)
                    color = QColor(parts[0].trimmed().toInt(),
                                   parts[1].trimmed().toInt(),
                                   parts[2].trimmed().toInt());
            }
            if (!color.isValid()) return;
            // Build a calltip string wide enough to show a color swatch.
            // Geany uses the same technique: callTipSetBack sets the background
            // of the calltip popup to the color, spaces fill the visible area.
            const QString spaces = QStringLiteral("     "); // ~5 chars wide
            const QByteArray tip = spaces.toUtf8();
            editor->callTipShow(pos, tip.constData());
            editor->callTipSetBack(color.rgb() & 0xFFFFFF);
        });
        QObject::connect(editor, &ScintillaNext::dwellEnd, editor, [editor](int, int) {
            editor->callTipCancel();
        });
    });
    connect(dockedEditor, &DockedEditor::titleBarDoubleClicked, this, &MainWindow::newFile);

    // Set up the menus
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newFile);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFileDialog);
    connect(ui->actionReload, &QAction::triggered, this, &MainWindow::reloadFile);
    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::closeCurrentFile);
    connect(ui->actionCloseAll, &QAction::triggered, this, &MainWindow::closeAllFiles);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);

    // Split editor actions
    connect(ui->actionSplitHorizontal, &QAction::triggered, this, [this]() {
        newFile();
        ScintillaNext *newEditor = currentEditor();
        if (newEditor) {
            dockedEditor->splitToRight(newEditor);
        }
    });
    connect(ui->actionSplitVertical, &QAction::triggered, this, [this]() {
        newFile();
        ScintillaNext *newEditor = currentEditor();
        if (newEditor) {
            dockedEditor->splitToBottom(newEditor);
        }
    });

#ifdef Q_OS_WIN
    ui->actionExit->setShortcut(QKeySequence("Alt+F4"));
#else
    ui->actionExit->setShortcut(QKeySequence::Quit);
#endif
    recordDefaultShortcut(ui->actionExit);

    connect(ui->actionOpenFolderasWorkspace, &QAction::triggered, this, &MainWindow::openFolderAsWorkspaceDialog);

    connect(ui->actionCloseAllExceptActive, &QAction::triggered, this, &MainWindow::closeAllExceptActive);
    connect(ui->actionCloseAllToLeft, &QAction::triggered, this, &MainWindow::closeAllToLeft);
    connect(ui->actionCloseAllToRight, &QAction::triggered, this, &MainWindow::closeAllToRight);

    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveCurrentFile);
    connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::saveCurrentFileAsDialog);
    connect(ui->actionSaveCopyAs, &QAction::triggered, this, &MainWindow::saveCopyAsDialog);
    connect(ui->actionSaveAll, &QAction::triggered, this, &MainWindow::saveAll);
    connect(ui->actionRename, &QAction::triggered, this, &MainWindow::renameFile);

    connect(ui->actionExportHtml, &QAction::triggered, this, [this]() {
        HtmlConverter html(currentEditor());
        exportAsFormat(&html, QStringLiteral("HTML files (*.html)"));
    });

    connect(ui->actionExportRtf, &QAction::triggered, this, [this]() {
        RtfConverter rtf(currentEditor());
        exportAsFormat(&rtf, QStringLiteral("RTF Files (*.rtf)"));
    });

    connect(ui->actionPrint, &QAction::triggered, this, &MainWindow::print);

    connectEditorAction(ui->actionToggleSingleLineComment, &ScintillaNext::toggleCommentSelection);
    connectEditorAction(ui->actionSingleLineComment, &ScintillaNext::commentLineSelection);
    connectEditorAction(ui->actionSingleLineUncomment, &ScintillaNext::uncommentLineSelection);

    connect(ui->actionBase64Encode, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        const QByteArray selection = editor->getSelText();
        editor->replaceSel(selection.toBase64().constData());
    });
    connect(ui->actionURLEncode, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        const QByteArray selection = editor->getSelText();
        editor->replaceSel(selection.toPercentEncoding().constData());
    });
    connect(ui->actionBase64Decode, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        const QByteArray selection = editor->getSelText();
        if (auto result = QByteArray::fromBase64Encoding(selection)) {
            editor->replaceSel((*result).constData());
        }
    });
    connect(ui->actionURLDecode,&QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        const QByteArray selection = editor->getSelText();
        editor->replaceSel(QByteArray::fromPercentEncoding(selection).constData());
    });
    connect(ui->actionCopyURL, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        URLFinder *urlFinder = editor->findChild<URLFinder *>(QString(), Qt::FindDirectChildrenOnly);
        if (urlFinder && urlFinder->isEnabled()) {
            urlFinder->copyURLToClipboard(contextMenuPos);
        }
    });

    connect(ui->actionClearRecentFilesList, &QAction::triggered, app->getRecentFilesListManager(), &RecentFilesListManager::clear);

    connect(ui->actionMoveToTrash, &QAction::triggered, this, &MainWindow::moveCurrentFileToTrash);

    RecentFilesListMenuBuilder *recentFileListMenuBuilder = new RecentFilesListMenuBuilder(app->getRecentFilesListManager());
    connect(ui->menuRecentFiles, &QMenu::aboutToShow, this, [=, this]() {
        // NOTE: its unfortunate that this has to be hard coded, but there's no way
        // to easily determine what should or shouldn't be there
        while (ui->menuRecentFiles->actions().size() > 4) {
            delete ui->menuRecentFiles->actions().takeLast();
        }

        recentFileListMenuBuilder->populateMenu(ui->menuRecentFiles);
    });

    connect(ui->actionRestoreRecentlyClosedFile, &QAction::triggered, this, [=, this]() {
        if (app->getRecentFilesListManager()->count() > 0) {
            openFileList(QStringList() << app->getRecentFilesListManager()->mostRecentFile());
        }
    });

    connect(ui->actionOpenAllRecentFiles, &QAction::triggered, this, [=, this]() {
        openFileList(app->getRecentFilesListManager()->fileList());
    });

    connect(recentFileListMenuBuilder, &RecentFilesListMenuBuilder::fileOpenRequest, this, &MainWindow::openFile);

    QActionGroup *eolActionGroup = new QActionGroup(this);
    eolActionGroup->addAction(ui->actionWindows);
    eolActionGroup->addAction(ui->actionUnix);
    eolActionGroup->addAction(ui->actionMacintosh);

    ui->actionWindows->setData(SC_EOL_CRLF);
    ui->actionUnix->setData(SC_EOL_LF);
    ui->actionMacintosh->setData(SC_EOL_CR);

    auto handleEolTrigger = [this]() {
        // qobject_cast lets us look at which specific action was clicked
        if (auto* action = qobject_cast<QAction*>(sender())) {
            int eolMode = action->data().toInt();
            convertEOLs(eolMode);
        }
    };

    // Connect all three to the same handler
    connect(ui->actionWindows,   &QAction::triggered, this, handleEolTrigger);
    connect(ui->actionUnix,      &QAction::triggered, this, handleEolTrigger);
    connect(ui->actionMacintosh, &QAction::triggered, this, handleEolTrigger);


    connectEditorAction(ui->actionUpperCase, &ScintillaNext::upperCase);
    connectEditorAction(ui->actionLowerCase, &ScintillaNext::lowerCase);

    connect(ui->actionTitleCase, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        if (!editor) return;
        QString text = QString::fromUtf8(editor->getSelText());
        if (text.endsWith(QLatin1Char(' '))) text.chop(1);
        bool nextUpper = true;
        for (QChar &c : text) {
            if (c.isSpace() || c == QLatin1Char('-') || c == QLatin1Char('_')) {
                nextUpper = true;
            } else {
                c = nextUpper ? c.toUpper() : c.toLower();
                nextUpper = false;
            }
        }
        editor->replaceSel(text.toUtf8().constData());
    });

    connect(ui->actionSentenceCase, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        if (!editor) return;
        QString text = QString::fromUtf8(editor->getSelText());
        if (text.endsWith(QLatin1Char(' '))) text.chop(1);
        bool nextUpper = true;
        for (QChar &c : text) {
            if (c == QLatin1Char('.') || c == QLatin1Char('!') || c == QLatin1Char('?')) {
                nextUpper = true;
            } else if (!c.isSpace()) {
                c = nextUpper ? c.toUpper() : c.toLower();
                nextUpper = false;
            }
        }
        editor->replaceSel(text.toUtf8().constData());
    });

    connect(ui->actionInvertCase, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        if (!editor) return;
        QString text = QString::fromUtf8(editor->getSelText());
        for (QChar &c : text) {
            if (c.isUpper())
                c = c.toLower();
            else if (c.isLower())
                c = c.toUpper();
        }
        editor->replaceSel(text.toUtf8().constData());
    });

    connectEditorAction(ui->actionDuplicateCurrentLine, &ScintillaNext::lineDuplicate);
    connectEditorAction(ui->actionMoveSelectedLinesUp, &ScintillaNext::moveSelectedLinesUp);
    connectEditorAction(ui->actionMoveSelectedLinesDown, &ScintillaNext::moveSelectedLinesDown);

    connect(ui->actionSplitLines, &QAction::triggered, this, [this]() {
        currentEditor()->targetFromSelection();
        currentEditor()->linesSplit(0);
    });

    connect(ui->actionJoinLines, &QAction::triggered, this, [this]()  {
        currentEditor()->targetFromSelection();
        currentEditor()->linesJoin();
    });

    connect(ui->actionRemoveEmptyLines, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        Finder f(editor);
        const UndoAction ua(editor);

        f.setSearchText(QStringLiteral("\\R\\R+"));
        f.setSearchFlags(SCFIND_REGEXP);
        f.replaceAll(editor->eolString());

        // The regex will not entirely remove a blank first line
        editor->deleteLeadingEmptyLines();

        // Regex will also not delete the final blank line
        editor->deleteTrailingEmptyLines();
    });

    connectEditorAction(ui->actionRemoveDuplicateLines, &ScintillaNext::removeDuplicateLines);
    connectEditorAction(ui->actionRemoveConsecutiveDuplicateLines, &ScintillaNext::removeConsecutiveDuplicateLines);

    connect(ui->actionReverseLineOrder, &QAction::triggered, this, [=, this]() {
        ScintillaSorter scintillaSorter(currentEditor());
        scintillaSorter.sort(ReverseSorter(Sorter::Direction::Ascending));
    });
    connect(ui->actionSortLinesAsc, &QAction::triggered, this, [=, this]() {
        ScintillaSorter scintillaSorter(currentEditor());
        scintillaSorter.sort(CaseSensitiveSorter(Sorter::Direction::Ascending));
    });
    connect(ui->actionSortLinesAscCaseInsensitive, &QAction::triggered, this, [=, this]() {
        ScintillaSorter scintillaSorter(currentEditor());
        scintillaSorter.sort(CaseInsensitiveSorter(Sorter::Direction::Ascending));
    });
    connect(ui->actionSortLinesbyLengthAsc, &QAction::triggered, this, [=, this]() {
        ScintillaSorter scintillaSorter(currentEditor());
        scintillaSorter.sort(LineLengthSorter(Sorter::Direction::Ascending));
    });
    connect(ui->actionSortLinesDesc, &QAction::triggered, this, [=, this]() {
        ScintillaSorter scintillaSorter(currentEditor());
        scintillaSorter.sort(CaseSensitiveSorter(Sorter::Direction::Descending));
    });
    connect(ui->actionSortLinesDescCaseInsensitive, &QAction::triggered, this, [=, this]() {
        ScintillaSorter scintillaSorter(currentEditor());
        scintillaSorter.sort(CaseInsensitiveSorter(Sorter::Direction::Descending));
    });
    connect(ui->actionSortLinesbyLengthDesc, &QAction::triggered, this, [=, this]() {
        ScintillaSorter scintillaSorter(currentEditor());
        scintillaSorter.sort(LineLengthSorter(Sorter::Direction::Descending));
    });

    connect(ui->actionColumnMode, &QAction::triggered, this, [this]() {
        ColumnEditorDialog *columnEditor = findChild<ColumnEditorDialog *>(QString(), Qt::FindDirectChildrenOnly);

        if (columnEditor == Q_NULLPTR) {
            columnEditor = new ColumnEditorDialog(this);
        }

        columnEditor->show();
        columnEditor->raise();
        columnEditor->activateWindow();
    });

    connectEditorAction(ui->actionUndo, &ScintillaNext::undo);
    connectEditorAction(ui->actionRedo, &ScintillaNext::redo);
    connectEditorAction(ui->actionCut, &ScintillaNext::cutAllowLine);

    // Custom Copy: if multiple selections exist, join each selection with a
    // newline so that pasting into a new file places each fragment on its own
    // line (consistent with VS Code, Sublime Text, etc.).
    connect(ui->actionCopy, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        if (!editor) return;
        const int numSelections = editor->selections();
        if (numSelections <= 1) {
            // Single selection (or no selection) — use the default behaviour.
            editor->copyAllowLine();
            return;
        }
        // Collect each selected range's text in document order.
        QStringList parts;
        parts.reserve(numSelections);
        for (int i = 0; i < numSelections; ++i) {
            const int start = editor->selectionNStart(i);
            const int end   = editor->selectionNEnd(i);
            if (start == end) continue; // skip empty carets
            parts << QString::fromUtf8(QByteArray(editor->textRange(start, end)));
        }
        if (parts.isEmpty()) {
            editor->copyAllowLine();
            return;
        }
        // Determine the EOL string used by this document so we insert the
        // correct line ending (CRLF on Windows docs, LF elsewhere).
        const QString eol = QString::fromUtf8(editor->eolString());
        QApplication::clipboard()->setText(parts.join(eol));
    });

    connectEditorAction(ui->actionDelete, &ScintillaNext::clear);

    // Custom Paste: when the clipboard text contains embedded newlines that
    // were produced by our multi-selection copy above, and the target editor
    // has a matching number of selections, distribute one fragment per caret.
    // Otherwise fall back to the normal paste behaviour.
    connect(ui->actionPaste, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        if (!editor) return;
        const QString clipText = QApplication::clipboard()->text();
        const int numSelections = editor->selections();
        if (numSelections <= 1 || clipText.isEmpty()) {
            editor->paste();
            return;
        }
        // Split by any EOL variant so we handle CRLF / LF / CR uniformly.
        const QStringList lines = clipText.split(QRegularExpression(QStringLiteral("\\r\\n|\\r|\\n")));
        if (lines.size() != numSelections) {
            // Fragment count doesn't match caret count — use normal paste.
            editor->paste();
            return;
        }
        // Replace each selection with the corresponding fragment.
        // Work from the last selection to the first so earlier positions
        // remain valid after each insertion.
        const UndoAction ua(editor);
        for (int i = numSelections - 1; i >= 0; --i) {
            const int start = editor->selectionNStart(i);
            const int end   = editor->selectionNEnd(i);
            const QByteArray bytes = lines[i].toUtf8();
            editor->setTargetRange(start, end);
            editor->replaceTarget(bytes.size(), bytes.constData());
        }
        // Clear multi-selection: place the caret after the last inserted text.
        editor->clearSelections();
    });
    connectEditorAction(ui->actionSelectAll, &ScintillaNext::selectAll);
    connect(ui->actionSelectNext, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();

        editor->setSearchFlags(SCFIND_NONE);
        editor->targetWholeDocument();
        editor->multipleSelectAddNext();
    });
    connect(ui->actionCopyFullPath, &QAction::triggered, this, [this]() {
        auto editor = currentEditor();
        if (editor->isFile()) {
            QApplication::clipboard()->setText(editor->getFilePath());
        }
    });
    connect(ui->actionCopyFileName, &QAction::triggered, this, [this]() {
        QApplication::clipboard()->setText(currentEditor()->getName());
    });
    connect(ui->actionCopyFileDirectory, &QAction::triggered, this, [this]() {
        auto editor = currentEditor();
        if (editor->isFile()) {
            QApplication::clipboard()->setText(editor->getPath());
        }
    });

    connect(ui->actionCopyAsHtml, &QAction::triggered, this, [this]() {
        HtmlConverter html(currentEditor());
        copyAsFormat(&html, "text/html");
    });

    connect(ui->actionCopyAsRtf, &QAction::triggered, this, [this]() {
        RtfConverter rtf(currentEditor());
        copyAsFormat(&rtf, "Rich Text Format");
    });

    connectEditorAction(ui->actionIncreaseIndent, &ScintillaNext::tab);
    connectEditorAction(ui->actionDecreaseIndent, &ScintillaNext::backTab);

    connect(ui->actionConvertTabsToSpaces, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        const int tabWidth = editor->tabWidth();
        const QString spaces = QString(tabWidth, ' ');
        Finder f(editor);
        const UndoAction ua(editor);
        f.setSearchText(QStringLiteral("\t"));
        f.setSearchFlags(0);
        f.replaceAll(spaces);
    });

    connect(ui->actionConvertSpacesToTabs, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        const int tabWidth = editor->tabWidth();
        const QString spaces = QString(tabWidth, ' ');
        Finder f(editor);
        const UndoAction ua(editor);
        f.setSearchText(spaces);
        f.setSearchFlags(0);
        f.replaceAll(QStringLiteral("\t"));
    });

    connect(ui->actionConvertLeadingSpacesToTabs, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        const int tabWidth = editor->tabWidth();
        const QString spaces = QString(tabWidth, ' ');
        const UndoAction ua(editor);

        const int lineCount = editor->lineCount();
        for (int line = 0; line < lineCount; ++line) {
            const int lineStart = editor->positionFromLine(line);
            const int lineEnd   = editor->lineEndPosition(line);
            if (lineStart == lineEnd)
                continue;

            int pos = lineStart;
            while (pos < lineEnd) {
                const QByteArray ch = editor->textRange(pos, pos + 1);
                if (ch != " ")
                    break;
                ++pos;
            }
            const int leadingSpaces = pos - lineStart;
            if (leadingSpaces < tabWidth)
                continue;

            const int fullTabs  = leadingSpaces / tabWidth;
            const int remainder = leadingSpaces % tabWidth;
            const QByteArray replacement = QByteArray(fullTabs, '\t') + QByteArray(remainder, ' ');
            const QByteArray oldIndent = editor->textRange(lineStart, lineStart + leadingSpaces);
            if (oldIndent == replacement)
                continue;

            editor->setTargetRange(lineStart, lineStart + leadingSpaces);
            editor->replaceTarget(replacement.size(), replacement.constData());
        }
    });

    connect(ui->actionTrimLeadingWhitespace, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        const UndoAction ua(editor);
        const int lineCount = editor->lineCount();
        for (int line = 0; line < lineCount; ++line) {
            const int lineStart = editor->positionFromLine(line);
            const int lineEnd   = editor->lineEndPosition(line);
            int pos = lineStart;
            while (pos < lineEnd) {
                const char ch = static_cast<char>(editor->charAt(pos));
                if (ch != ' ' && ch != '\t')
                    break;
                ++pos;
            }
            if (pos == lineStart) continue;
            editor->setTargetRange(lineStart, pos);
            editor->replaceTarget(0, "");
        }
    });

    connect(ui->actionTrimTrailingWhitespace, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        const UndoAction ua(editor);
        const int lineCount = editor->lineCount();
        for (int line = 0; line < lineCount; ++line) {
            const int lineStart = editor->positionFromLine(line);
            const int lineEnd   = editor->lineEndPosition(line);
            int pos = lineEnd;
            while (pos > lineStart) {
                const char ch = static_cast<char>(editor->charAt(pos - 1));
                if (ch != ' ' && ch != '\t')
                    break;
                --pos;
            }
            if (pos == lineEnd) continue;
            editor->setTargetRange(pos, lineEnd);
            editor->replaceTarget(0, "");
        }
    });

    addAction(ui->actionToggleOverType);
    connect(ui->actionToggleOverType, &QAction::triggered, this, [this]() {
        currentEditor()->editToggleOvertype();
        ui->statusBar->refresh(currentEditor());
    });

    SearchResultsDock *srDock = new SearchResultsDock(this);
    addDockWidget(Qt::BottomDockWidgetArea, srDock);
    srDock->toggleViewAction()->setShortcut(Qt::Key_F7);
    ui->menuView->addAction(srDock->toggleViewAction());

    connect(srDock, &SearchResultsDock::searchResultActivated, this, [=, this](ScintillaNext *editor, int lineNumber, int startPositionFromBeginning, int endPositionFromBeginning) {
        dockedEditor->switchToEditor(editor);

        int linePos = editor->positionFromLine(lineNumber);
        editor->goToRange({linePos + startPositionFromBeginning, linePos + endPositionFromBeginning});
        editor->verticalCentreCaret();

        editor->grabFocus();
    });

    connect(ui->actionFind, &QAction::triggered, this, [this]() {
        showFindReplaceDialog(FindReplaceDialog::FIND_TAB);
    });

    connect(ui->actionFindNext, &QAction::triggered, this, [this]() {
        FindReplaceDialog *f = findChild<FindReplaceDialog *>(QString(), Qt::FindDirectChildrenOnly);

        if (f) {
            f->performNextSearch();
        }
    });

    connect(ui->actionFindPrevious, &QAction::triggered, this, [this]() {
        FindReplaceDialog *f = findChild<FindReplaceDialog *>(QString(), Qt::FindDirectChildrenOnly);

        if (f) {
            f->performPrevSearch();
        }
    });

    connect(ui->actionQuickFind, &QAction::triggered, this, [this]() {
        QuickFindWidget *quickFind = findChild<QuickFindWidget *>(QString(), Qt::FindDirectChildrenOnly);

        if (quickFind == Q_NULLPTR) {
            quickFind = new QuickFindWidget(this);
        }

        quickFind->setEditor(currentEditor());
        quickFind->setFocus();
        quickFind->show();
    });

    connect(ui->actionReplace, &QAction::triggered, this, [this]() {
        showFindReplaceDialog(FindReplaceDialog::REPLACE_TAB);
    });

    connect(ui->actionSearchAndBookmark, &QAction::triggered, this, [this]() {
        showFindReplaceDialog(FindReplaceDialog::MARK_TAB);
    });

    connect(ui->actionGoToLine, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        const int currentLine = editor->lineFromPosition(editor->currentPos()) + 1;
        const int maxLine = editor->lineCount();
        bool ok;

        QInputDialog d = QInputDialog(this);
        Qt::WindowFlags flags = d.windowFlags() & ~Qt::WindowContextHelpButtonHint;
        int lineToGoTo = d.getInt(this, tr("Go to line"), tr("Line Number (1 - %1)").arg(maxLine), currentLine, 1, maxLine, 1, &ok, flags);

        if (ok) {
            editor->ensureVisible(lineToGoTo - 1);
            editor->gotoLine(lineToGoTo - 1);
            editor->verticalCentreCaret();
        }
    });

    // Style all actions that have a MarkerNumber and interpret that as the color needed
    MarkerAppDecorator *markerAppDecorator = app->findChild<MarkerAppDecorator*>(QString(), Qt::FindDirectChildrenOnly);
    for (QAction* action : findChildren<QAction*>()) {
        if (action->property("MarkerNumber").isValid()) {
            int markerNumber = action->property("MarkerNumber").toInt();
            action->setIcon(ActionUtils::createSolidIcon(markerAppDecorator->markerColor(markerNumber)));
        }
    }

    auto mark_callback = [=, this]() {
        MarkerAppDecorator *markerAppDecorator = app->findChild<MarkerAppDecorator*>(QString(), Qt::FindDirectChildrenOnly);

        if (markerAppDecorator && markerAppDecorator->isEnabled()) {
            if (sender()->property("MarkerNumber").isValid()) {
                ScintillaNext *editor = currentEditor();
                markerAppDecorator->mark(editor, sender()->property("MarkerNumber").toInt());
            }
        }
    };

    auto clear_mark_callback = [=, this]() {
        MarkerAppDecorator *markerAppDecorator = app->findChild<MarkerAppDecorator*>(QString(), Qt::FindDirectChildrenOnly);

        if (markerAppDecorator && markerAppDecorator->isEnabled()) {
            if (sender()->property("MarkerNumber").isValid()) {
                ScintillaNext *editor = currentEditor();
                markerAppDecorator->clear(editor, sender()->property("MarkerNumber").toInt());
            }
        }
    };

    connect(ui->actionMarkStyle1, &QAction::triggered, this, mark_callback);
    connect(ui->actionMarkStyle2, &QAction::triggered, this, mark_callback);
    connect(ui->actionMarkStyle3, &QAction::triggered, this, mark_callback);

    connect(ui->actionClearStyle1, &QAction::triggered, this, clear_mark_callback);
    connect(ui->actionClearStyle2, &QAction::triggered, this, clear_mark_callback);
    connect(ui->actionClearStyle3, &QAction::triggered, this, clear_mark_callback);

    connect(ui->actionClearAllStyles, &QAction::triggered, this, [=, this]() {
        MarkerAppDecorator *markerAppDecorator = app->findChild<MarkerAppDecorator*>(QString(), Qt::FindDirectChildrenOnly);

        if (markerAppDecorator && markerAppDecorator->isEnabled()) {
            markerAppDecorator->clearAll(currentEditor());
        }
    });

    // Copy the text of every range marked with a given style (color) to the clipboard,
    // one entry per line, in the order the ranges appear in the document.
    auto copy_marked_callback = [=, this]() {
        MarkerAppDecorator *markerAppDecorator = app->findChild<MarkerAppDecorator*>(QString(), Qt::FindDirectChildrenOnly);

        if (markerAppDecorator && markerAppDecorator->isEnabled()) {
            if (sender()->property("MarkerNumber").isValid()) {
                ScintillaNext *editor = currentEditor();
                const QStringList marked = markerAppDecorator->markedText(editor, sender()->property("MarkerNumber").toInt());

                if (!marked.isEmpty()) {
                    QApplication::clipboard()->setText(marked.join('\n'));
                }
            }
        }
    };

    connect(ui->actionCopyMarkedStyle1, &QAction::triggered, this, copy_marked_callback);
    connect(ui->actionCopyMarkedStyle2, &QAction::triggered, this, copy_marked_callback);
    connect(ui->actionCopyMarkedStyle3, &QAction::triggered, this, copy_marked_callback);

    // Copy everything marked with any of the three styles, in document order
    connect(ui->actionCopyAllMarkedStyles, &QAction::triggered, this, [=, this]() {
        MarkerAppDecorator *markerAppDecorator = app->findChild<MarkerAppDecorator*>(QString(), Qt::FindDirectChildrenOnly);

        if (!markerAppDecorator || !markerAppDecorator->isEnabled()) {
            return;
        }

        ScintillaNext *editor = currentEditor();

        // Merge the ranges from all three styles, then sort by document position
        QVector<QPair<int, int>> allRanges;
        for (int i = 0; i < 3; i++) {
            allRanges += markerAppDecorator->markedRanges(editor, i);
        }

        if (allRanges.isEmpty()) {
            return;
        }

        std::sort(allRanges.begin(), allRanges.end(), [](const QPair<int, int> &a, const QPair<int, int> &b) {
            return a.first < b.first;
        });

        QStringList lines;
        for (const auto &range : allRanges) {
            lines.append(QString::fromUtf8(editor->get_text_range(range.first, range.second)));
        }

        QApplication::clipboard()->setText(lines.join('\n'));
    });

    connect(ui->actionToggleBookmark, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        BookMarkDecorator *bookMarkDecorator = editor->findChild<BookMarkDecorator*>(QString(), Qt::FindDirectChildrenOnly);

        if (bookMarkDecorator && bookMarkDecorator->isEnabled()) {
            editor->forEachLineInSelection(editor->mainSelection(), [&](int line) {
                bookMarkDecorator->toggleBookmark(line);
            });
        }
    });

    connect(ui->actionNextBookmark, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        BookMarkDecorator *bookMarkDecorator = editor->findChild<BookMarkDecorator*>(QString(), Qt::FindDirectChildrenOnly);

        if (bookMarkDecorator && bookMarkDecorator->isEnabled()) {
            int currentLine = editor->lineFromPosition(editor->currentPos());
            int nextBookmarkedLine = bookMarkDecorator->nextBookmarkAfter(currentLine + 1);

            if (nextBookmarkedLine != -1) {
                editor->ensureVisibleEnforcePolicy(nextBookmarkedLine);
                editor->gotoLine(nextBookmarkedLine);
            }
        }
    });

    connect(ui->actionClearBookmarks, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        BookMarkDecorator *bookMarkDecorator = editor->findChild<BookMarkDecorator*>(QString(), Qt::FindDirectChildrenOnly);

        if (bookMarkDecorator && bookMarkDecorator->isEnabled()) {
            bookMarkDecorator->clearAllBookmarks();
        }
    });

    connect(ui->actionInvertBookmarks, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        BookMarkDecorator *bookMarkDecorator = editor->findChild<BookMarkDecorator*>(QString(), Qt::FindDirectChildrenOnly);

        if (bookMarkDecorator && bookMarkDecorator->isEnabled()) {
            for (int line = 0; line < editor->lineCount(); line++) {
                bookMarkDecorator->toggleBookmark(line);
            }
        }
    });

    connect(ui->actionPreviousBookmark, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        BookMarkDecorator *bookMarkDecorator = editor->findChild<BookMarkDecorator*>(QString(), Qt::FindDirectChildrenOnly);

        if (bookMarkDecorator && bookMarkDecorator->isEnabled()) {
            int currentLine = editor->lineFromPosition(editor->currentPos());
            int prevBookmarkedLine = bookMarkDecorator->previousBookMarkBefore(currentLine - 1);

            if (prevBookmarkedLine != -1) {
                editor->ensureVisibleEnforcePolicy(prevBookmarkedLine);
                editor->gotoLine(prevBookmarkedLine);
            }
        }
    });

    connect(ui->actionCutBookmarkedLines, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        BookMarkDecorator *bookMarkDecorator = editor->findChild<BookMarkDecorator*>(QString(), Qt::FindDirectChildrenOnly);

        if (bookMarkDecorator && bookMarkDecorator->isEnabled()) {
            QString s = bookMarkDecorator->cutBookMarkedLines();

            if (!s.isEmpty()) {
                QApplication::clipboard()->setText(s);
            }
        }
    });

    connect(ui->actionCopyBookmarkedLines, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        BookMarkDecorator *bookMarkDecorator = editor->findChild<BookMarkDecorator*>(QString(), Qt::FindDirectChildrenOnly);

        if (bookMarkDecorator && bookMarkDecorator->isEnabled()) {
            QString s = bookMarkDecorator->copyBookMarkedLines();

            if (!s.isEmpty()) {
                QApplication::clipboard()->setText(s);
            }
        }
    });

    connect(ui->actionDeleteBookmarkedLines, &QAction::triggered, this, [this]() {
        ScintillaNext *editor = currentEditor();
        BookMarkDecorator *bookMarkDecorator = editor->findChild<BookMarkDecorator*>(QString(), Qt::FindDirectChildrenOnly);

        if (bookMarkDecorator && bookMarkDecorator->isEnabled()) {
            bookMarkDecorator->deleteBookMarkedLines();
        }
    });


    // The action needs added to the window so it can be triggered via the keyboard
    addAction(ui->actionNextTab);
    ui->actionNextTab->setShortcuts(ui->actionNextTab->shortcuts() << QKeySequence(Qt::CTRL | Qt::Key_PageDown));
    recordDefaultShortcut(ui->actionNextTab);
    connect(ui->actionNextTab, &QAction::triggered, this, [this]() {
        int index = dockedEditor->currentDockArea()->currentIndex();
        int total = dockedEditor->currentDockArea()->dockWidgetsCount();

        index++;
        dockedEditor->currentDockArea()->setCurrentIndex(index < total ? index : 0);
    });

    // The action needs added to the window so it can be triggered via the keyboard
    addAction(ui->actionPreviousTab);
    ui->actionPreviousTab->setShortcuts(ui->actionPreviousTab->shortcuts() << QKeySequence(Qt::CTRL | Qt::Key_PageUp));
    recordDefaultShortcut(ui->actionPreviousTab);
    connect(ui->actionPreviousTab, &QAction::triggered, this, [this]() {
        int index = dockedEditor->currentDockArea()->currentIndex();
        int total = dockedEditor->currentDockArea()->dockWidgetsCount();

        index--;
        dockedEditor->currentDockArea()->setCurrentIndex(index >= 0 ? index : total - 1);
    });

    ui->pushExitFullScreen->setParent(this); // This is important
    ui->pushExitFullScreen->setVisible(false);
    connect(ui->pushExitFullScreen, &QPushButton::clicked, ui->actionFullScreen, &QAction::trigger);
    connect(ui->actionFullScreen, &QAction::triggered, this, [this](bool b) {
        static bool wasMaximized;

        if (b) {
            // NOTE: don't hide() these as it will cancel their actions they hold
            ui->menuBar->setMaximumHeight(0);
            ui->mainToolBar->setMaximumHeight(0);

            wasMaximized = isMaximized();
            if (wasMaximized) {
                // By default when calling showMaximized() from a full screen state, the window will resize
                // to its "normal" size and then immediately resize to the "maximized" size which is very ugly.
                // By calling setGeometry() to the size of the screen, it at least alleviates the ugly animation
                // going from: fullscreen -> small "normal" size -> full size of screen
                setGeometry(screen()->availableGeometry());
            }

            showFullScreen();

            ui->pushExitFullScreen->setGeometry(width() - 20, 0, 20, 20);
            ui->pushExitFullScreen->show();
            ui->pushExitFullScreen->raise();
        }
        else {
            ui->menuBar->setMaximumHeight(QWIDGETSIZE_MAX);
            ui->mainToolBar->setMaximumHeight(QWIDGETSIZE_MAX);

            if (wasMaximized)
                showMaximized();
            else
                showNormal();

            ui->pushExitFullScreen->hide();
        }
    });


    // Show All Characters is just a short cut to toggle whitespace and EOL on
    ui->actionShowAllCharacters->setChecked(app->getSettings()->showWhitespace() && app->getSettings()->showEndOfLine());
    connect(ui->actionShowAllCharacters, &QAction::triggered, app->getSettings(), &ApplicationSettings::setShowWhitespace);
    connect(ui->actionShowAllCharacters, &QAction::triggered, app->getSettings(), &ApplicationSettings::setShowEndOfLine);

    // Show White Space
    ui->actionShowWhitespace->setChecked(app->getSettings()->showWhitespace());
    connect(app->getSettings(), &ApplicationSettings::showWhitespaceChanged, ui->actionShowWhitespace, &QAction::setChecked);
    connect(ui->actionShowWhitespace, &QAction::toggled, app->getSettings(), &ApplicationSettings::setShowWhitespace);
    // Update the "Show All Character" action
    connect(ui->actionShowWhitespace, &QAction::toggled, this, [this](bool b) {
        ui->actionShowAllCharacters->setChecked(b && ui->actionShowEndofLine->isChecked());
    });

    // Show EOL
    ui->actionShowEndofLine->setChecked(app->getSettings()->showEndOfLine());
    connect(app->getSettings(), &ApplicationSettings::showEndOfLineChanged, ui->actionShowEndofLine, &QAction::setChecked);
    connect(ui->actionShowEndofLine, &QAction::toggled, app->getSettings(), &ApplicationSettings::setShowEndOfLine);
    // Update the "Show All Character" action
    connect(ui->actionShowEndofLine, &QAction::toggled, this, [this](bool b) {
        ui->actionShowAllCharacters->setChecked(b && ui->actionShowWhitespace->isChecked());
    });

    // Show Wrap Symbol
    ui->actionShowWrapSymbol->setChecked(app->getSettings()->showWrapSymbol());
    connect(app->getSettings(), &ApplicationSettings::showWrapSymbolChanged, ui->actionShowWrapSymbol, &QAction::setChecked);
    connect(ui->actionShowWrapSymbol, &QAction::toggled, app->getSettings(), &ApplicationSettings::setShowWrapSymbol);

    // Show Indentation Guide
    ui->actionShowIndentGuide->setChecked(app->getSettings()->showIndentGuide());
    connect(app->getSettings(), &ApplicationSettings::showIndentGuideChanged, ui->actionShowIndentGuide, &QAction::setChecked);
    connect(ui->actionShowIndentGuide, &QAction::toggled, app->getSettings(), &ApplicationSettings::setShowIndentGuide);

    // Word Wrap
    ui->actionWordWrap->setChecked(app->getSettings()->wordWrap());
    connect(app->getSettings(), &ApplicationSettings::wordWrapChanged, ui->actionWordWrap, &QAction::setChecked);
    connect(ui->actionWordWrap, &QAction::toggled, app->getSettings(), &ApplicationSettings::setWordWrap);

    // Zooming controls all editors simulaneously
    connect(ui->actionZoomIn, &QAction::triggered, this, [this]() {
        for (ScintillaNext *editor : editors()) {
            editor->zoomIn();
        }
        zoomLevel = currentEditor()->zoom();

        showEditorZoomLevelIndicator();
    });
    connect(ui->actionZoomOut, &QAction::triggered, this, [this]() {
        for (ScintillaNext *editor : editors()) {
            editor->zoomOut();
        }
        zoomLevel = currentEditor()->zoom();

        showEditorZoomLevelIndicator();
    });
    connect(ui->actionZoomReset, &QAction::triggered, this, [this]() {
        for (ScintillaNext *editor : editors()) {
            editor->setZoom(0);
        }
        zoomLevel = 0;

        showEditorZoomLevelIndicator();
    });

    // Zoom watcher has detected a zoom event, so just trigger the UI action
    connect(zoomEventWatcher, &ZoomEventWatcher::zoomIn, ui->actionZoomIn, &QAction::trigger);
    connect(zoomEventWatcher, &ZoomEventWatcher::zoomOut, ui->actionZoomOut, &QAction::trigger);

    connectEditorAction(ui->actionFoldAll, &ScintillaNext::foldAll, SC_FOLDACTION_CONTRACT | SC_FOLDACTION_CONTRACT_EVERY_LEVEL);
    connectEditorAction(ui->actionUnfoldAll, &ScintillaNext::foldAll, SC_FOLDACTION_EXPAND | SC_FOLDACTION_CONTRACT_EVERY_LEVEL);

    connectEditorAction(ui->actionFoldLevel1, &ScintillaNext::foldAllLevels, 0);
    connectEditorAction(ui->actionFoldLevel2, &ScintillaNext::foldAllLevels, 1);
    connectEditorAction(ui->actionFoldLevel3, &ScintillaNext::foldAllLevels, 2);
    connectEditorAction(ui->actionFoldLevel4, &ScintillaNext::foldAllLevels, 3);
    connectEditorAction(ui->actionFoldLevel5, &ScintillaNext::foldAllLevels, 4);
    connectEditorAction(ui->actionFoldLevel6, &ScintillaNext::foldAllLevels, 5);
    connectEditorAction(ui->actionFoldLevel7, &ScintillaNext::foldAllLevels, 6);
    connectEditorAction(ui->actionFoldLevel8, &ScintillaNext::foldAllLevels, 7);
    connectEditorAction(ui->actionFoldLevel9, &ScintillaNext::foldAllLevels, 8);

    connectEditorAction(ui->actionUnfoldLevel1, &ScintillaNext::unFoldAllLevels, 0);
    connectEditorAction(ui->actionUnfoldLevel2, &ScintillaNext::unFoldAllLevels, 1);
    connectEditorAction(ui->actionUnfoldLevel3, &ScintillaNext::unFoldAllLevels, 2);
    connectEditorAction(ui->actionUnfoldLevel4, &ScintillaNext::unFoldAllLevels, 3);
    connectEditorAction(ui->actionUnfoldLevel5, &ScintillaNext::unFoldAllLevels, 4);
    connectEditorAction(ui->actionUnfoldLevel6, &ScintillaNext::unFoldAllLevels, 5);
    connectEditorAction(ui->actionUnfoldLevel7, &ScintillaNext::unFoldAllLevels, 6);
    connectEditorAction(ui->actionUnfoldLevel8, &ScintillaNext::unFoldAllLevels, 7);
    connectEditorAction(ui->actionUnfoldLevel9, &ScintillaNext::unFoldAllLevels, 8);

    languageActionGroup = new QActionGroup(this);
    languageActionGroup->setExclusive(true);

    connect(ui->actionPreferences, &QAction::triggered, this, [=, this] {
        PreferencesDialog *pd = findChild<PreferencesDialog *>(QString(), Qt::FindDirectChildrenOnly);

        if (pd == Q_NULLPTR) {
            pd = new PreferencesDialog(app->getSettings(), this);
        }

        pd->show();
        pd->raise();
        pd->activateWindow();
    });

    connect(ui->actionShortcutEditor, &QAction::triggered, this, &MainWindow::openShortcutEditor);

    // The macro manager has already loaded any saved macros, so it might have some already
    ui->actionRunMacroMultipleTimes->setEnabled(macroManager.availableMacros().size() > 0);
    ui->actionEditMacros->setEnabled(macroManager.availableMacros().size() > 0);

    connect(ui->actionMacroRecording, &QAction::triggered, this, [this](bool b) {
        if (b) {
            macroManager.startRecording(currentEditor());
        }
        else {
            macroManager.stopRecording();
        }
    });

    connect(&macroManager, &MacroManager::recordingStarted, this, [this]() {
        ui->actionMacroRecording->setText(tr("Stop Recording"));

        // A macro is being recorded so disable some macro options
        ui->actionPlayback->setEnabled(false);
        ui->actionRunMacroMultipleTimes->setEnabled(false);
        ui->actionSaveCurrentRecordedMacro->setEnabled(false);
    });

    connect(&macroManager, &MacroManager::recordingStopped, this, [this]() {
        ui->actionMacroRecording->setText(tr("Start Recording"));

        // Only enable these if the macro manager recorded a valid macro
        ui->actionPlayback->setEnabled(macroManager.hasCurrentUnsavedMacro());
        ui->actionSaveCurrentRecordedMacro->setEnabled(macroManager.hasCurrentUnsavedMacro());

        // The macro manager might have other macros
        ui->actionRunMacroMultipleTimes->setEnabled(macroManager.availableMacros().size() > 0 || macroManager.hasCurrentUnsavedMacro());
    });

    connect(ui->actionPlayback, &QAction::triggered, this, [this]() {
        macroManager.replayCurrentMacro(currentEditor());
    });

    connect(ui->actionSaveCurrentRecordedMacro, &QAction::triggered, this, [=, this]() {
        MacroSaveDialog macroSaveDialog;

        macroSaveDialog.show();
        macroSaveDialog.raise();
        macroSaveDialog.activateWindow();

        if (macroSaveDialog.exec() == QDialog::Accepted) {
            // We have at least 1 saved macro at this point
            ui->actionEditMacros->setEnabled(true);

            // The macro has been saved so disable save option
            ui->actionSaveCurrentRecordedMacro->setEnabled(false);

            // TODO: does the macro name already exist? Make the user retry

            macroManager.saveCurrentMacro(macroSaveDialog.getName());

            // TODO handle shortcuts
            if (!macroSaveDialog.getShortcut().isEmpty()) {
                // do something with msd.getShortcut().isEmpty()
            }
        }
    });

    connect(ui->actionRunMacroMultipleTimes, &QAction::triggered, this, [this]() {
        MacroRunDialog *macroRunDialog = findChild<MacroRunDialog *>(QString(), Qt::FindDirectChildrenOnly);

        if (macroRunDialog == Q_NULLPTR) {
            macroRunDialog = new MacroRunDialog(this, &macroManager);

            connect(macroRunDialog, &MacroRunDialog::execute, this, [this](Macro *macro, int times) {
                if (times > 0)
                    macro->replay(currentEditor(), times);
                else if (times == -1)
                    macro->replayTillEndOfFile(currentEditor());
            });
        }

        macroRunDialog->show();
        macroRunDialog->raise();
        macroRunDialog->activateWindow();
    });

    connect(ui->actionEditMacros, &QAction::triggered, this, [this]() {
        MacroEditorDialog med(this, &macroManager);

        med.show();
        med.raise();
        med.activateWindow();

        med.exec();

        ui->actionEditMacros->setEnabled(macroManager.availableMacros().size() > 0);
    });

    connect(ui->menuMacro, &QMenu::aboutToShow, this, [this]() {
        // NOTE: its unfortunate that this has to be hard coded, but there's no way
        // to easily determine what should or shouldn't be there
        while (ui->menuMacro->actions().size() > 6) {
            delete ui->menuMacro->actions().takeLast();
        }

        for (const Macro *m : macroManager.availableMacros()) {
            ui->menuMacro->addAction(m->getName(), [=, this]() { m->replay(currentEditor()); });
        }
    });

    ui->actionAboutQt->setIcon(QPixmap(QLatin1String(":/qt-project.org/qmessagebox/images/qtlogo-64.png")));
    connect(ui->actionAboutQt, &QAction::triggered, &QApplication::aboutQt);

    ui->actionAboutNotepadNext->setShortcut(QKeySequence::HelpContents);
    recordDefaultShortcut(ui->actionAboutNotepadNext);
    connect(ui->actionAboutNotepadNext, &QAction::triggered, this, [this]() {
        QMessageBox::about(this, QString(),
                            QStringLiteral("<h3>%1 v%2 %3</h3>"
                                    "<p>%4</p>"
                                    "<p><a href=\\\"https://github.com/rosmapo/mmedit\\\">mmedit Home Page</a></p>"
                                    R"(<p>This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.</p> <p>This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.</p> <p>You should have received a copy of the GNU General Public License along with this program. If not, see &lt;<a href="https://www.gnu.org/licenses/">https://www.gnu.org/licenses/</a>&gt;.</p>)")
                                .arg(QApplication::applicationDisplayName(), APP_VERSION, APP_DISTRIBUTION, QStringLiteral(APP_COPYRIGHT).toHtmlEscaped()));
    });

    // ── Color Picker (Tools menu) ────────────────────────────────────────────
    auto *colorPickerDlg = new ColorPickerDialog(this);
    // Keep the dialog's editor reference in sync with the active editor.
    connect(this, &MainWindow::editorActivated, colorPickerDlg,
            &ColorPickerDialog::setEditor);
    auto *wordCountDlg = new WordCountDialog(this);
    connect(ui->actionWordCount, &QAction::triggered, this, [=, this]() {
        wordCountDlg->setEditor(currentEditor());
        wordCountDlg->show();
        wordCountDlg->raise();
        wordCountDlg->activateWindow();
    });

    connect(ui->actionInsertDateTime, &QAction::triggered, this, [=, this]() {
        ScintillaNext *editor = currentEditor();
        if (!editor) return;
        const QString text = QLocale().toString(QDateTime::currentDateTime(), app->getSettings()->dateTimeFormat());
        editor->replaceSel(text.toUtf8().constData());
    });

    connect(ui->actionColorPicker, &QAction::triggered, this, [=, this]() {
        colorPickerDlg->setEditor(currentEditor());
        colorPickerDlg->show();
        colorPickerDlg->raise();
        colorPickerDlg->activateWindow();
    });

    connect(ui->actionHexViewer, &QAction::triggered, this, [=, this]() {
        ScintillaNext *editor = currentEditor();
        if (!editor) return;

        // Read raw bytes
        QByteArray rawData;
        if (editor->isFile()) {
            QFile f(editor->getFilePath());
            if (f.open(QIODevice::ReadOnly)) { rawData = f.readAll(); f.close(); }
        } else {
            int len = (int)editor->textLength();
            rawData = editor->getText(len + 1).left(len);
        }

        // Build hex dump
        QString hexName = QString("[HEX] %1").arg(editor->getName());
        QString dump;
        dump.reserve(rawData.size() * 5);

        // Header: charset + BOM info
        QString bomInfo;
        if (rawData.startsWith(QByteArray::fromHex("EFBBBF")))
            bomInfo = "UTF-8 BOM (EF BB BF)";
        else if (rawData.startsWith(QByteArray::fromHex("FFFE")))
            bomInfo = "UTF-16 LE BOM (FF FE)";
        else if (rawData.startsWith(QByteArray::fromHex("FEFF")))
            bomInfo = "UTF-16 BE BOM (FE FF)";
        else
            bomInfo = "No BOM";
        dump += QString("# File: %1\n# Charset: %2  |  %3  |  %4 bytes\n#\n")
                    .arg(editor->isFile() ? editor->getFilePath() : editor->getName())
                    .arg(editor->charset())
                    .arg(bomInfo)
                    .arg(rawData.size());

        const int bytesPerRow = 16;
        for (int i = 0; i < rawData.size(); i += bytesPerRow) {
            dump += QString("%1  ").arg(i, 8, 16, QChar('0'));
            int rowLen = qMin(bytesPerRow, rawData.size() - i);
            for (int j = 0; j < 8; ++j)
                dump += j < rowLen ? QString("%1 ").arg((uchar)rawData[i+j], 2, 16, QChar('0')) : "   ";
            dump += " ";
            for (int j = 8; j < bytesPerRow; ++j)
                dump += j < rowLen ? QString("%1 ").arg((uchar)rawData[i+j], 2, 16, QChar('0')) : "   ";
            dump += " |";
            for (int j = 0; j < rowLen; ++j) {
                uchar c = (uchar)rawData[i+j];
                dump += (c >= 32 && c < 127) ? QChar(c) : QChar('.');
            }
            dump += "|\n";
        }

        // Open in new tab
        ScintillaNext *hexEditor = app->getEditorManager()->createEditor(hexName);
        hexEditor->setReadOnly(false);
        hexEditor->appendText(dump.toUtf8().size(), dump.toUtf8().constData());
        hexEditor->setSavePoint();
        hexEditor->setReadOnly(true);
        hexEditor->gotoPos(0);
    });

    connect(ui->actionDebugInfo, &QAction::triggered, this, [=, this]() {
        QMessageBox mb(QMessageBox::Information, tr("Debug Info"), app->debugInfo().join('\n'), QMessageBox::Ok, this);

        mb.setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont).family());
        mb.setTextInteractionFlags(Qt::TextSelectableByMouse);

        mb.exec();
    });

    tabsQuickActionsBar = new TabsQuickActionsBar(TabsQuickActionsBar::ShowTabsMenu, ui->menuBar);
    ui->menuBar->setCornerWidget(tabsQuickActionsBar, Qt::TopRightCorner);
    connect(tabsQuickActionsBar, &TabsQuickActionsBar::createNewTabClicked, this, &MainWindow::newFile);
    connect(tabsQuickActionsBar, &TabsQuickActionsBar::closeCurrentTabClicked, this, &MainWindow::closeCurrentFile);
    connect(tabsQuickActionsBar, &TabsQuickActionsBar::tabsMenuAboutToShow, this, [this](QMenu *editorsMenu) {
        const auto editorsList = editors();

        editorsMenu->clear();

        for (const auto editor : editorsList) {
            const auto iconPath = editor->isSavedToDisk() ? ":/icons/saved.png" : ":/icons/unsaved.png";
            const auto action = editorsMenu->addAction(QIcon(iconPath), editor->getName());

            if (editor->isActiveWindow()) {
                auto font = action->font();
                font.setBold(true);
                action->setFont(font);
            }

            connect(action, &QAction::triggered, this, [this, editor]() { switchToEditor(editor); });
        }
    });

#ifdef Q_OS_WIN
    connect(ui->actionShowInExplorer, &QAction::triggered, this, [this]() {
        QString filePath = QDir::toNativeSeparators(currentEditor()->getFileInfo().canonicalFilePath());
        QStringList arguments = {"/select,", filePath};
        QProcess::startDetached("explorer", arguments);
    });

    QString terminalName = app->getSettings()->value("App/TerminalName", "Command Prompt").toString();
    ui->actionOpenTerminalHere->setText(ui->actionOpenTerminalHere->text().arg(terminalName));

    connect(ui->actionOpenTerminalHere, &QAction::triggered, this, [=, this]() {
        QString command = app->getSettings()->value("App/TerminalCommand", "cmd").toString();
        QString filePath = QDir::toNativeSeparators(currentEditor()->getFileInfo().dir().canonicalPath());
        QStringList arguments = {"/c", "start", "/d", filePath, command};
        QProcess::startDetached("cmd", arguments);
    });
#endif

    FolderAsWorkspaceDock *fawDock = new FolderAsWorkspaceDock(this);
    fawDock->hide();
    addDockWidget(Qt::LeftDockWidgetArea, fawDock);
    fawDock->toggleViewAction()->setObjectName("actionFolderAsWorkspace");
    ui->menuView->addAction(fawDock->toggleViewAction());
    connect(fawDock, &FolderAsWorkspaceDock::fileDoubleClicked, this, &MainWindow::openFile);
    applyCustomShortcuts();

    MarkdownPreviewDock *mdPreviewDock = new MarkdownPreviewDock(this);
    mdPreviewDock->hide();
    addDockWidget(Qt::RightDockWidgetArea, mdPreviewDock);
    mdPreviewDock->toggleViewAction()->setObjectName("actionMarkdownPreview");
    ui->menuTools->addAction(mdPreviewDock->toggleViewAction());
    connect(this, &MainWindow::editorActivated, mdPreviewDock, &MarkdownPreviewDock::setEditor);

    // Spell Check
    connect(ui->actionSpellCheck, &QAction::toggled, this, [=, this](bool checked) {
        app->getSettings()->setSpellCheckEnabled(checked);
    });
    connect(app->getSettings(), &ApplicationSettings::spellCheckEnabledChanged, this, [=, this](bool enabled) {
        ui->actionSpellCheck->setChecked(enabled);
    });
    ui->actionSpellCheck->setChecked(app->getSettings()->spellCheckEnabled());

    // Change history: propagate setting changes to all already-open editors
    connect(app->getSettings(), &ApplicationSettings::showChangeHistoryChanged, this, [=, this](bool enabled) {
        for (auto *editor : editors()) {
            applyChangeHistoryToEditor(editor, enabled);
        }
    });
    connect(mdPreviewDock, &QDockWidget::visibilityChanged, mdPreviewDock, [mdPreviewDock](bool visible) {
        if (visible) mdPreviewDock->updatePreview();
    });

    FileListDock *fileListDock = new FileListDock(this);
    fileListDock->hide();
    addDockWidget(Qt::LeftDockWidgetArea, fileListDock);
    ui->menuView->addAction(fileListDock->toggleViewAction());

    // Minimap dock (right side, visible by default)
    MinimapPanel *minimapPanel = new MinimapPanel(this);
    QDockWidget *minimapDock = new QDockWidget(tr("Minimap"), this);
    minimapDock->setObjectName("MinimapDock");
    minimapDock->setWidget(minimapPanel);
    minimapDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable);
    minimapDock->setTitleBarWidget(new QWidget()); // hide title bar
    minimapDock->setMaximumWidth(130);
    minimapDock->setMinimumWidth(80);
    addDockWidget(Qt::RightDockWidgetArea, minimapDock);
    QAction *actionToggleMinimap = new QAction(tr("Toggle Minimap"), this);
	actionToggleMinimap->setObjectName("actionToggleMinimap");
	actionToggleMinimap->setCheckable(true);
	actionToggleMinimap->setChecked(!minimapDock->isHidden());
	actionToggleMinimap->setShortcut(QKeySequence(Qt::Key_F12));
	actionToggleMinimap->setShortcutContext(Qt::WindowShortcut);
	connect(actionToggleMinimap, &QAction::triggered, minimapDock, &QDockWidget::setVisible);
	connect(minimapDock, &QDockWidget::visibilityChanged, actionToggleMinimap, &QAction::setChecked);
	addAction(actionToggleMinimap);           // registruje skratku na okno
	ui->menuView->addAction(actionToggleMinimap);
	recordDefaultShortcut(actionToggleMinimap); // zapíše default pre editor skratiek

    // Connect minimap to editor switching
    connect(dockedEditor, &DockedEditor::editorActivated, this, [minimapPanel](ScintillaNext *editor) {
        minimapPanel->setEditor(editor);
    });

    // Show minimap immediately when an editor is added (e.g. on startup/session restore)
    // Opravený kód v MainWindow.cpp
	connect(dockedEditor, &DockedEditor::editorAdded, this, [minimapPanel, this](ScintillaNext *editor) {
		// Okamžité záložné priradenie: zabezpečí, že minimapa nezostane
		// s neplatným pointerom na vymazaný editor.
		minimapPanel->setEditor(editor);

		// Ak už DockedEditor eviduje aktuálny editor, prepíšeme ho ním
		// (užitočné napr. pri hromadnom načítavaní relácie s viacerými súbormi).
		if (currentEditor()) {
			minimapPanel->setEditor(currentEditor());
		}
	});

    connect(app->getSettings(), &ApplicationSettings::showMenuBarChanged, this, [this](bool showMenuBar) {
        // Don't 'hide' it, else the actions won't be enabled
        ui->menuBar->setMaximumHeight(showMenuBar ? QWIDGETSIZE_MAX : 0);
    });
    ui->actionToggleMenuBar->setChecked(app->getSettings()->showMenuBar());
	ui->menuBar->setMaximumHeight(app->getSettings()->showMenuBar() ? QWIDGETSIZE_MAX : 0);
    connect(app->getSettings(), &ApplicationSettings::showMenuBarChanged, this, [this](bool show) {
        ui->actionToggleMenuBar->setChecked(show);
    });
    connect(ui->actionToggleMenuBar, &QAction::triggered, this, [this, app](bool checked) {
        app->getSettings()->setShowMenuBar(checked);
    });
    connect(app->getSettings(), &ApplicationSettings::showToolBarChanged, ui->mainToolBar, &QToolBar::setVisible);
    connect(app->getSettings(), &ApplicationSettings::showStatusBarChanged, ui->statusBar, &QStatusBar::setVisible);

    ui->actionDarkMode->setChecked(app->getSettings()->darkMode());
    connect(app->getSettings(), &ApplicationSettings::darkModeChanged, this, [this, minimapPanel](bool dark) {
        ui->actionDarkMode->setChecked(dark);
        applyDarkModeToAllEditors();
        minimapPanel->refreshStyles();
    });
    connect(ui->actionDarkMode, &QAction::triggered, this, [this, app](bool checked) {
        app->getSettings()->setDarkMode(checked);
    });
    connect(ui->statusBar, &EditorInfoStatusBar::customContextMenuRequestedForEOLLabel, this, [this](const QPoint &pos){
        ui->menuEOLConversion->popup(pos);
    });

    // It seems restoreState() does not affect the status bar so set it manually
    ui->statusBar->setVisible(app->getSettings()->showStatusBar());

    setupLanguageMenu();

    applyStyleSheet();

    restoreSettings();

    initUpdateCheck();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recordDefaultShortcut(QAction *action)
{
    if (!action) return;

    const QString objName = action->objectName();
    if (objName.isEmpty()) return;

    // Mirror ShortcutEditorDialog's actionKey()/keyFromObjectName() logic so
    // the keys line up: strip a leading "action" prefix.
    const QString key = objName.startsWith(QStringLiteral("action"))
                             ? objName.mid(6)
                             : objName;
    if (key.isEmpty()) return;

    m_defaultShortcuts[key] = action->shortcut();
}

void MainWindow::captureDefaultShortcuts()
{
    for (QAction *action : findChildren<QAction *>()) {
        if (!action->objectName().startsWith(QStringLiteral("action"))) continue;
        if (action->isSeparator()) continue;

        recordDefaultShortcut(action);
    }
}

void MainWindow::applyCustomShortcuts()
{
    ApplicationSettings *settings = app->getSettings();
    settings->beginGroup("Shortcuts");

    for (const QString &actionName : settings->childKeys()) {
        QAction *action = findChild<QAction *>(QStringLiteral("action") + actionName);

        if (!action) {
            qWarning() << "CustomShortcut: Cannot find action" << actionName;
            continue;
        }

        const QVariant value = settings->value(actionName);
        if (!value.canConvert<QStringList>()) {
            qWarning() << "CustomShortcut: Invalid shortcut format for" << actionName;
            continue;
        }

        QList<QKeySequence> shortcuts;
        for (const QString &shortcutString : value.toStringList()) {
            auto sequence = QKeySequence(shortcutString);

#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
                if (sequence.count() > 0 && sequence[0].key() != Qt::Key_unknown) {
#else
                if (sequence.count() > 0 && (sequence[0] & ~Qt::KeyboardModifierMask) != Qt::Key_unknown) {
#endif
                    shortcuts.append(sequence);
                }
                else {
                    qWarning() << "CustomShortcut: Cannot create QKeySequence(" << shortcutString << ") for " << actionName;
                }
        }

        if (!shortcuts.empty()) {
            action->setShortcuts(shortcuts);
        }
    }

    settings->endGroup();
}

void MainWindow::setupLanguageMenu()
{
    qInfo(Q_FUNC_INFO);

    QStringList language_names = app->getLanguages();

    int i = 0;
    while (i < language_names.size()) {
        QList<QAction *> actions;
        int j = i;

        // Get all consecutive names that start with the same letter
        // NOTE: this loop always runs once since i == j the first time
        while (j < language_names.size() && language_names[i][0].toUpper() == language_names[j][0].toUpper()) {
            const QString key = language_names[j];
            QAction *action = new QAction(key);
            action->setCheckable(true);
            action->setData(key);
            connect(action, &QAction::triggered, this, &MainWindow::languageMenuTriggered);
            languageActionGroup->addAction(action);
            actions.append(action);

            ++j;
        }

        if (actions.size() == 1) {
            ui->menuLanguage->addActions(actions);
        }
        else {
            // Create a sub menu with the actions
            QMenu *compactMenu = new QMenu(actions[0]->text().at(0).toUpper());
            compactMenu->addActions(actions);
            ui->menuLanguage->addMenu(compactMenu);
        }
        i = j;
    }
}

ScintillaNext *MainWindow::currentEditor() const
{
    return dockedEditor->getCurrentEditor();
}

int MainWindow::editorCount() const
{
    return dockedEditor->count();
}

QVector<ScintillaNext *> MainWindow::editors() const
{
    // NOTE: this will need re-evaluated in the future.
    // So far it has been assumed 1 ScintillaNext instance is 1 DockedEditor widget instance.
    // If in the future a ScintillaNext can be cloned then the DockedEditor could return
    // the same ScintillaNext instance multiple times since 1 ScintillaNext could mean >= 1 DockedEditor widget instance
    return dockedEditor->editors();
}

void MainWindow::newFile()
{
    qInfo(Q_FUNC_INFO);

    static int count = 1;

    // NOTE: in theory need to check all editors in the editorManager to future proof this.
    // If there is another window it would need to check those too to see if New X exists. The editor
    // manager would encompass all editors

    forever {
        QString newFileName = tr("New %1").arg(count++);
        bool canUseName = true;

        for (const ScintillaNext *editor : editors()) {
            if (!editor->isFile() && editor->getName() == newFileName) {
                canUseName = false;
                break;
            }
        }

        if (canUseName) {
            ScintillaNext *editor = app->getEditorManager()->createEditor(newFileName);
            editor->grabFocus();
            break;
        }
    }
}

// One unedited, new blank document
ScintillaNext *MainWindow::getInitialEditor()
{
    if (editorCount() == 1) {
        // Use the first available editor, not currentEditor() which may be null
        // if the editor hasn't been focused yet
        ScintillaNext *editor = editors().isEmpty() ? nullptr : editors().first();

        if (!editor) {
            return Q_NULLPTR;
        }

        // If the editor:
        //   is a temporary file
        //   is a 'real' file (or a 'missing' file)
        //   can undo any actions
        //   can redo any actions
        // Then do not treat it as an 'initial editor' that can be transparently closed for the user
        if (editor->isTemporary() || editor->isFile() || editor->canUndo() || editor->canRedo()) {
            return Q_NULLPTR;
        }

        return editor;
    }

    return Q_NULLPTR;
}

void MainWindow::openFileList(const QStringList &fileNames)
{
    qInfo(Q_FUNC_INFO);

    if (fileNames.size() == 0)
        return;

    QList<ScintillaNext *> openedEditors;
    ScintillaNext *initialEditor = getInitialEditor();

    for (const QString &filePath : fileNames) {
        qInfo("%s", qUtf8Printable(filePath));

        // Search currently open editors to see if it is already open
        ScintillaNext *editor = app->getEditorManager()->getEditorByFilePath(filePath);

        if (editor == Q_NULLPTR) {
            QFileInfo fileInfo(filePath);

            if (!fileInfo.isFile()) {
                auto reply = QMessageBox::question(this, tr("Create File"), tr("<b>%1</b> does not exist. Do you want to create it?").arg(filePath));

                if (reply == QMessageBox::Yes) {
                    editor = app->getEditorManager()->createEditorFromFile(filePath, true);
                }
                else {
                    // Make sure it is not still in the recent files list still.
                    // Normally when a file is opened it is removed from the file list,
                    // but if a user doesn't want to create the file, remove it explicitly.
                    app->getRecentFilesListManager()->removeFile(filePath);
                    continue;
                }
            }
            else {
                editor = app->getEditorManager()->createEditorFromFile(filePath);
            }
        }

        if (editor) {
            openedEditors.append(editor);
        }
    }

    // If any were successful
    if (!openedEditors.empty()) {
        dockedEditor->switchToEditor(openedEditors.last());

        if (initialEditor) {
            initialEditor->close();
        }
    }

}

bool MainWindow::checkEditorsBeforeClose(const QVector<ScintillaNext *> &editors)
{
    QVector<ScintillaNext *> unsaved;
    for (auto *e : editors) {
        if (!e->isSavedToDisk()) unsaved.append(e);
    }

    if (unsaved.isEmpty()) return true;

    // Focus the user's attention on the first unsaved file
    dockedEditor->switchToEditor(unsaved.first());

    // Single point of interaction
    UserSaveAction action = promptForSave(unsaved);

    switch (action) {
        case UserSaveAction::DiscardAll:
            return true;
        case UserSaveAction::SaveAll:
            return saveAllEditors(unsaved);
        case UserSaveAction::Cancel:
        default:
            return false;
    }
}

void MainWindow::openFileDialog()
{
    const QString filter = app->getFileDialogFilter();

    QStringList fileNames = FileDialogHelpers::getOpenFileNames(this, QString(), defaultDirectoryManager->getDefaultDirectory(), filter);

    if (!fileNames.empty())
        emit fileDialogAccepted(fileNames.last());

    openFileList(fileNames);
}

void MainWindow::openFile(const QString &filePath)
{
    openFileList(QStringList() << filePath);
}

void MainWindow::openFolderAsWorkspaceDialog()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Folder as Workspace"), defaultDirectoryManager->getDefaultDirectory(), QFileDialog::ShowDirsOnly);

    setFolderAsWorkspacePath(dir);
}

void MainWindow::setFolderAsWorkspacePath(const QString &dir)
{
    if (!dir.isEmpty()) {
        FolderAsWorkspaceDock *fawDock = findChild<FolderAsWorkspaceDock *>();
        fawDock->setRootPath(dir);
        fawDock->setVisible(true);
    }
}

void MainWindow::reloadFile()
{
    auto editor = currentEditor();

    if (!editor->isFile() && !editor->isSavedToDisk()) {
        return;
    }

    const QString filePath = editor->getFilePath();
    auto reply = QMessageBox::question(this, tr("Reload File"), tr("Are you sure you want to reload <b>%1</b>? Any unsaved changes will be lost.").arg(filePath));

    if (reply == QMessageBox::Yes) {
        editor->reload();
    }
}

void MainWindow::closeCurrentFile()
{
    closeFile(currentEditor());
}

void MainWindow::closeFile(ScintillaNext *editor)
{
    if (!checkEditorsBeforeClose({editor})) {
        return;
    }

    editor->close();
    // Note: if this was the last editor, lastEditorClosed() signal from DockedEditor
    // will fire after ADS removes the widget, and handle newFile() or close() there.
}

void MainWindow::closeAllFiles()
{
    if (!checkEditorsBeforeClose(editors())) {
        return;
    }

    // Ask the manager to close the editors the dockedEditor knows about
    for (ScintillaNext *editor : editors()) {
        editor->close();
    }

    newFile();
}

void MainWindow::closeAllExceptActive()
{
    auto e = currentEditor();
    auto editor_list = editors();

    editor_list.removeOne(e);

    if (checkEditorsBeforeClose(editor_list)) {
        for (ScintillaNext *editor : editor_list) {
            editor->close();
        }
    }
}

void MainWindow::closeAllToLeft()
{
    const int index = dockedEditor->currentDockArea()->currentIndex();
    QVector<ScintillaNext *> editors;

    for (int i = 0; i < index; ++i) {
        auto editor = qobject_cast<ScintillaNext *>(dockedEditor->currentDockArea()->dockWidget(i)->widget());
        editors.append(editor);
    }

    if (checkEditorsBeforeClose(editors)) {
        for (ScintillaNext *editor : editors) {
            editor->close();
        }
    }
}

void MainWindow::closeAllToRight()
{
    const int index = dockedEditor->currentDockArea()->currentIndex();
    const int total = dockedEditor->currentDockArea()->dockWidgetsCount();
    QVector<ScintillaNext *> editors;

    for (int i = index + 1; i < total; ++i) {
        auto editor = qobject_cast<ScintillaNext *>(dockedEditor->currentDockArea()->dockWidget(i)->widget());
        editors.append(editor);
    }

    if (checkEditorsBeforeClose(editors)) {
        for (ScintillaNext *editor : editors) {
            editor->close();
        }
    }
}

bool MainWindow::saveCurrentFile()
{
    return saveFile(currentEditor());
}

bool MainWindow::saveFile(ScintillaNext *editor)
{
    if (editor->isSavedToDisk())
        return true;

    if (!editor->isFile()) {
        dockedEditor->switchToEditor(editor);
        return saveCurrentFileAsDialog();
    }

    // If file requires elevation, go straight to pkexec without trying normal save first
    if (editor->isNeedsElevation()) {
        const QString filePath = editor->getFilePath();
        return saveFileWithElevation(editor, filePath);
    }

    if (app->getSettings()->trimTrailingWhitespaceOnSave()) {
        const int lineCount = editor->lineCount();
        editor->beginUndoAction();
        for (int line = 0; line < lineCount; ++line) {
            const int lineStart = editor->positionFromLine(line);
            const int lineEnd   = editor->lineEndPosition(line);
            int pos = lineEnd;
            while (pos > lineStart) {
                const char ch = static_cast<char>(editor->charAt(pos - 1));
                if (ch != ' ' && ch != '\t')
                    break;
                --pos;
            }
            if (pos == lineEnd) continue;
            editor->setTargetRange(pos, lineEnd);
            editor->replaceTarget(0, "");
        }
        editor->endUndoAction();
    }

    QFileDevice::FileError error = editor->save();
    if (error == QFileDevice::NoError) {
        return true;
    }
    else if (error == QFileDevice::PermissionsError || error == QFileDevice::OpenError) {
        return saveFileWithElevation(editor, editor->getFilePath());
    }
    else {
        showSaveErrorMessage(editor, error);
        return false;
    }
}
bool MainWindow::saveCurrentFileAsDialog()
{
    const QString filter = app->getFileDialogFilter();
    ScintillaNext *editor = currentEditor();

    QString selectedFilter = app->getFileDialogFilterForLanguage(editor->languageName);
    QString fileName = FileDialogHelpers::getSaveFileName(this, QString(), defaultDirectoryManager->getDefaultDirectory(), filter, &selectedFilter);

    if (fileName.size() == 0) {
        return false;
    }

    emit fileDialogAccepted(fileName);

    // TODO: distinguish between the above case (i.e. the user cancels the dialog) and a failure
    // calling editor->saveAs() as it might fail.

    return saveFileAs(editor, fileName);
}

bool MainWindow::saveCurrentFileAs(const QString &fileName)
{
    return saveFileAs(currentEditor(), fileName);
}

bool MainWindow::saveFileAs(ScintillaNext *editor, const QString &fileName)
{
    qInfo("saveFileAs(%s)", qUtf8Printable(fileName));

    QFileDevice::FileError error = editor->saveAs(fileName);

    if (error == QFileDevice::NoError) {
        return true;
    }
    else {
        showSaveErrorMessage(editor, error);
        return false;
    }
}

bool MainWindow::saveCopyAsDialog()
{
    const QString filter = app->getFileDialogFilter();
    const QString languageName = currentEditor()->languageName;

    QString selectedFilter = app->getFileDialogFilterForLanguage(languageName);
    const QString fileName = FileDialogHelpers::getSaveFileName(this, tr("Save a Copy As"), defaultDirectoryManager->getDefaultDirectory(), filter, &selectedFilter);

    if (fileName.size() == 0) {
        return false;
    }

    emit fileDialogAccepted(fileName);

    return saveCopyAs(fileName);
}

bool MainWindow::saveCopyAs(const QString &fileName)
{
    auto editor = currentEditor();

    QFileDevice::FileError error = editor->saveCopyAs(fileName);

    if (error == QFileDevice::NoError) {
        return true;
    }
    else {
        showSaveErrorMessage(editor, error);
        return false;
    }
}

bool MainWindow::saveAll()
{
    return saveAllEditors(editors());
}

bool MainWindow::saveAllEditors(const QVector<ScintillaNext *> &editors)
{
    for (ScintillaNext *editor : editors) {
        if (!saveFile(editor)){
            return false;
        }
    }

    return true;
}

void MainWindow::exportAsFormat(Converter *converter, const QString &filter)
{
    const QString fileName = FileDialogHelpers::getSaveFileName(this, tr("Export As"), QString(), filter + ";;All files (*)");

    if (fileName.isEmpty()) {
        return;
    }

    QFile f(fileName);

    f.open(QIODevice::WriteOnly);

    QTextStream s(&f);
    converter->convert(s);
    f.close();
}

void MainWindow::copyAsFormat(Converter *converter, const QString &mimeType)
{
    // This is not ideal as we are *assuming* the converter is currently associated with the currentEditor()
    ScintillaNext *editor = currentEditor();
    QByteArray buffer;
    QTextStream stream(&buffer);

    if (editor->selectionEmpty())
        converter->convert(stream);
    else {
        converter->convertRange(stream, editor->selectionStart(), editor->selectionEnd());
    }

    QMimeData *mimeData = new QMimeData();
    mimeData->setData(mimeType, buffer);

    QApplication::clipboard()->setMimeData(mimeData);
}

void MainWindow::renameFile()
{
    ScintillaNext *editor = currentEditor();

    if (editor->isFile()) {
        const QString filter = app->getFileDialogFilter();
        QString selectedFilter = app->getFileDialogFilterForLanguage(editor->languageName);
        QString fileName = FileDialogHelpers::getSaveFileName(this, tr("Rename"), editor->getFilePath(), filter, &selectedFilter);

        if (fileName.isEmpty()) {
            return;
        }

        emit fileDialogAccepted(fileName);

        // TODO
        // The new fileName might be to one of the existing editors.
        //auto otherEditor = app->getEditorByFilePath(fileName);

        bool renameSuccessful = editor->rename(fileName);
        Q_UNUSED(renameSuccessful)
    }
    else {
        bool ok;
        QString text = QInputDialog::getText(this, tr("Rename"), tr("Name:"), QLineEdit::Normal, editor->getName(), &ok);

        if (ok && !text.isEmpty()) {
            editor->setName(text);
        }
    }
}

void MainWindow::moveCurrentFileToTrash()
{
    ScintillaNext *editor = currentEditor();

    moveFileToTrash(editor);
}

void MainWindow::moveFileToTrash(ScintillaNext *editor)
{
    Q_ASSERT(editor->isFile());

    const QString filePath = editor->getFilePath();
    auto reply = QMessageBox::question(this, tr("Delete File"), tr("Are you sure you want to move <b>%1</b> to the trash?").arg(filePath));

    if (reply == QMessageBox::Yes) {
        if (editor->moveToTrash()) {
            closeCurrentFile();

            // Since the file no longer exists, specifically remove it from the recent files list
            // NOTE: filePath was captured before closeCurrentFile() because the editor pointer
            // is invalidated after close() — accessing editor->getFilePath() here would be
            // a use-after-free.
            app->getRecentFilesListManager()->removeFile(filePath);
        }
        else {
            QMessageBox::warning(this, tr("Error Deleting File"),  tr("Something went wrong deleting <b>%1</b>?").arg(filePath));
        }
    }
}

void MainWindow::print()
{
    QPrintPreviewDialog printDialog(this, Qt::Window);
    EditorPrintPreviewRenderer renderer(currentEditor());

    connect(&printDialog, &QPrintPreviewDialog::paintRequested, &renderer, &EditorPrintPreviewRenderer::render);

    // TODO: load/save the page layout that was used and reload it next time
    //preview.printer()->setPageLayout( /* todo */ );

    printDialog.printer()->setPageMargins(QMarginsF(.5, .5, .5, .5), QPageLayout::Inch);

    connect(&printDialog, &QPrintPreviewDialog::accepted, this, [&]() {
        qInfo() << printDialog.printer()->pageLayout();
    });

    printDialog.exec();
}

void MainWindow::convertEOLs(int eolMode)
{
    ScintillaNext *editor = currentEditor();

    // TODO: does convertEOLs trigger SCN_MODIFIED notifications? If so can these be turned off to increase performance?
    editor->convertEOLs(eolMode);
    editor->setEOLMode(eolMode);

    updateEOLBasedUi(editor);

    // There's no simple Scintilla notification that the EOL mode has changed
    // So tell the status bar to refresh its info
    ui->statusBar->refresh(editor);
}

void MainWindow::showFindReplaceDialog(int index)
{
    ScintillaNext *editor = currentEditor();
    FindReplaceDialog *frd = findChild<FindReplaceDialog *>(QString(), Qt::FindDirectChildrenOnly);

    if (frd == Q_NULLPTR) {
        frd = new FindReplaceDialog(determineSearchResultsHandler(), this);
    }
    else {
        frd->setSearchResultsHandler(determineSearchResultsHandler());
    }

    // TODO: if dockedEditor::editorActivated() is fired, or if the editor get closed
    // the FindReplaceDialog's editor pointer needs updated...

    // Get any selected text
    if (!editor->selectionEmpty()) {
        int selection = editor->mainSelection();
        int start = editor->selectionNStart(selection);
        int end = editor->selectionNEnd(selection);
        if (end > start) {
            auto selText = editor->get_text_range(start, end);
            frd->setFindString(QString::fromUtf8(selText));
        }
    }
    else {
        int start = editor->wordStartPosition(editor->currentPos(), true);
        int end = editor->wordEndPosition(editor->currentPos(), true);
        if (end > start) {
            editor->setSelectionStart(start);
            editor->setSelectionEnd(end);
            auto selText = editor->get_text_range(start, end);
            frd->setFindString(QString::fromUtf8(selText));
        }
    }

    frd->setTab(index);
    frd->show();
    frd->raise();
    frd->activateWindow();
}

void MainWindow::updateFileStatusBasedUi(ScintillaNext *editor)
{
    qInfo(Q_FUNC_INFO);

    bool isFile = editor->isFile();
    QString fileName;

    if (isFile) {
        fileName = editor->getFilePath();
    }
    else {
        fileName = editor->getName();
    }

    QString title = QStringLiteral("[*]%1").arg(fileName);
    if (app->isRunningAsAdmin()) {
        title += QStringLiteral(" - [%1]").arg(tr("Administrator"));
    }
    setWindowTitle(title);

    ui->actionReload->setEnabled(isFile);
    ui->actionMoveToTrash->setEnabled(isFile);
    ui->actionCopyFullPath->setEnabled(isFile);
    ui->actionCopyFileDirectory->setEnabled(isFile);
    ui->actionShowInExplorer->setEnabled(isFile);
    ui->actionOpenTerminalHere->setEnabled(isFile);
}

bool MainWindow::isAnyUnsaved() const
{
    for (const ScintillaNext *editor : editors()) {
        if (!editor->isSavedToDisk()) {
            return true;
        }
    }

    return false;
}

void MainWindow::updateEOLBasedUi(ScintillaNext *editor)
{
    qInfo(Q_FUNC_INFO);

    switch(editor->eOLMode()) {
    case SC_EOL_CR:
        ui->actionMacintosh->setChecked(true);
        break;
    case SC_EOL_CRLF:
        ui->actionWindows->setChecked(true);
        break;
    case SC_EOL_LF:
        ui->actionUnix->setChecked(true);
        break;
    }
}

void MainWindow::updateSaveStatusBasedUi(ScintillaNext *editor)
{
    qInfo(Q_FUNC_INFO);

    bool isDirty = !editor->isSavedToDisk();

    setWindowModified(isDirty);

    ui->actionSave->setEnabled(isDirty);
    ui->actionSaveAll->setEnabled(isDirty || isAnyUnsaved());

    if (editorCount() == 1) {
        bool ableToClose = editor->isFile() || isDirty;
        ui->actionClose->setEnabled(ableToClose);
        ui->actionCloseAll->setEnabled(ableToClose);
    }
    else {
        ui->actionClose->setEnabled(true);
        ui->actionCloseAll->setEnabled(true);
    }
}

void MainWindow::updateEditorPositionBasedUi()
{
    const int index = dockedEditor->currentDockArea()->currentIndex();
    const int total = dockedEditor->currentDockArea()->dockWidgetsCount();

    ui->actionCloseAllToLeft->setEnabled(index > 0);
    ui->actionCloseAllToRight->setEnabled(index < (total - 1));
    ui->actionCloseAllExceptActive->setEnabled(editorCount() > 1);
}

void MainWindow::updateLanguageBasedUi(ScintillaNext *editor)
{
    qInfo(Q_FUNC_INFO);

    const QString language_name = editor->languageName;

    for (QAction *action : languageActionGroup->actions()) {
        if (action->data().toString() == language_name) {
            action->setChecked(true);

            // Found one, so we are completely done
            return;
        }
    }

    // The above loop did not set any action as checked, so make sure they are all unchecked now
    for (QAction *action : languageActionGroup->actions()) {
        if (action->isChecked()) {
            action->setChecked(false);
        }
    }
}

void MainWindow::updateGui(ScintillaNext *editor)
{
    qInfo(Q_FUNC_INFO);

    updateFileStatusBasedUi(editor);
    updateSaveStatusBasedUi(editor);
    updateEOLBasedUi(editor);
    updateEditorPositionBasedUi();
    updateSelectionBasedUi(editor);
    updateContentBasedUi(editor);
    updateLanguageBasedUi(editor);
}

void MainWindow::updateDocumentBasedUi(Scintilla::Update updated)
{
    ScintillaNext *editor = qobject_cast<ScintillaNext *>(sender());

    // TODO: what if this is triggered by an editor that is not the active editor?

    if (Scintilla::FlagSet(updated, Scintilla::Update::Content)) {
        updateSelectionBasedUi(editor);
    }

    if (Scintilla::FlagSet(updated, Scintilla::Update::Content) || Scintilla::FlagSet(updated, Scintilla::Update::Selection)) {
        updateContentBasedUi(editor);
    }
}

void MainWindow::updateSelectionBasedUi(ScintillaNext *editor)
{
    ui->actionUndo->setEnabled(editor->canUndo());
    ui->actionRedo->setEnabled(editor->canRedo());
}

void MainWindow::updateContentBasedUi(ScintillaNext *editor)
{
    bool hasAnySelections = !editor->selectionEmpty();

    ui->actionPaste->setEnabled(editor->canPaste());

    ui->actionLowerCase->setEnabled(hasAnySelections);
    ui->actionUpperCase->setEnabled(hasAnySelections);
    ui->actionTitleCase->setEnabled(hasAnySelections);
    ui->actionSentenceCase->setEnabled(hasAnySelections);
	ui->actionInvertCase->setEnabled(hasAnySelections);

    ui->actionBase64Encode->setEnabled(hasAnySelections);
    ui->actionURLEncode->setEnabled(hasAnySelections);
    ui->actionBase64Decode->setEnabled(hasAnySelections);
    ui->actionURLDecode->setEnabled(hasAnySelections);
}

void MainWindow::detectLanguage(ScintillaNext *editor)
{
    qInfo(Q_FUNC_INFO);

    if (!editor->isFile()) {
        // Default to some specific language if it is not a file.
        setLanguage(editor, "Text");
        return;
    }
    else {
        const QString language_name = app->detectLanguage(editor);

        setLanguage(editor, language_name);
    }

    return;
}

void MainWindow::activateEditor(ScintillaNext *editor)
{
    qInfo(Q_FUNC_INFO);

    checkFileForModification(editor);
    updateGui(editor);

    emit editorActivated(editor);
}

void MainWindow::applyStyleSheet()
{
    qInfo(Q_FUNC_INFO);

    QString sheet;
    QFile f(":/stylesheets/npp.css");
    qInfo() << "Loading stylesheet:" << f.fileName();

    f.open(QFile::ReadOnly);
    sheet = f.readAll();
    f.close();

    // If there is a "custom.css" file where the ini is located, load it as a style sheet addition
    QString directoryPath = QFileInfo(app->getSettings()->fileName()).absolutePath();
    QString fullPath = QDir(directoryPath).filePath("custom.css");
    if (QFile::exists(fullPath)) {
        QFile custom(fullPath);
        qInfo() << "Loading stylesheet:" << custom.fileName();

        custom.open(QFile::ReadOnly);
        sheet += custom.readAll();
        custom.close();
    }

    setStyleSheet(sheet);
}

void MainWindow::setLanguage(ScintillaNext *editor, const QString &languageName)
{
    qInfo(Q_FUNC_INFO);
    qInfo("Language Name: %s", qUtf8Printable(languageName));

    app->setEditorLanguage(editor, languageName);
}

void MainWindow::applyDarkModeToAllEditors()
{
    qInfo(Q_FUNC_INFO);

    for (auto *editor : editors()) {
        app->applyEditorTheme(editor);
    }
}

// Change history uses Scintilla's built-in SC_CHANGE_HISTORY_* support.
// We assign it its own dedicated margin (MARGIN_CHANGE_HISTORY = 4) so it
// never overlaps the bookmark margin (margin 1) used by BookMarkDecorator.
//
// Margin layout used in this project:
//   0 – line numbers
//   1 – bookmarks / markers  (BookMarkDecorator)
//   2 – fold margin
//   3 – (reserved / unused)
//   4 – change history       (this feature)
//
// SC_CHANGE_HISTORY_ENABLED  turns on tracking.
// SC_CHANGE_HISTORY_MARKERS  paints the coloured bars via Scintilla markers
//                            28–31 (SC_MARKNUM_HISTORY_*).  Those markers live
//                            in their own margin so they cannot collide with
//                            bookmarks which use markers 0–2 in margin 1.
static constexpr int MARGIN_CHANGE_HISTORY = 4;

void MainWindow::applyChangeHistoryToEditor(ScintillaNext *editor, bool enabled)
{
    if (enabled) {
        // Enable tracking + marker-based rendering
        // ENABLED|MARKERS: Scintilla tracks changes and places markers 21-24 on lines.
        // MARKERS also auto-adds history bits to margin 1's mask - we immediately
        // strip them out so margin 1 (bookmarks) never renders history bars.
        editor->setChangeHistory(SC_CHANGE_HISTORY_ENABLED | SC_CHANGE_HISTORY_MARKERS);

        // Remove history bits from margin 1 (bookmark margin) so they don't render there.
        constexpr int historyMask = (1 << SC_MARKNUM_HISTORY_REVERTED_TO_ORIGIN)
                                  | (1 << SC_MARKNUM_HISTORY_SAVED)
                                  | (1 << SC_MARKNUM_HISTORY_MODIFIED)
                                  | (1 << SC_MARKNUM_HISTORY_REVERTED_TO_MODIFIED);
        editor->setMarginMaskN(1, editor->marginMaskN(1) & ~historyMask);

        // Dedicated 4 px margin for change history bars only.
        editor->setMarginTypeN(MARGIN_CHANGE_HISTORY, SC_MARGIN_SYMBOL);
        editor->setMarginWidthN(MARGIN_CHANGE_HISTORY, 2);
        editor->setMarginMaskN(MARGIN_CHANGE_HISTORY, historyMask);

        // SC_MARK_LEFTRECT = 2 px bar on the left edge of the margin cell.
        editor->markerDefine(SC_MARKNUM_HISTORY_SAVED,                SC_MARK_LEFTRECT);
        editor->markerDefine(SC_MARKNUM_HISTORY_MODIFIED,             SC_MARK_LEFTRECT);
        editor->markerDefine(SC_MARKNUM_HISTORY_REVERTED_TO_ORIGIN,   SC_MARK_LEFTRECT);
        editor->markerDefine(SC_MARKNUM_HISTORY_REVERTED_TO_MODIFIED, SC_MARK_LEFTRECT);

        // green=saved  orange=modified(unsaved)  blue=reverted-to-origin  purple=reverted-to-modified
        editor->markerSetBack(SC_MARKNUM_HISTORY_SAVED,               0x5EC522);
        editor->markerSetBack(SC_MARKNUM_HISTORY_MODIFIED,            0x0B9EF5);
        editor->markerSetBack(SC_MARKNUM_HISTORY_REVERTED_TO_ORIGIN,  0xF6823B);
        editor->markerSetBack(SC_MARKNUM_HISTORY_REVERTED_TO_MODIFIED,0xF755A8);
    } else {
        editor->setChangeHistory(SC_CHANGE_HISTORY_DISABLED);
        editor->setMarginWidthN(MARGIN_CHANGE_HISTORY, 0);
    }
}

void MainWindow::bringWindowToForeground()
{
    qInfo(Q_FUNC_INFO);

    // There doesn't seem to be a cross platform way to force the window to the foreground

#ifdef Q_OS_WIN
    HWND hWnd = reinterpret_cast<HWND>(effectiveWinId());

    if (hWnd) {
        // I have no idea what this does, but it seems to work on Windows
        // References:
        // https://stackoverflow.com/questions/916259/win32-bring-a-window-to-top
        // https://github.com/notepad-plus-plus/notepad-plus-plus/blob/ebe7648ee1a5a560d4fc65297cbdcf08055e56e3/PowerEditor/src/winmain.cpp#L596

        HWND hCurWnd = GetForegroundWindow();
        DWORD threadId = GetCurrentThreadId();
        DWORD procId = GetWindowThreadProcessId(hCurWnd, NULL);

        int sw = 0;
        if (IsZoomed(hWnd)) {
            sw = SW_MAXIMIZE;
        } else if (IsIconic(hWnd)) {
            sw = SW_RESTORE;
        }

        if (sw != 0) {
            ShowWindow(hWnd, sw);
        }

        AttachThreadInput(procId, threadId, TRUE);
        SetForegroundWindow(hWnd);
        SetFocus(hWnd);
        AttachThreadInput(procId, threadId, FALSE);
    }
#else
    setWindowState((windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
    raise();
    activateWindow();
#endif
}

bool MainWindow::checkFileForModification(ScintillaNext *editor)
{
    qInfo(Q_FUNC_INFO);

    auto state = editor->checkFileForStateChange();

    if (state == ScintillaNext::NoChange) {
        return false;
    }
    else if (state == ScintillaNext::Modified) {
        qInfo("ScintillaNext::Modified");
        const QString filePath = editor->getFilePath();
        auto reply = QMessageBox::question(this, tr("Reload File"), tr("<b>%1</b> has been modified by another program. Do you want to reload it?").arg(filePath));

        if (reply == QMessageBox::Yes) {
            editor->reload();
        }
        else {
            editor->omitModifications();
        }
    }
    else if (state == ScintillaNext::Deleted) {
        qInfo("ScintillaNext::Deleted");
    }
    else if (state == ScintillaNext::Restored) {
        qInfo("ScintillaNext::Restored");
    }

    return true;
}

bool MainWindow::saveFileWithElevation(ScintillaNext *editor, const QString &filePath)
{
    // Go straight to pkexec — polkit will show its own auth dialog
    const QByteArray data = editor->getText(editor->textLength() + 1);

    QProcess proc;
    proc.setProcessChannelMode(QProcess::ForwardedErrorChannel);
    proc.start("pkexec", QStringList() << "tee" << filePath);

    if (!proc.waitForStarted(5000)) {
        QMessageBox::warning(this, tr("Error"),
            tr("Could not start pkexec. Is polkit installed?"));
        return false;
    }

    proc.write(data);
    proc.closeWriteChannel();
    proc.waitForFinished(15000);

    if (proc.exitCode() == 0) {
        editor->setSavePoint();
        editor->setNeedsElevation(true);
        return true;
    }

    if (proc.exitCode() != 126) { // 126 = user cancelled auth
        QMessageBox::warning(this, tr("Error Saving File"),
            tr("Could not save <b>%1</b> with administrator privileges.<br>pkexec exited with code %2.")
            .arg(filePath).arg(proc.exitCode()));
    }
    return false;
}

void MainWindow::showSaveErrorMessage(ScintillaNext *editor, QFileDevice::FileError error)
{
    const QString name = editor->isFile() ? editor->getFilePath() : editor->getName();

    // Map error code to human-readable string
    QString errorString;
    switch (error) {
        case QFileDevice::ReadError:        errorString = tr("Read error"); break;
        case QFileDevice::WriteError:       errorString = tr("Write error"); break;
        case QFileDevice::FatalError:       errorString = tr("Fatal error"); break;
        case QFileDevice::ResourceError:    errorString = tr("Resource error"); break;
        case QFileDevice::OpenError:        errorString = tr("Open error"); break;
        case QFileDevice::AbortError:       errorString = tr("Abort error"); break;
        case QFileDevice::TimeOutError:     errorString = tr("Timeout error"); break;
        case QFileDevice::UnspecifiedError: errorString = tr("Unspecified error"); break;
        case QFileDevice::RemoveError:      errorString = tr("Remove error"); break;
        case QFileDevice::RenameError:      errorString = tr("Rename error"); break;
        case QFileDevice::PositionError:    errorString = tr("Position error"); break;
        case QFileDevice::ResizeError:      errorString = tr("Resize error"); break;
        case QFileDevice::PermissionsError: errorString = tr("Permissions error"); break;
        case QFileDevice::CopyError:        errorString = tr("Copy error"); break;
        default:                            errorString = tr("Unknown error (%1)").arg(static_cast<int>(error)); break;
    }

    QMessageBox::warning(this, tr("Error Saving File"),
        tr("An error occurred when saving <b>%1</b><br><br>Error: %2").arg(name, errorString));
}

void MainWindow::showEditorZoomLevelIndicator()
{
    // Not sure if Scintilla's zoom level matches up to an exact percentage, but visibly this is close
    FadingIndicator::showText(currentEditor(), tr("Zoom: %1%").arg(zoomLevel * 10 + 100));
}

MainWindow::UserSaveAction MainWindow::promptForSave(const QVector<ScintillaNext *> &editors)
{
    const int count = editors.count();
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("Save File"));
    msgBox.setIcon(QMessageBox::Question);

    // Using pluralization for the main text
    QString text = (count == 1)
                       ? tr("Save changes to <b>%1</b>?").arg(editors.first()->getName())
                       : tr("There are %n files with unsaved changes. Save them?", "", count);
    msgBox.setText(text);

    auto *saveBtn = msgBox.addButton(count > 1 ? tr("Save All") : tr("Save"), QMessageBox::AcceptRole);
    auto *discardBtn = msgBox.addButton(count > 1 ? tr("Discard All") : tr("Discard"), QMessageBox::DestructiveRole);
    msgBox.addButton(QMessageBox::Cancel);

    msgBox.setDefaultButton(saveBtn);
    msgBox.exec();

    if (msgBox.clickedButton() == saveBtn)    return UserSaveAction::SaveAll;
    if (msgBox.clickedButton() == discardBtn) return UserSaveAction::DiscardAll;
    return UserSaveAction::Cancel;
}

void MainWindow::saveSettings() const
{
    qInfo(Q_FUNC_INFO);

    ApplicationSettings *settings = app->getSettings();

    settings->setValue("MainWindow/geometry", saveGeometry());
    settings->setValue("MainWindow/windowState", saveState());

    settings->setValue("Editor/ZoomLevel", zoomLevel);
}

void MainWindow::restoreSettings()
{
    qInfo(Q_FUNC_INFO);

    ApplicationSettings *settings = app->getSettings();

    zoomLevel = settings->value("Editor/ZoomLevel", 0).toInt();

    if (settings->contains("Gui/ToolBar")) {
        QStringList actionNames;
        actionNames = settings->value("Gui/ToolBar").toStringList();

        ui->mainToolBar->clear();

        ActionUtils::populateActionContainer(ui->mainToolBar, this, actionNames);
    }
}

ISearchResultsHandler *MainWindow::determineSearchResultsHandler()
{
    // Determine what will get the search results
    if (app->getSettings()->combineSearchResults()) {
        searchResults.reset(new SearchResultsCollector(findChild<SearchResultsDock *>()));

        return searchResults.data();
    }
    else {
        return findChild<SearchResultsDock *>();
    }
}

void MainWindow::restoreWindowState()
{
    ApplicationSettings *settings = app->getSettings();

    restoreGeometry(settings->value("MainWindow/geometry").toByteArray());
    restoreState(settings->value("MainWindow/windowState").toByteArray());

    // Always hide the dock no matter how the application was closed
    SearchResultsDock *srDock = findChild<SearchResultsDock *>();
    srDock->hide();
}

void MainWindow::switchToEditor(const ScintillaNext *editor)
{
    dockedEditor->switchToEditor(editor);
}

void MainWindow::focusIn()
{
    qInfo(Q_FUNC_INFO);

    ScintillaNext *editor = currentEditor();

    if (editor) {
        if (checkFileForModification(currentEditor())) {
            updateGui(currentEditor());
        }
    }
}

void MainWindow::addEditor(ScintillaNext *editor)
{
    qInfo(Q_FUNC_INFO);

    detectLanguage(editor);

    // These should only ever occur for the focused editor??
    // TODO: look at editor inspector as an example to ensure updates are only coming from one editor.
    // Can save the connection objects and disconnected from them and only connect to the editor as it is activated.
    connect(editor, &ScintillaNext::savePointChanged, this, [=, this]() { updateSaveStatusBasedUi(editor); });
    connect(editor, &ScintillaNext::renamed, this, [= ,this]() { detectLanguage(editor); });
    connect(editor, &ScintillaNext::renamed, this, [=, this]() { updateFileStatusBasedUi(editor); });
    connect(editor, &ScintillaNext::updateUi, this, &MainWindow::updateDocumentBasedUi);

    // Watch for any zoom events (Ctrl+Scroll or pinch-to-zoom (Qt translates it as Ctrl+Scroll)) so that the event
    // can be handled before the ScintillaEditBase widget, so that it can be applied to all editors to keep zoom level equal.
    // NOTE: Need to install this on the scroll area's viewport, not on the editor widget itself...that was painful to learn
    editor->viewport()->installEventFilter(zoomEventWatcher);

    editor->setZoom(zoomLevel);

    editor->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(editor, &ScintillaNext::customContextMenuRequested, this, [=, this](const QPoint &pos) {
        contextMenuPos = editor->positionFromPoint(pos.x(), pos.y());

        QStringList actionNames = {
            "Cut",
            "Copy",
            "Paste",
            "Delete",
            "",
            "SelectAll",
            "",
            "Base64Encode",
            "URLEncode",
            "",
            "Base64Decode",
            "URLDecode"
        };

        // If the entry exists in the settings, use that
        ApplicationSettings *settings = app->getSettings();
        if (settings->contains("Gui/EditorContextMenu")) {
            actionNames = settings->value("Gui/EditorContextMenu").toStringList();
        }

        // If the cursor is at a URL, prepend the action
        URLFinder *urlFinder = editor->findChild<URLFinder *>(QString(), Qt::FindDirectChildrenOnly);
        if (urlFinder && urlFinder->isEnabled() && urlFinder->isURL(contextMenuPos)) {
            actionNames.prepend("");
            actionNames.prepend("CopyURL");
        }

        auto menu = buildMenu(actionNames);
        menu->addSeparator();
        menu->addMenu(ui->menuMarkAllOccurrences);
        menu->addMenu(ui->menuClearMarks);

        // SpellChecker: návrhy + "Add to dictionary"
        SpellChecker *sc = editor->findChild<SpellChecker *>(
                               QString(), Qt::FindDirectChildrenOnly);
        if (sc && sc->isEnabled()) {
            const QString misspelled = sc->wordAtPosition(contextMenuPos);
            if (!misspelled.isEmpty() && !sc->spellCheck(misspelled)) {
                menu->addSeparator();
                const QStringList suggs = sc->suggestions(misspelled);
                if (suggs.isEmpty()) {
                    QAction *noSugg = menu->addAction(tr("(no suggestions)"));
                    noSugg->setEnabled(false);
                } else {
                    for (const QString &s : suggs.mid(0, 8)) {
                        QAction *a = menu->addAction(s);
                        connect(a, &QAction::triggered, this,
                                [editor, s, misspelled, pos = contextMenuPos]() {
                            const int len = static_cast<int>(editor->length());
                            const QByteArray raw = editor->getText(len + 1).left(len);
                            const QByteArray needle = misspelled.toUtf8();
                            // Hľadaj slovo v okolí kliknutej pozície
                            int byteStart = qMax(0, pos - (int)needle.size());
                            const int searchEnd = qMin(raw.size(), pos + (int)needle.size() + 1);
                            byteStart = raw.indexOf(needle, byteStart);
                            if (byteStart >= 0 && byteStart < searchEnd) {
                                editor->setTargetRange(byteStart, byteStart + needle.size());
                                const QByteArray replacement = s.toUtf8();
                                editor->replaceTarget(replacement.size(), replacement.constData());
                            }
                        });
                    }
                }
                menu->addSeparator();
                QAction *addAct = menu->addAction(
                    tr("Add \"%1\" to dictionary").arg(misspelled));
                connect(addAct, &QAction::triggered, this, [sc, misspelled]() {
                    sc->addToUserDict(misspelled);
                });
            }
        }

        menu->popup(QCursor::pos());
    });

    // The editor has been entirely configured at this point, so add it to the docked editor
    dockedEditor->addEditor(editor);

    // Apply change-history margin state from current settings
    applyChangeHistoryToEditor(editor, app->getSettings()->showChangeHistory());
}

void MainWindow::checkForUpdates(bool silent)
{
#ifdef Q_OS_WIN
    qInfo(Q_FUNC_INFO);

    QString url = "https://github.com/dail8859/NotepadNext/raw/master/updates.json";
    QSimpleUpdater::getInstance()->checkForUpdates(url);

    if (!silent) {
        connect(QSimpleUpdater::getInstance(), &QSimpleUpdater::checkingFinished, this, &MainWindow::checkForUpdatesFinished, Qt::UniqueConnection);
    }
    else {
        disconnect(QSimpleUpdater::getInstance(), &QSimpleUpdater::checkingFinished, this, &MainWindow::checkForUpdatesFinished);
    }


    app->getSettings()->setValue("App/LastUpdateCheck", QDateTime::currentDateTime());
#else
    Q_UNUSED(silent);
#endif
}

void MainWindow::checkForUpdatesFinished(QString url)
{
#ifdef Q_OS_WIN
    if (!QSimpleUpdater::getInstance()->getUpdateAvailable(url)) {
        QMessageBox::information(this, QString(), tr("No updates are available at this time."));
    }
#endif
}

void MainWindow::initUpdateCheck()
{
#ifdef Q_OS_WIN
#ifdef QT_DEBUG
    if (true) {
#else
    QSettings registry(QSettings::NativeFormat, QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());
    const bool autoUpdatesEnabled = registry.value("AutoUpdate", 0).toBool();
    qInfo("AutoUpdates: %d", autoUpdatesEnabled);

    if (autoUpdatesEnabled) {
#endif
        connect(ui->actionCheckForUpdates, &QAction::triggered, this, &MainWindow::checkForUpdates);

        // A bit after startup, see if we need to automatically check for an update
        QTimer::singleShot(15000, this, [this]() {
            ApplicationSettings settings;
            QDateTime dt = settings.value("App/LastUpdateCheck", QDateTime::currentDateTime()).toDateTime();

            if (dt.isValid()) {
                qInfo("Last checked for updates at: %s", qUtf8Printable(dt.toString()));

                if (dt.addDays(7) < QDateTime::currentDateTime()) {
                    checkForUpdates(true);
                }
            }
        });
    }
    else {
        ui->actionCheckForUpdates->setDisabled(true);
        ui->actionCheckForUpdates->setVisible(false);
    }
#else
    ui->actionCheckForUpdates->setDisabled(true);
    ui->actionCheckForUpdates->setVisible(false);
#endif
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    const SessionManager *sessionManager = app->getSessionManager();
    QVector<ScintillaNext *> e;

    // Check all editors to see if the session manager will not handle it
    for (auto editor : editors()) {
        if (!sessionManager->willFileGetStoredInSession(editor)) {
            e.append(editor);
        }
    }

    if (!checkEditorsBeforeClose(e)) {
        event->ignore();
        return;
    }

    emit aboutToClose();

    event->accept();

    QMainWindow::closeEvent(event);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    qInfo(Q_FUNC_INFO);

    // NOTE: for urls these can be dragged anywhere in the application, editor, tabs, menu
    // because the ScintillaNext editor ignores urls so they can be handled by the main
    // application
    // Text dragging within the editor object itself is handled by Scintilla, but if the text
    // is dragged to other parts (tabs, menu, etc) it will be handled by the application to
    // create a new editor from the text.

    // Accept urls and text
    if (event->mimeData()->hasUrls() || event->mimeData()->hasText()) {
        event->acceptProposedAction();
    }
    else {
        event->ignore();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    qInfo(Q_FUNC_INFO);

    if (event->mimeData()->hasUrls()) {
        // Get the urls into a stringlist
        QStringList fileNames;
        for (const QUrl &url : event->mimeData()->urls()) {
            if (url.isLocalFile()) {
                QFileInfo info(url.toLocalFile());

                if (info.exists()) {
                    if (info.isDir()) {
                        QDirIterator it(url.toLocalFile(), QDir::Files, QDirIterator::FollowSymlinks| QDirIterator::Subdirectories);
                        while (it.hasNext()) {
                            fileNames << it.next();
                        }
                    }
                    else {
                        fileNames.append(url.toLocalFile());
                    }
                }
            }
        }

        openFileList(fileNames);
        bringWindowToForeground();
        event->acceptProposedAction();
    }
    else if (event->mimeData()->hasText()) {
        if (event->source()) {
            // if it is from an editor, remove the text
            ScintillaNext *sn = qobject_cast<ScintillaNext *>(event->source());
            if (sn) {
                sn->replaceSel("");
            }
        }

        newFile();
        currentEditor()->setText(event->mimeData()->text().toLocal8Bit().constData());
        bringWindowToForeground();
        event->acceptProposedAction();
    }
    else {
        event->ignore();
    }
}

QMenu *MainWindow::buildMenu(QStringList actionNames)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);

    ActionUtils::populateActionContainer(menu, this, actionNames);

    return menu;
}

void MainWindow::tabBarRightClicked(ScintillaNext *editor)
{
    qInfo(Q_FUNC_INFO);

    // Focus on the correct tab
    dockedEditor->switchToEditor(editor);

    // Default actions
    QStringList actionNames{
        "Close",
        "CloseAllExceptActive",
        "CloseAllToLeft",
        "CloseAllToRight",
        "",
        "Save",
        "SaveAs",
        "Rename",
        "",
        "Reload",
        "",
#ifdef Q_OS_WIN
        "ShowInExplorer",
        "OpenTerminalHere",
        "",
#endif
        "CopyFullPath",
        "CopyFileName",
        "CopyFileDirectory"
    };

    // If the entry exists in the settings, use that
    ApplicationSettings *settings = app->getSettings();
    if (settings->contains("Gui/TabBarContextMenu")) {
        actionNames = settings->value("Gui/TabBarContextMenu").toStringList();
    }

    buildMenu(actionNames)->popup(QCursor::pos());
}

void MainWindow::languageMenuTriggered()
{
    const QAction *act = qobject_cast<QAction *>(sender());
    auto editor = currentEditor();
    QVariant v = act->data();

    setLanguage(editor, v.toString());
}

void MainWindow::openShortcutEditor()
{
    // Collect all QActions from menus (skip separators and the editor action itself)
    QList<QAction *> actions;
    for (QAction *a : findChildren<QAction *>()) {
        if (!a->objectName().startsWith(QStringLiteral("action"))) continue;
        if (a->objectName() == QStringLiteral("actionShortcutEditor")) continue;
        if (a->isSeparator()) continue;
        actions.append(a);
    }

    ShortcutEditorDialog dlg(actions, m_defaultShortcuts, this);
    if (dlg.exec() != QDialog::Accepted) return;

    // Persist changed shortcuts to ApplicationSettings
    ApplicationSettings *settings = app->getSettings();
    settings->beginGroup(QStringLiteral("Shortcuts"));

    // Only touch keys that actually changed in this session. Previously this
    // cleared the entire group with settings->remove(QString()) before
    // rewriting it, which meant that simply opening the dialog and clicking
    // OK without changing anything (an empty "changed" map) wiped out every
    // previously saved custom shortcut.
    const auto changed = dlg.changedShortcuts();
    for (auto it = changed.cbegin(); it != changed.cend(); ++it) {
        if (it.value().isEmpty())
            settings->remove(it.key());
        else
            settings->setValue(it.key(), it.value().toString());
    }
    settings->endGroup();

    // Apply the new shortcuts immediately
    applyCustomShortcuts();
}
