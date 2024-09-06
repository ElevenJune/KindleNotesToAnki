#ifndef CLIPPINGPARSER_H
#define CLIPPINGPARSER_H

#include <QObject>
#include <QFile>

class WordManager;

class ClippingParser : public QObject
{
    Q_OBJECT
public:
    explicit ClippingParser(QObject *parent = nullptr);

    void setPath(const QString& path){m_path = path;}
    bool readFile();

private:
    void addWordToBook(const QString& book, const QString& word, const QString& details);

signals:
    void signalFileRead();

private :
    QString   m_path;
    WordManager* m_wordManager;

};

#endif // CLIPPINGPARSER_H
