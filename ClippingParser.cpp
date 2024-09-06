#include "ClippingParser.h"
#include <QFile>
#include <QDebug>

ClippingParser::ClippingParser(QObject *parent)
    : QObject(parent),
    m_path("/media/data/Programmation/KindleNotesToAnki/KindleNotes2Anki/clip.txt")
{
    readFile();
}

bool ClippingParser::readFile()
{
    bool newWord = true;
    QString book;
    QString details;
    QString word;
    QFile file(m_path);
    if(!file.open(QFile::ReadOnly))
        qWarning() << "Could not open " << m_path << file.errorString();
    while(!file.atEnd()){
        QString line = file.readLine().replace("\r\n","");
        //qDebug() << line;
        if(newWord){
            newWord = false;
            book = line;
            //qDebug() << "New word from book" << book;
        }
        else if(line.startsWith("-"))
            details = line;
        else if(line.contains("====")){
            newWord=true;
            addWordToBook(book,word,details);
        }
        else if(line!="")
            word = line;
    }
    printCollection();
    return true;
}

void ClippingParser::addWordToBook(const QString &book, const QString &word, const QString &details)
{
    for(auto &b:m_books){
        if(b.getName()==book){
            b.addWord(word,details);
            return;
        }
    }
    Book b;
    b.setName(book);
    b.addWord(word,details);
    m_books.push_back(b);
}

void ClippingParser::printCollection()
{
    //print each book
    for(auto &b:m_books){
        b.printBook();
        //qDebug() << "";
    }
}

Book::Book()
{

}

void Book::addWord(const QString &word, const QString &details)
{
    for(auto &w:m_words){
        if(w.getWord()==word)
            return;
    }
    m_words.push_back(Word(word,details));
}

void Book::printBook()
{
    qDebug() << "Book : " << getName();
    for(auto& w : m_words){
        //qDebug() << "   -" << w.getWord();
        //qDebug() << "Details : " << w.getDetails();
    }
}
