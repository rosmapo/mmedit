#include "ShortcutEditorDialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QDialogButtonBox>
#include <QKeySequenceEdit>
#include <QGroupBox>
#include <QMessageBox>
#include <QAction>
#include <QRegularExpression>

// ---------------------------------------------------------------------------
// Helper: strip "action" prefix + underscores from objectName to get the key
// used in the [Shortcuts] INI section.
// e.g.  "actionSave_All"  ->  "Save_All"  (Qt trims spaces, so "Save All" works too)
// ---------------------------------------------------------------------------
static QString keyFromObjectName(const QString &objectName)
{
    if (objectName.startsWith(QStringLiteral("action")))
        return objectName.mid(6); // length of "action"
    return objectName;
}

// ---------------------------------------------------------------------------
ShortcutEditorDialog::ShortcutEditorDialog(QList<QAction *> actions, QWidget *parent)
    : QDialog(parent)
    , m_actions(actions)
{
    setWindowTitle(tr("Shortcut Editor"));
    setMinimumSize(680, 480);

    // Snapshot originals
    for (QAction *a : m_actions) {
        const QString key = actionKey(a);
        if (key.isEmpty()) continue;
        const QKeySequence ks = a->shortcut();
        m_originals[key] = ks;
        m_current[key]   = ks;
    }

    buildUi();
    populateTable();
}

// ---------------------------------------------------------------------------
QString ShortcutEditorDialog::actionKey(QAction *action) const
{
    if (!action) return {};
    const QString obj = action->objectName();
    if (obj.isEmpty()) return {};
    return keyFromObjectName(obj);
}

// ---------------------------------------------------------------------------
void ShortcutEditorDialog::buildUi()
{
    auto *mainLayout = new QVBoxLayout(this);

    // --- Filter row ---
    auto *filterLayout = new QHBoxLayout;
    filterLayout->addWidget(new QLabel(tr("Filter:")));
    m_filterEdit = new QLineEdit;
    m_filterEdit->setPlaceholderText(tr("Type to search actions..."));
    m_filterEdit->setClearButtonEnabled(true);
    filterLayout->addWidget(m_filterEdit);
    mainLayout->addLayout(filterLayout);

    // --- Table ---
    m_table = new QTableWidget(0, 2);
    m_table->setHorizontalHeaderLabels({tr("Action"), tr("Shortcut")});
    m_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setAlternatingRowColors(true);
    m_table->setSortingEnabled(true);
    m_table->verticalHeader()->setVisible(false);
    mainLayout->addWidget(m_table, 1);

    // --- Edit group ---
    auto *editGroup  = new QGroupBox(tr("Edit selected shortcut"));
    auto *editLayout = new QGridLayout(editGroup);

    editLayout->addWidget(new QLabel(tr("Press new shortcut:")), 0, 0);
    m_seqEdit = new QKeySequenceEdit;
    editLayout->addWidget(m_seqEdit, 0, 1);

    m_clearBtn = new QPushButton(tr("Clear"));
    editLayout->addWidget(m_clearBtn, 0, 2);

    m_resetBtn = new QPushButton(tr("Reset to default"));
    editLayout->addWidget(m_resetBtn, 0, 3);

    m_conflictLbl = new QLabel;
    m_conflictLbl->setStyleSheet(QStringLiteral("color: red;"));
    editLayout->addWidget(m_conflictLbl, 1, 0, 1, 4);

    editGroup->setEnabled(false);
    mainLayout->addWidget(editGroup);
    // keep reference so we can enable/disable
    m_seqEdit->parentWidget(); // editGroup is parent-widget chain
    // store group ref via m_seqEdit's groupBox parent:
    m_seqEdit->setProperty("groupRef", QVariant::fromValue<QObject*>(editGroup));

    // --- Bottom buttons ---
    m_resetAllBtn = new QPushButton(tr("Reset ALL to defaults"));
    m_buttonBox   = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    auto *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(m_resetAllBtn);
    bottomLayout->addStretch();
    bottomLayout->addWidget(m_buttonBox);
    mainLayout->addLayout(bottomLayout);

    // Connections
    connect(m_filterEdit, &QLineEdit::textChanged, this, &ShortcutEditorDialog::filterTable);
    connect(m_table->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &ShortcutEditorDialog::onTableSelectionChanged);
    connect(m_seqEdit, &QKeySequenceEdit::keySequenceChanged,
            this, &ShortcutEditorDialog::onKeySequenceChanged);
    connect(m_clearBtn,    &QPushButton::clicked, this, &ShortcutEditorDialog::clearShortcut);
    connect(m_resetBtn,    &QPushButton::clicked, this, &ShortcutEditorDialog::resetToDefault);
    connect(m_resetAllBtn, &QPushButton::clicked, this, &ShortcutEditorDialog::resetAllToDefault);
    connect(m_buttonBox,   &QDialogButtonBox::accepted, this, &ShortcutEditorDialog::applyChanges);
    connect(m_buttonBox,   &QDialogButtonBox::rejected, this, &QDialog::reject);
}

