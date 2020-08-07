#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "mainwindow.h"
namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

public slots:
    void on_StartButton_clicked();
    void on_ChooseButton_clicked();
    void on_QuitButton_clicked();
private:
    Ui::Menu *ui;
//    MainWindow game;
};

#endif // MENU_H
