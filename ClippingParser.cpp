#include "ClippingParser.h"
#include <QFile>
#include <QDebug>
#include "WordManager.h"

ClippingParser::ClippingParser(QObject *parent)
    : QObject(parent),
    m_path("/media/data/Programmation/KindleNotesToAnki/KindleNotes2Anki/clip.txt"),
    m_wordManager(&WordManager::getInstance())
{
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
    emit signalFileRead();
    m_wordManager->printCollection();
    return true;
}

void ClippingParser::addWordToBook(const QString &book, const QString &word, const QString &details)
{
    assert(m_wordManager);
    m_wordManager->addWordToBook(book,word,details);
}
