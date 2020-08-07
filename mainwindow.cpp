﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QPushButton>
#include <iostream>
#include <fstream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setFocus();
}

void MainWindow::init_map(QString stage) {
    // read map
    current_map = stage.toInt();
    QString file_path = ":/res/maps/map"+stage+".txt";
    QFile mapfile(file_path);
    mapfile.open(QIODevice::ReadOnly);
    QTextStream textstream(&mapfile);

    textstream >> map_col >> map_row;
    map = new int*[map_row];
    for (int i = 0; i < map_row; ++i)map[i] = new int[map_col];
    for(int i=0; i<map_row; ++i) {
        for(int j=0; j<map_col; ++j) {
            map[i][j]=0;
        }
    }

    countWin=0;
    numBoxOnFlag=0;
    StepCount = 0;
    ui->label->setText("Steps: "+QString::number(StepCount));

    for(int i=0; i<map_row; ++i) {
        for(int j=0; j<map_col; ++j) {
            textstream >> map[i][j];
            if(map[i][j]==4) {
                countWin++;
            } else if(map[i][j]==6) {
                numBoxOnFlag++;
            }
        }
        for (int i = 0; i < map_row*map_col; ++i)
            labels << new QLabel(this);

        pix_wall.load(":/res/wall.png");             // index 1
        pix_ground.load(":/res/ground.png");         // index 2
        pix_box.load(":/res/box.png");         // index 3
        pix_flag.load(":/res/flag.png");         // index 4
        pix_player.load(":/res/player.png");   // index 5
        pix_box_on_flag.load(":/res/box_on_flag.png");// index 6
        pix_player_on_flag.load(":/res/player_on_flag.png");// index 7
        for (int i = 0; i < labels.length(); ++i)
            labels.at(i)->clear();

        int base_x=100;
        int base_y=100;
        for (int i = 0; i < map_row*map_col; ++i) {
            labels.at(i)->setGeometry(base_x+((i%map_col)-1)*50,base_y+(i/map_col)*50,50,50);
            if(map[i/map_col][i%map_col]==0) {
                labels.at(i)->clear();
            } else if(map[i/map_col][i%map_col]==1) {
                labels.at(i)->setPixmap(pix_wall);
            } else if(map[i/map_col][i%map_col]==2) {
                labels.at(i)->setPixmap(pix_ground);
            } else if(map[i/map_col][i%map_col]==3) {
                labels.at(i)->setPixmap(pix_box);
            } else if(map[i/map_col][i%map_col]==4) {
                labels.at(i)->setPixmap(pix_flag);

            } else if(map[i/map_col][i%map_col]==5) {
                labels.at(i)->setPixmap(pix_player);
                player_row=i/map_col;
                player_col=i%map_col;
            } else if(map[i/map_col][i%map_col]==6) {
                labels.at(i)->setPixmap(pix_box_on_flag);
            } else if(map[i/map_col][i%map_col]==7) {
                labels.at(i)->setPixmap(pix_player_on_flag);
            }

            labels.at(i)->setScaledContents(true);
        }
    }
}

void MainWindow::update_map() {


    numBoxOnFlag=0;
    for (int i = 0; i < map_row*map_col; ++i) {
        if(map[i/map_col][i%map_col]==1) {
            labels.at(i)->setPixmap(pix_wall);
        } else if(map[i/map_col][i%map_col]==2) {
            labels.at(i)->setPixmap(pix_ground);
        } else if(map[i/map_col][i%map_col]==3) {
            labels.at(i)->setPixmap(pix_box);
        } else if(map[i/map_col][i%map_col]==4) {
            labels.at(i)->setPixmap(pix_flag);
        } else if(map[i/map_col][i%map_col]==5) {
            labels.at(i)->setPixmap(pix_player);
        } else if(map[i/map_col][i%map_col]==6) {
            labels.at(i)->setPixmap(pix_box_on_flag);
            numBoxOnFlag++;
        } else if(map[i/map_col][i%map_col]==7) {
            labels.at(i)->setPixmap(pix_player_on_flag);
        }
        labels.at(i)->setScaledContents(true);
    }
    show();
}

