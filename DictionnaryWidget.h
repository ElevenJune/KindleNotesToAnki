#ifndef DICTIONNARYWIDGET_H
#define DICTIONNARYWIDGET_H

#include <QWidget>

namespace Ui {
class DictionnaryWidget;
}

class DictionnaryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DictionnaryWidget(QWidget *parent = nullptr);
    ~DictionnaryWidget();

    void fillDefinition(const QString& word, const QStringList& definitions);
    void fillBookList();

signals:
    void signalSearchClicked(QString word, bool translation);

private slots:
    void slotSwitchTranlationMode();

private:
    Ui::DictionnaryWidget *ui;
    bool m_translationMode;
};

#endif // DICTIONNARYWIDGET_H
