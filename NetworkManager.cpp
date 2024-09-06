#include "NetworkManager.h"

#include <QRegularExpression>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

NetworkManager::NetworkManager()
    : m_manager(),
      m_dico()
{
    connect(this,&NetworkManager::signalFinishedParsing,
            this,&NetworkManager::slotFinishedParsing);
}

void NetworkManager::getWordsDefinition(QStringList words)
{
    // Mot à rechercher
    QString mot = words.takeFirst();

    // Construction de l'URL
    QString url = QString("https://www.linternaute.fr/dictionnaire/fr/definition/%0/").arg(mot);

    //send the read request
    QNetworkReply* reply = m_manager.get(QNetworkRequest(QUrl(url)));
    QObject::connect(reply, &QNetworkReply::finished, this, [this,words,reply,mot](){
        qDebug()<<"Parsing "<<mot;
        if (reply->error() == QNetworkReply::NoError){
            parseHTMLAnswer(reply);
        }else
            // Erreur lors de la réception de la réponse
            qDebug() << "Erreur : " << reply->errorString();
        if(!words.isEmpty())
            getWordsDefinition(words);
        else
            emit signalFinishedParsing();
        reply->deleteLater();
    });
}

void NetworkManager::getWordsTranslation(QStringList words)
{
    // Construction de l'URL
    QUrl url = QUrl::fromUserInput(QString("https://api-free.deepl.com/v2/translate"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader,"application/json");
    request.setRawHeader("Authorization","DeepL-Auth-Key 03162040-9d4e-d418-d6dc-d34fce490bc1:fx");
    QJsonObject body;
    body.insert("text", QJsonValue::fromVariant(words));
    body["target_lang"] = "FR";
    body["source_lang"] = "ES";
    QJsonDocument doc(body);


    //send the read request
    qDebug() << url << body;
    QNetworkReply* reply = m_manager.post(request,doc.toJson());
    QObject::connect(reply, &QNetworkReply::finished, this, [this,words,reply](){
        qDebug()<<"Parsing "<<words;
        if (reply->error() == QNetworkReply::NoError){
            QJsonDocument jsonReply = QJsonDocument::fromJson(reply->readAll());
            qDebug()<<jsonReply;
            QString translation = jsonReply.object()["translations"].toArray()[0].toObject()["text"].toString();
            emit signalNewWordDefintion(words[0], {translation});
        }else
            // Erreur lors de la réception de la réponse
            qDebug() << "Erreur : " << reply->errorString();
        //if(!words.isEmpty())
        //    getWordsTranslation(words);
        //else
        //    emit signalFinishedParsing();
        reply->deleteLater();
    });
}

void NetworkManager::slotFinishedParsing()
{
    for(const auto &word:m_dico.keys()){
        qDebug() << "===========Word============";
        qDebug() << word + "\n";
        int i = 1;
        for(const auto &def:m_dico[word]){
            qDebug() << "==Definition " << i++;
            qDebug() << def << "\n";
        }
    }
}

QString NetworkManager::removeHTML(QString& line){
    QRegularExpression regEx(R"(<[^>]*>)", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatchIterator match;
    QRegularExpressionMatch grp;
    match = regEx.globalMatch(line);
    while(match.hasNext()){
        grp = match.next();
        line.replace(grp.captured(),"");
    }
    return line.trimmed();
}
void NetworkManager::parseHTMLAnswer(QNetworkReply* reply){
    const QString titleBalise("dico_title_2");
    const QString defBalise("grid_last");
    const QString motCroise("<span id=\"motcroise\">");
    QString line;
    QString multiLineDef;
    QString wordLine;
    QStringList definitions;
    bool multiLineParse = false;
    int i = 0;

    while (reply->canReadLine()) {
        line = QString::fromUtf8(reply->readLine()).trimmed();

        if(line.contains(motCroise))
            break;

        if(multiLineParse){
            if(!line.contains("</li>"))
                multiLineDef.append(line.replace("\n",""));
            else{
                multiLineParse=false;
                definitions.push_back(removeHTML(multiLineDef));
            }
        }
        if(wordLine.isEmpty() && line.contains(titleBalise)){
            wordLine = removeHTML(line);
        }
        if(line.contains(defBalise)){
            multiLineParse = true;
            multiLineDef.clear();
        }
        ++i;

    }
    m_dico.insert(wordLine,definitions);
    emit signalNewWordDefintion(wordLine,definitions);
}
