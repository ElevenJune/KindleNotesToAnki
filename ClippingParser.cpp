#include "ClippingParser.h"
#include <QFile>
#include <QDebug>

ClippingParser::ClippingParser(QObject *parent)
    : QObject(parent),
      m_path("./test.txt")
{

}

bool ClippingParser::readFile()
{
    QFile file(m_path);
    if(!file.open(QFile::ReadOnly))
        qWarning() << "Could not open " << m_path << file.errorString();
    while(!file.atEnd()){
        qDebug() << file.readLine();
    }
    return true;
}
