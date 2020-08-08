#include "menu.h"
#include "ui_menu.h"
#include <QFileInfo>
#include <QDebug>
Menu::Menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu) {

    ui->setupUi(this);
    checkMaps();

    this->setWindowTitle("Sokoban");
    this->setFixedSize(300,500);
    ui->StartButton->setGeometry(100,150,100,50);
    ui->comboBox->setGeometry(100,220,100,50);
    ui->QuitButton->setGeometry(100,290,100,50);
    QPixmap bkgnd(":/res/menu.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    }


void Menu::on_StartButton_clicked() {

//    ui->setupUi(this);
    MainWindow * game = new MainWindow();

    game->init_map(QString::number(ui->comboBox->currentIndex()+1));
    game->show();
    this->setWindowTitle("Sokoban");
    qDebug() << "Start game";
    this->hide();
}
//void Menu::on_ChooseButton_clicked() {

//    qDebug()<<ui->textEdit->toPlainText();
//    MainWindow * game = new MainWindow();
//    game->init_map(ui->textEdit->toPlainText());
//    game->show();
//    this->hide();
//}

void Menu::on_QuitButton_clicked() {
    this->close();
}
void Menu::checkMaps() {
    map_count=1;
    QString file_path = "./maps/map"+QString::number(map_count)+".txt";
    QFileInfo check_file(file_path);
    while(check_file.exists() && check_file.isFile()){
        ui->comboBox->addItem("Level "+QString::number(map_count),map_count);
        qDebug() << "Add map"<<map_count<<".txt";
        map_count++;
        file_path = "./maps/map"+QString::number(map_count)+".txt";
        check_file.setFile(file_path);
    }
}
Menu::~Menu() {

    delete ui;
}
