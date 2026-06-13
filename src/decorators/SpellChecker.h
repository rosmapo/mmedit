#pragma once

#include "EditorDecorator.h"
#include <QTimer>
#include <QStringList>
#include <memory>

class Hunspell;

class SpellChecker : public EditorDecorator
{
    Q_OBJECT

public:
    explicit SpellChecker(ScintillaNext *editor);
    ~SpellChecker();

    bool loadDictionary(const QString &lang);
    QString currentLanguage() const { return m_lang; }
    QStringList suggestions(const QString &word) const;
    void addToUserDict(const QString &word);
    bool spellCheck(const QString &word) const;
    QString wordAtPosition(int bytePos) const;

public slots:
    void check();
    void clear();
    void notify(const Scintilla::NotificationData *pscn) override;

private:
    bool isWordChar(QChar c) const;
    bool shouldSkipWord(const QString &word) const;

    Hunspell        *m_hunspell = nullptr;
    QTimer          *m_timer    = nullptr;
    int              m_indicator = -1;
    QString          m_lang;
    QStringList      m_userWords;
    QString          m_userDictPath;
};
