#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>


class NetworkManager : public QObject
{
    Q_OBJECT
public:
    NetworkManager();

    void getWordsDefinition(QStringList words);
    void getWordsTranslation(QStringList words);

signals:
    void signalFinishedParsing();
    void signalNewWordDefintion(QString word, QStringList definitions);

private slots:
    void slotFinishedParsing();

private:
    QString removeHTML(QString &line);
    void parseHTMLAnswer(QNetworkReply *reply);

private:
    QNetworkAccessManager m_manager;
    QMap<QString,QStringList> m_dico;
};

#endif // NETWORKMANAGER_H
