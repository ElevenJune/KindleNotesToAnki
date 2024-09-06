#include "DictionnaryWidget.h"
#include "ui_DictionnaryWidget.h"

#include "models/BookModel.h"
#include "WordManager.h"

DictionnaryWidget::DictionnaryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DictionnaryWidget)
{
    ui->setupUi(this);
    //ui->definitionTextEdit->setReadOnly(true);
    connect(ui->searchButton,&QPushButton::clicked,this,[&](){emit signalSearchClicked(ui->wordLineEdit->text(),m_translationMode);});
    connect(ui->switchButton,&QPushButton::clicked,this,&DictionnaryWidget::slotSwitchTranlationMode);
}

DictionnaryWidget::~DictionnaryWidget()
{
    delete ui;
}

void DictionnaryWidget::fillDefinition(const QString &word, const QStringList &definitions)
{
    QPlainTextEdit* te = ui->definitionTextEdit;
    te->clear();
    te->appendHtml(QString("<strong>%0</strong></br>").arg(word));
    int i = 1;
    for(const QString& def : definitions)
    {
        te->appendHtml(QString("<u>Définition %0</u></br>").arg(i++));
        te->appendPlainText(def+"\n");
    }
}

void DictionnaryWidget::fillBookList()
{
    ui->bookList->clear();
    const QList<BookModel*>& books = WordManager::getInstance().getBooks();
    for(int i = 0; i < books.count(); ++i){
        BookModel* bm = books[i];
        ui->bookList->appendHtml(QString("<strong>%0 - </strong>%1</br>")
                                     .arg(i)
                                     .arg(bm->getName()));
        for(auto& w : bm->getWords())
            ui->bookList->appendPlainText(QString("     - %0").arg(w->getWord()));
    }
}

void DictionnaryWidget::slotSwitchTranlationMode()
{
    m_translationMode=!m_translationMode;
    ui->searchButton->setText(m_translationMode? "Translate" : "Get Definition");
}