// ---------------------------------------------------------------------------
void ShortcutEditorDialog::populateTable(const QString &filter)
{
    m_table->setSortingEnabled(false);
    m_table->setRowCount(0);

    const QString lf = filter.toLower();

    for (QAction *a : m_actions) {
        const QString key = actionKey(a);
        if (key.isEmpty()) continue;

        // Build display name from action text (strip & accelerators)
        QString displayName = a->text().remove(QLatin1Char('&')).trimmed();
        if (displayName.isEmpty())
            displayName = key;

        if (!lf.isEmpty() && !displayName.toLower().contains(lf) && !key.toLower().contains(lf))
            continue;

        const QKeySequence cur = m_current.value(key);
        const bool modified    = (cur != m_originals.value(key));

        int row = m_table->rowCount();
        m_table->insertRow(row);

        auto *nameItem = new QTableWidgetItem(displayName);
        nameItem->setData(Qt::UserRole, key); // store the INI key
        if (modified) {
            QFont f = nameItem->font();
            f.setBold(true);
            nameItem->setFont(f);
        }
        m_table->setItem(row, 0, nameItem);

        auto *seqItem = new QTableWidgetItem(cur.toString(QKeySequence::NativeText));
        seqItem->setData(Qt::UserRole, key);
        if (modified) {
            QFont f = seqItem->font();
            f.setBold(true);
            seqItem->setFont(f);
        }
        m_table->setItem(row, 1, seqItem);
    }

    m_table->setSortingEnabled(true);
    m_table->sortItems(0);
}

// ---------------------------------------------------------------------------
void ShortcutEditorDialog::filterTable(const QString &text)
{
    m_selectedRow = -1;
    populateTable(text);
}

// ---------------------------------------------------------------------------
void ShortcutEditorDialog::onTableSelectionChanged()
{
    if (m_updating) return;

    auto *editGroup = qobject_cast<QGroupBox *>(
        m_seqEdit->property("groupRef").value<QObject*>());

    const QList<QTableWidgetItem *> sel = m_table->selectedItems();
    if (sel.isEmpty()) {
        m_selectedRow = -1;
        if (editGroup) editGroup->setEnabled(false);
        m_conflictLbl->clear();
        return;
    }

    m_selectedRow = sel.first()->row();
    const QString key = m_table->item(m_selectedRow, 0)->data(Qt::UserRole).toString();
    const QKeySequence cur = m_current.value(key);

    m_updating = true;
    m_seqEdit->setKeySequence(cur);
    m_updating = false;

    if (editGroup) editGroup->setEnabled(true);
    m_conflictLbl->clear();
}

// ---------------------------------------------------------------------------
void ShortcutEditorDialog::onKeySequenceChanged(const QKeySequence &seq)
{
    if (m_updating || m_selectedRow < 0) return;

    const QString key = m_table->item(m_selectedRow, 0)->data(Qt::UserRole).toString();

    // Check for conflicts
    m_conflictLbl->clear();
    if (!seq.isEmpty()) {
        for (auto it = m_current.cbegin(); it != m_current.cend(); ++it) {
            if (it.key() != key && it.value() == seq) {
                // Find display name of conflicting action
                QString confName = it.key();
                for (QAction *a : m_actions) {
                    if (actionKey(a) == it.key()) {
                        confName = a->text().remove(QLatin1Char('&')).trimmed();
                        break;
                    }
                }
                m_conflictLbl->setText(tr("⚠ Conflict with: %1").arg(confName));
                break;
            }
        }
    }

    m_current[key] = seq;

    // Update table cell
    const bool modified = (seq != m_originals.value(key));
    auto *nameItem = m_table->item(m_selectedRow, 0);
    auto *seqItem  = m_table->item(m_selectedRow, 1);
    seqItem->setText(seq.toString(QKeySequence::NativeText));

    QFont f = nameItem->font();
    f.setBold(modified);
    nameItem->setFont(f);
    seqItem->setFont(f);
}

// ---------------------------------------------------------------------------
void ShortcutEditorDialog::clearShortcut()
{
    if (m_selectedRow < 0) return;
    m_updating = true;
    m_seqEdit->setKeySequence(QKeySequence());
    m_updating = false;
    onKeySequenceChanged(QKeySequence());
}

// ---------------------------------------------------------------------------
void ShortcutEditorDialog::resetToDefault()
{
    if (m_selectedRow < 0) return;
    const QString key  = m_table->item(m_selectedRow, 0)->data(Qt::UserRole).toString();
    const QKeySequence orig = m_originals.value(key);
    m_updating = true;
    m_seqEdit->setKeySequence(orig);
    m_updating = false;
    onKeySequenceChanged(orig);
}

// ---------------------------------------------------------------------------
void ShortcutEditorDialog::resetAllToDefault()
{
    const auto reply = QMessageBox::question(
        this, tr("Reset all shortcuts"),
        tr("Reset ALL shortcuts to their defaults?\nThis cannot be undone."),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (reply != QMessageBox::Yes) return;

    m_current = m_originals;
    populateTable(m_filterEdit->text());
    m_seqEdit->setKeySequence(QKeySequence());
    m_conflictLbl->clear();
}

// ---------------------------------------------------------------------------
void ShortcutEditorDialog::applyChanges()
{
    // Apply changed shortcuts back to QAction objects immediately
    for (QAction *a : m_actions) {
        const QString key = actionKey(a);
        if (key.isEmpty()) continue;
        if (m_current.contains(key))
            a->setShortcut(m_current.value(key));
    }
    accept();
}

// ---------------------------------------------------------------------------
QMap<QString, QKeySequence> ShortcutEditorDialog::changedShortcuts() const
{
    QMap<QString, QKeySequence> result;
    for (auto it = m_current.cbegin(); it != m_current.cend(); ++it) {
        // Include all non-default shortcuts (so user-cleared ones are also saved as empty)
        if (it.value() != m_originals.value(it.key()))
            result.insert(it.key(), it.value());
    }
    return result;
}
