#ifndef WORDMANAGER_H
#define WORDMANAGER_H

#include <QObject>

class BookModel;

class WordManager : public QObject
{
    Q_OBJECT

public:
    static WordManager& getInstance(){static WordManager m; return m;}

    const QList<BookModel*>& getBooks() const {return m_books;}

    void extracted();
    void printCollection();

    void addWordToBook(const QString &book, const QString &word, const QString &details);
private:
    explicit WordManager(QObject *parent = nullptr);
    ~WordManager();

signals:

private:
    QList<BookModel*> m_books;
};

#endif // WORDMANAGER_H