void MainWindow::CheckWin() {
    if(countWin==numBoxOnFlag) {
        current_map++;
        init_map(QString::number(current_map));
    }
}
void MainWindow::on_Start_clicked() {

    init_map("1");
    setFocus();
}
void MainWindow::on_Restart_clicked() {

    init_map("2");
    setFocus();
}
void MainWindow::keyPressEvent(QKeyEvent *e) {

    switch(e->key()) {
    case Qt::Key_Up:
        key_move(-1,0);
        break;
    case Qt::Key_Down:
        key_move(1,0);
        break;
    case Qt::Key_Left:
        key_move(0,-1);
        break;
    case Qt::Key_Right:
        key_move(0,1);
        break;
    }
    update_map();
    CheckWin();
    ui->label->setText("Steps: "+QString::number(StepCount));
}
void MainWindow::key_move(int ud,int lr) {
    // move up -> ud=-1, lr=0
    // move down -> ud=1, lr=0
    // move left -> ud=0, lr=-1
    // move right -> ud=0, lr=1

    //player
    if(  map[player_row][player_col]==5  ) {
        //player ground
        if(map[player_row+ud][player_col+lr]==2) {
            map[player_row][player_col]=2;
            map[player_row+ud][player_col+lr]=5;
            player_row+=ud;
            player_col+=lr;
            StepCount++;
        }
        // player box
        else if(map[player_row+ud][player_col+lr]==3 ) {
            // player box ground
            if( map[player_row+2*ud][player_col+2*lr]==2) {
                map[player_row][player_col]= 2;
                map[player_row+ud][player_col+lr]= 5;
                map[player_row+2*ud][player_col+2*lr] =3;
                player_row+=ud;
                player_col+=lr;
                StepCount++;
            }
            //player box flag
            else if(map[player_row+2*ud][player_col+2*lr]==4 ) {
                map[player_row][player_col]= 2;
                map[player_row+ud][player_col+lr]= 5;
                map[player_row+2*ud][player_col+2*lr] =6;
                player_row+=ud;
                player_col+=lr;
                StepCount++;
            }
        }
        //player flag
        else if(map[player_row+ud][player_col+lr]==4) {
            map[player_row][player_col]=2;
            map[player_row+ud][player_col+lr]=7;
            player_row+=ud;
            player_col+=lr;
            StepCount++;
        }
        //player Fbox
        else if(map[player_row+ud][player_col+lr]==6 ) {
            //player Fbox ground
            if(map[player_row+2*ud][player_col+2*lr]==2) {
                map[player_row][player_col]=2;
                map[player_row+ud][player_col+lr]=7;
                map[player_row+2*ud][player_col+2*lr]=3;
                player_row+=ud;
                player_col+=lr;
                StepCount++;
            }
            //player Fbox flag
            else if(map[player_row+2*ud][player_col+2*lr]==4) {
                map[player_row][player_col]=2;
                map[player_row+ud][player_col+lr]=7;
                map[player_row+2*ud][player_col+2*lr]=6;
                player_row+=ud;
                player_col+=lr;
                StepCount++;
            }
        }
    }
    //player on flag
    else if(map[player_row][player_col]==7) {
        //pf->flag
        if(map[player_row+ud][player_col+lr]==4 ) {
            map[player_row][player_col]=4;
            map[player_row+ud][player_col+lr]=7;
            player_row+=ud;
            player_col+=lr;
            StepCount++;
        }
        //pflag >ground
        else if(map[player_row+ud][player_col+lr]==2) {
            map[player_row][player_col]=4;
            map[player_row+ud][player_col+lr]=5;
            player_row+=ud;
            player_col+=lr;
            StepCount++;
        }
        //pflag ->box
        else if(map[player_row+ud][player_col+lr]==3) {
            // ->ground
            if(map[player_row+2*ud][player_col+2*lr]==2) {
                map[player_row][player_col]=4;
                map[player_row+ud][player_col+lr]=5;
                map[player_row+2*ud][player_col+2*lr]=3;
                player_row+=ud;
                player_col+=lr;
                StepCount++;
            }
            // ->flag
            else if(map[player_row-2][player_col]==4) {
                map[player_row][player_col]=4;
                map[player_row+ud][player_col+lr]=5;
                map[player_row+2*ud][player_col+2*lr]=6;
                player_row+=ud;
                player_col+=lr;
                StepCount++;
            }
        }
        //pflag ->Fbox
        else if(map[player_row+ud][player_col+lr]==6) {
            // ->ground
            if(map[player_row+2*ud][player_col+2*lr]==2) {
                map[player_row][player_col]=4;
                map[player_row+ud][player_col+lr]=7;
                map[player_row+2*ud][player_col+2*lr]=3;
                player_row+=ud;
                player_col+=lr;
                StepCount++;
            }
            //->flag
            else if(map[player_row+2*ud][player_col+2*lr]==4) {
                map[player_row][player_col]=4;
                map[player_row+ud][player_col+lr]=7;
                map[player_row+2*ud][player_col+2*lr]=6;
                player_row+=ud;
                player_col+=lr;
                StepCount++;
            }
        }
    }
}

MainWindow::~MainWindow() {
    delete ui;
}


