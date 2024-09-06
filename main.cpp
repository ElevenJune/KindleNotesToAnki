#include "MainWindow.h"

#include <QApplication>
#include <ClippingParser.h>
#include "NetworkManager.h"
#include "ClippingParser.h"
#include "DictionnaryWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    NetworkManager manager;
    w.setNetworkManager(&manager);
    ClippingParser p;
    QObject::connect(&p,&ClippingParser::signalFileRead,w.dictionnaryWidget(),&DictionnaryWidget::fillBookList);
    p.readFile();
    //manager.getWordsDefinition({"mange","prie","aime"});
    //manager.getWordsTranslation({"hijo de puta","incondicional","vergenzoso"});

    return a.exec();
}
