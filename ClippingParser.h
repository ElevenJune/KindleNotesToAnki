#ifndef CLIPPINGPARSER_H
#define CLIPPINGPARSER_H

#include <QObject>
#include <QFile>

class ClippingParser : public QObject
{
    Q_OBJECT
public:
    explicit ClippingParser(QObject *parent = nullptr);

    bool readFile();
    void setPath(const QString& path){m_path = path;}

signals:
    void signalFileRead();

private :
    QString   m_path;

};

#endif // CLIPPINGPARSER_H
