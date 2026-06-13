#ifndef SHORTCUTEDITORDIALOG_H
#define SHORTCUTEDITORDIALOG_H

#include <QDialog>
#include <QAction>
#include <QKeySequence>
#include <QMap>
#include <QList>

class QTableWidget;
class QLineEdit;
class QPushButton;
class QLabel;
class QDialogButtonBox;
class QKeySequenceEdit;

class ShortcutEditorDialog : public QDialog
{
    Q_OBJECT

public:
    // defaultShortcuts: actionKey -> "true" application default shortcut
    // (i.e. the shortcut the action would have if no [Shortcuts] entry
    // existed in the config at all). If an action's key is missing from
    // this map, its shortcut at dialog-open time is used as a fallback.
    explicit ShortcutEditorDialog(QList<QAction *> actions,
                                   const QMap<QString, QKeySequence> &defaultShortcuts = {},
                                   QWidget *parent = nullptr);

    // Returns map of actionKey -> new QKeySequence (only changed ones)
    QMap<QString, QKeySequence> changedShortcuts() const;

private slots:
    void filterTable(const QString &text);
    void onTableSelectionChanged();
    void onKeySequenceChanged(const QKeySequence &seq);
    void clearShortcut();
    void resetToDefault();
    void resetAllToDefault();
    void applyChanges();

private:
    void buildUi();
    void populateTable(const QString &filter = QString());
    QString actionKey(QAction *action) const;

    QList<QAction *>            m_actions;
    // actionKey -> original shortcut at dialog open time
    QMap<QString, QKeySequence> m_originals;
    // actionKey -> current (possibly edited) shortcut
    QMap<QString, QKeySequence> m_current;
    // actionKey -> "true" application default shortcut (used by
    // "Reset to default" / "Reset ALL to defaults")
    QMap<QString, QKeySequence> m_defaults;

    QLineEdit        *m_filterEdit   = nullptr;
    QTableWidget     *m_table        = nullptr;
    QKeySequenceEdit *m_seqEdit      = nullptr;
    QPushButton      *m_clearBtn     = nullptr;
    QPushButton      *m_resetBtn     = nullptr;
    QPushButton      *m_resetAllBtn  = nullptr;
    QDialogButtonBox *m_buttonBox    = nullptr;
    QLabel           *m_conflictLbl  = nullptr;

    int  m_selectedRow = -1;
    bool m_updating    = false;
};

#endif // SHORTCUTEDITORDIALOG_H
