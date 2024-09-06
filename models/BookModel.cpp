#include "BookModel.h"

#include <QDebug>

BookModel::BookModel()
{

}

BookModel::~BookModel()
{
    for(auto &w:m_words){
        delete w;
    }
}

void BookModel::addWord(const QString &word, const QString &details)
{
    for(auto &w:m_words){
        if(w->getWord()==word)
            return;
    }
    m_words.push_back(new Word(word,details));
}

void BookModel::printBook()
{
    qDebug() << "Book : " << getName();
    for(auto& w : m_words){
        //qDebug() << "   -" << w.getWord();
        //qDebug() << "Details : " << w.getDetails();
    }
}
