#ifndef CLIPPINGPARSER_H
#define CLIPPINGPARSER_H

#include <QObject>
#include <QFile>

class Word{
public:
    Word(QString word, QString details):m_word(word),m_details(details){};

    const QString& getWord() const {return m_word;}
    const QString& getDetails() const {return m_details;}

private:
    QString m_word;
    QString m_details;
};

class Book{
public:
    Book();

    const QString& getName() const {return m_name;}

    void addWord(const QString& word, const QString& details);
    void setName(const QString& name){m_name = name;}

    void printBook();

private:
    QString m_name;
    QList<Word> m_words;
};

class ClippingParser : public QObject
{
    Q_OBJECT
public:
    explicit ClippingParser(QObject *parent = nullptr);

    bool readFile();
    void setPath(const QString& path){m_path = path;}

    void addWordToBook(const QString& book, const QString& word, const QString& details);

    void printCollection();

signals:
    void signalFileRead();

private :
    QString   m_path;
    QList<Book> m_books;

};

#endif // CLIPPINGPARSER_H
