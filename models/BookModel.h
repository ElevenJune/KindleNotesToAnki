#ifndef BOOKMODEL_H
#define BOOKMODEL_H

#include <QString>
#include <QList>

class Word{
public:
    Word(QString word, QString details):m_word(word),m_details(details){};

    const QString& getWord() const {return m_word;}
    const QString& getDetails() const {return m_details;}

private:
    QString m_word;
    QString m_details;
};

class BookModel{
public:
    BookModel();
    ~BookModel();

    const QString& getName() const {return m_name;}

    void addWord(const QString& word, const QString& details);
    void setName(const QString& name){m_name = name;}

    const QList<Word*>& getWords() const {return m_words;}

    void printBook();

private:
    QString m_name;
    QList<Word*> m_words;
};


#endif // BOOKMODEL_H
