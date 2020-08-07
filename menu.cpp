#include "menu.h"
#include "ui_menu.h"

#include <QDebug>
Menu::Menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu) {
    ui->setupUi(this);
}


void Menu::on_StartButton_clicked() {

//    ui->setupUi(this);
    MainWindow * game = new MainWindow();
    game->init_map("1");
    game->show();
    qDebug() << "show game";
    this->hide();
}
void Menu::on_ChooseButton_clicked() {

    qDebug()<<ui->textEdit->toPlainText();
    MainWindow * game = new MainWindow();
    game->init_map(ui->textEdit->toPlainText());
    game->show();
    this->hide();
}

void Menu::on_QuitButton_clicked() {
    this->close();
}

Menu::~Menu() {

    delete ui;
}
