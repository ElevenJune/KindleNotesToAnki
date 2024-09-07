#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QList>
#include <QFile>
#include <QDebug>

namespace Utils{
QString readFile(const QString& path){
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qWarning() << "Could not open " << path << file.errorString();
        return "";
    }

    QString content = file.readAll();
    file.close();
    return content;
}

}

#endif // UTILS_H
