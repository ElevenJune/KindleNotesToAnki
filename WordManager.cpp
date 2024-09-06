#include "WordManager.h"
#include "models/BookModel.h"

void WordManager::printCollection()
{
    //print each book
    for(auto &b:m_books){
        b->printBook();
        //qDebug() << "";
    }
}

void WordManager::addWordToBook(const QString &book, const QString &word, const QString &details)
{
    for(auto &b:m_books){
        if(b->getName()==book){
            b->addWord(word,details);
            return;
        }
    }
    BookModel* b = new BookModel();
    b->setName(book);
    b->addWord(word,details);
    m_books.push_back(b);
}

WordManager::WordManager(QObject *parent)
    : QObject{parent}
{}

WordManager::~WordManager()
{
    for(auto& b : m_books)
        delete b;
}


