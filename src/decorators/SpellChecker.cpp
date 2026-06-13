#include "SpellChecker.h"
#include "ScintillaNext.h"

#include <hunspell/hunspell.hxx>

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>
#include <QTextStream>
#include <QTimer>

static QStringList dictionarySearchPaths()
{
    return {
        QStringLiteral("/usr/share/hunspell"),
        QStringLiteral("/usr/share/myspell/dicts"),
        QStringLiteral("/usr/local/share/hunspell"),
    };
}

SpellChecker::SpellChecker(ScintillaNext *editor)
    : EditorDecorator(editor)
    , m_timer(new QTimer(this))
{
    m_indicator = editor->allocateIndicator("spell_checker");
    editor->indicSetStyle(m_indicator, INDIC_SQUIGGLE);
    editor->indicSetFore(m_indicator, 0x0000FF); // red in BGR
    editor->indicSetUnder(m_indicator, true);

    m_timer->setInterval(500);
    m_timer->setSingleShot(true);
    connect(m_timer, &QTimer::timeout, this, &SpellChecker::check);

    // Opravene C++20 varovanie: zmenene [=] na [this]
    connect(this, &EditorDecorator::stateChanged, this, [this](bool enabled) {
        if (enabled) {
            check();
        } else {
            clear();
            m_timer->stop();
        }
    });

    // User dictionary path
    const QString configDir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    m_userDictPath = configDir + QStringLiteral("/user.dic");

    // Load user dictionary
    if (QFile::exists(m_userDictPath)) {
        QFile f(m_userDictPath);
        if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&f);
            while (!in.atEnd()) {
                const QString word = in.readLine().trimmed();
                if (!word.isEmpty())
                    m_userWords << word;
            }
        }
    }
}

SpellChecker::~SpellChecker()
{
    delete m_hunspell;
}

bool SpellChecker::loadDictionary(const QString &lang)
{
    delete m_hunspell;
    m_hunspell = nullptr;
    m_lang = QString();

    for (const QString &path : dictionarySearchPaths()) {
        const QString aff = path + QChar('/') + lang + QStringLiteral(".aff");
        const QString dic = path + QChar('/') + lang + QStringLiteral(".dic");
        if (QFile::exists(aff) && QFile::exists(dic)) {
            m_hunspell = new Hunspell(aff.toLocal8Bit().constData(),
                                      dic.toLocal8Bit().constData());
            m_lang = lang;
            qInfo("SpellChecker: loaded dictionary %s from %s",
                  qUtf8Printable(lang), qUtf8Printable(path));
            return true;
        }
    }

    qWarning("SpellChecker: dictionary not found for %s", qUtf8Printable(lang));
    return false;
}

QStringList SpellChecker::suggestions(const QString &word) const
{
    if (!m_hunspell) return {};
    QStringList result;
    for (const auto &s : m_hunspell->suggest(word.toStdString()))
        result << QString::fromStdString(s);
    return result;
}

void SpellChecker::addToUserDict(const QString &word)
{
    if (m_userWords.contains(word)) return;
    m_userWords << word;

    // IMPLEMENTÁCIA MOŽNOSTI A: Vytvorenie nadradeneho adresara, ak neexistuje
    QDir dir(QFileInfo(m_userDictPath).absolutePath());
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QFile f(m_userDictPath);
    if (f.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&f);
        out << word << '\n';
    } else {
        qWarning("SpellChecker: Failed to open user dictionary for writing: %s", qUtf8Printable(m_userDictPath));
    }

    if (m_hunspell)
        m_hunspell->add(word.toStdString());

    check();
}

bool SpellChecker::spellCheck(const QString &word) const
{
    if (!m_hunspell) return true;
    if (m_userWords.contains(word)) return true;
    return m_hunspell->spell(word.toStdString());
}

QString SpellChecker::wordAtPosition(int bytePos) const
{
    if (!editor) return {};

    const int totalLen = static_cast<int>(editor->length());
    if (totalLen == 0 || bytePos < 0 || bytePos > totalLen) return {};

    const QByteArray raw = editor->getText(totalLen + 1).left(totalLen);
    const QString text   = QString::fromUtf8(raw);

    // Preveď byte pozíciu na index v QString
    int i = QString::fromUtf8(raw.left(bytePos)).length();
    if (i >= text.length()) i = text.length() - 1;

    // Ak nie sme na znaku slova, vráť prázdny reťazec
    if (i < 0 || !isWordChar(text[i])) return {};

    // Nájdi začiatok slova
    int start = i;
    while (start > 0 && isWordChar(text[start - 1])) --start;

    // Nájdi koniec slova
    int end = i;
    while (end < text.length() && isWordChar(text[end])) ++end;

    return text.mid(start, end - start);
}

bool SpellChecker::isWordChar(QChar c) const
{
    return c.isLetter() || c == QChar('\'') || c == QChar('\u2019');
}

bool SpellChecker::shouldSkipWord(const QString &word) const
{
    if (word.length() < 2) return true;

    // Skip URLs
    if (word.startsWith(QStringLiteral("http")) ||
        word.startsWith(QStringLiteral("www.")))
        return true;

    // Skip words with digits
    for (const QChar &c : word)
        if (c.isDigit()) return true;

    // Skip ALL_CAPS (abbreviations)
    if (word == word.toUpper()) return true;

    // Skip camelCase (contains uppercase after first char)
    for (int i = 1; i < word.length(); ++i)
        if (word[i].isUpper()) return true;

    return false;
}

void SpellChecker::check()
{
    if (!m_hunspell || !editor) return;

    // Clear current indicators
    editor->setIndicatorCurrent(m_indicator);
    editor->indicatorClearRange(0, editor->length());

    const int totalLen = static_cast<int>(editor->length());
    if (totalLen == 0) return;

    const QByteArray raw = editor->getText(totalLen + 1).left(totalLen);
    const QString text = QString::fromUtf8(raw);

    int i = 0;
    while (i < text.length()) {
        // Skip non-word chars
        if (!isWordChar(text[i])) { ++i; continue; }

        // Collect word
        int start = i;
        while (i < text.length() && isWordChar(text[i])) ++i;
        const QString word = text.mid(start, i - start);

        if (!shouldSkipWord(word) && !spellCheck(word)) {
            // Convert QString position to UTF-8 byte position
            const int byteStart = text.left(start).toUtf8().length();
            const int byteLen   = word.toUtf8().length();
            editor->indicatorFillRange(byteStart, byteLen);
        }
    }
}

void SpellChecker::clear()
{
    if (!editor) return;
    editor->setIndicatorCurrent(m_indicator);
    editor->indicatorClearRange(0, editor->length());
}

void SpellChecker::notify(const Scintilla::NotificationData *pscn)
{
    if (!m_hunspell) return;

    if (pscn->nmhdr.code == Scintilla::Notification::Modified) {
        if (FlagSet(pscn->modificationType, Scintilla::ModificationFlags::InsertText) ||
            FlagSet(pscn->modificationType, Scintilla::ModificationFlags::DeleteText)) {
            m_timer->start();
        }
    }
}