#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class DictionnaryWidget;
class NetworkManager;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    DictionnaryWidget* dictionnaryWidget(){return m_dico;}
    void setNetworkManager(NetworkManager* nm);

private:
    Ui::MainWindow *ui;
    DictionnaryWidget* m_dico;
    NetworkManager* m_network;
};
#endif // MAINWINDOW_H
