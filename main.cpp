#include "MainWindow.h"

#include <QApplication>
#include <ClippingParser.h>
#include "NetworkManager.h"
#include "ClippingParser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    ClippingParser p;
    p.readFile();
    w.show();

    NetworkManager manager;
    w.setNetworkManager(&manager);
    ClippingParser parser;
    //manager.getWordsDefinition({"mange","prie","aime"});
    //manager.getWordsTranslation({"hijo de puta","incondicional","vergenzoso"});

    return a.exec();
}
