#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "DictionnaryWidget.h"
#include "NetworkManager.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      m_dico(new DictionnaryWidget(this))
{
    ui->setupUi(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(ui->centralwidget);
    mainLayout->addWidget(m_dico);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setNetworkManager(NetworkManager *nm)
{
    m_network=nm;
    if(!nm)
        return;
    connect(m_network,&NetworkManager::signalNewWordDefintion,this,[&](QString word, QStringList definitions){
        m_dico->fillDefinition(word,definitions);
    });
    connect(m_dico,&DictionnaryWidget::signalSearchClicked, this, [&](QString word, bool translation){
        if(!translation)
            m_network->getWordsDefinition({word});
        else
            m_network->getWordsTranslation({word});
    });
}

