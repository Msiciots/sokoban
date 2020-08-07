
#include "mainwindow.h"
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
    ui(new Ui::MainWindow)
{
        ui->setupUi(this);
 // connect(ui->Restart,SIGNAL(clicked()),this,SLOT(Restart()));
 //   connect(this,SIGNAL(add_signal()),this,SLOT(Restart()));



    setFocus();



}

void MainWindow::init_map(QString stage){
    // read map
    current_map = stage.toInt();
    QString file_path = ":/res/maps/map"+stage+".txt";
    QFile mapfile(file_path);
    mapfile.open(QIODevice::ReadOnly);
    QTextStream textstream(&mapfile);



    textstream >> map_col >> map_row;

map = new int*[map_row];
      //  qDebug() <<"*******";
    for (int i = 0; i < map_row; ++i)map[i] = new int[map_col];
//    qDebug() << "x:" << x;
    for(int i=0;i<map_row;++i){
        for(int j=0;j<map_col;++j){
           map[i][j]=0;
        }
    }

    countWin=0;
    numBoxOnFlag=0;

    for(int i=0;i<map_row;++i){
        for(int j=0;j<map_col;++j){
           textstream >> map[i][j];

           if(map[i][j]==4){
               countWin++;
           }
           else if(map[i][j]==6){
               numBoxOnFlag++;
           }
        }


    for (int i = 0; i < map_row*map_col; ++i)
       labels << new QLabel(this);  // 0~71

    int base_x=100;
    int base_y=100;

    pix_wall.load(":/res/wall.png");             // index 1
    pix_ground.load(":/res/ground.png");         // index 2
    pix_box.load(":/res/box.png");         // index 3
    pix_flag.load(":/res/flag.png");         // index 4
    pix_player.load(":/res/player.png");   // index 5
    pix_box_on_flag.load(":/res/box_on_flag.png");// index 6

    for (int i = 0; i < labels.length(); ++i)
        labels.at(i)->clear();
    for (int i = 0; i < map_row*map_col; ++i){
       labels.at(i)->setGeometry(base_x+((i%map_col)-1)*50,base_y+(i/map_col)*50,50,50);
       if(map[i/map_col][i%map_col]==0){
           labels.at(i)->clear();
       }
       else if(map[i/map_col][i%map_col]==1){
           labels.at(i)->setPixmap(pix_wall);
       }
       else if(map[i/map_col][i%map_col]==2){
        labels.at(i)->setPixmap(pix_ground);
       }
       else if(map[i/map_col][i%map_col]==3){
        labels.at(i)->setPixmap(pix_box);
       }
       else if(map[i/map_col][i%map_col]==4){
        labels.at(i)->setPixmap(pix_flag);

       }
       else if(map[i/map_col][i%map_col]==5){
        labels.at(i)->setPixmap(pix_player);
        player_row=i/map_col;
        player_col=i%map_col;
       }
       else if(map[i/map_col][i%map_col]==6){
        labels.at(i)->setPixmap(pix_box_on_flag);
       }

       labels.at(i)->setScaledContents(true);
    }
    }
}




void MainWindow::update_map(){


    numBoxOnFlag=0;
    for (int i = 0; i < map_row*map_col; ++i){

       if(map[i/map_col][i%map_col]==1){
           labels.at(i)->setPixmap(pix_wall);
       }
       else if(map[i/map_col][i%map_col]==2){
        labels.at(i)->setPixmap(pix_ground);
       }
       else if(map[i/map_col][i%map_col]==3){
           labels.at(i)->setPixmap(pix_box);
           }
       else if(map[i/map_col][i%map_col]==4){
        labels.at(i)->setPixmap(pix_flag);
       }
       else if(map[i/map_col][i%map_col]==5){
        labels.at(i)->setPixmap(pix_player);
       }
       else if(map[i/map_col][i%map_col]==6){
        labels.at(i)->setPixmap(pix_box_on_flag);

        numBoxOnFlag++;
       }

       labels.at(i)->setScaledContents(true);

    }
    show();
}





void MainWindow::CheckWin(){

    if(countWin==numBoxOnFlag)
{

        init_map("2");

}
}



MainWindow::~MainWindow()
{

    delete ui;
}





void MainWindow::on_Start_clicked()
{

    init_map("1");
    setFocus();

}

void MainWindow::on_Restart_clicked()
{

    init_map("2");
    setFocus();
}



void MainWindow::keyup(){


    //player
     if(  map[player_row][player_col]==5  ) {
    StepCount++;
           //player ground
          if(map[player_row-1][player_col]==2){

                map[player_row][player_col]=2;
                player_row--;
                map[player_row][player_col]=5;


               // update_map();


            }
          // player box
          else if(map[player_row-1][player_col]==3 ){
               // player box ground
              if( map[player_row-2][player_col]==2){
                      map[player_row][player_col]= 2;
                      player_row--;
                      map[player_row][player_col]= 5;
                      player_row--;
                      map[player_row][player_col] =3;
                      player_row++;

                     // update_map();
                }

              //player box flag
                 else if(map[player_row-2][player_col]==4 ){

                     map[player_row][player_col]= 2;
                     player_row--;
                     map[player_row][player_col]= 5;
                     player_row--;
                     map[player_row][player_col] =6;

                     player_row++;

                     //update_map();




                 }

          }


          //player flag
          else if(map[player_row-1][player_col]==4){
              map[player_row][player_col]=2;
              player_row--;
              map[player_row][player_col]=4;
             // update_map();


          }

          //player Fbox
           else if(map[player_row-1][player_col]==6 ){
                      //player Fbox ground
                   if(map[player_row-2][player_col]==2){
                    map[player_row][player_col]=2;

                    player_row--;
                    map[player_row][player_col]=4;
                    player_row--;
                    map[player_row][player_col]=3;
                    player_row++;
                   // update_map();
                   }
                   //player Fbox flag
                   else if(map[player_row-2][player_col]==4){
                       map[player_row][player_col]=2;
                       player_row--;
                       map[player_row][player_col]=4;
                       player_row--;
                       map[player_row][player_col]=6;
                       player_row++;
                      // update_map();

                   }

            }


       }





         //flag ->
         else if(map[player_row][player_col]==4){
         StepCount++;
             //flag->flag
             if(map[player_row-1][player_col]==4 ) {
                       map[player_row][player_col]=4;

                       player_row--;
                       map[player_row][player_col]=4;
                     //  update_map();
             }
             //flag _>ground
            else if(map[player_row-1][player_col]==2){
                  map[player_row][player_col]=4;
                  player_row--;
                  map[player_row][player_col]=5;
                  //update_map();
              }

             //flag ->box
             else if(map[player_row-1][player_col]==3){
                  // ->ground
                 if(map[player_row-2][player_col]==2){
                 map[player_row][player_col]=4;

                 player_row--;
                 map[player_row][player_col]=5;
                 player_row--;
                 map[player_row][player_col]=3;
                 player_row++;
                 //update_map();
                   }
                //->flag
                 else if(map[player_row-2][player_col]==4){

                  map[player_row][player_col]=4;

                  player_row--;
                  map[player_row][player_col]=5;
                  player_row--;
                  map[player_row][player_col]=6;
                  player_row++;
                  //update_map();
                 }


           }

             //flag ->Fbox
             else if(map[player_row-1][player_col]==6){
                  // ->ground
                 if(map[player_row-2][player_col]==2){
                 map[player_row][player_col]=4;

                 player_row--;
                 map[player_row][player_col]=4;
                 player_row--;
                 map[player_row][player_col]=3;
                 player_row++;
                // update_map();
                   }
                //->flag
                 else if(map[player_row-2][player_col]==4){

                  map[player_row][player_col]=4;

                  player_row--;
                  map[player_row][player_col]=4;
                  player_row--;
                  map[player_row][player_col]=6;
                  player_row++;
                  //update_map();
                 }

           }

       }



}


void MainWindow::keydown(){


    //player
     if(  map[player_row][player_col]==5  ) {
        StepCount++;
           //player ground
          if(map[player_row+1][player_col]==2){

                map[player_row][player_col]=2;
                player_row++;
                map[player_row][player_col]=5;


               // update_map();


            }
          // player box
          else if(map[player_row+1][player_col]==3 ){
               // player box ground
              if( map[player_row+2][player_col]==2){
                      map[player_row][player_col]= 2;
                      player_row++;
                      map[player_row][player_col]= 5;
                      player_row++;
                      map[player_row][player_col] =3;
                      player_row--;

                     // update_map();
                }

              //player box flag
                 else if(map[player_row+2][player_col]==4 ){

                     map[player_row][player_col]= 2;
                     player_row++;
                     map[player_row][player_col]= 5;
                     player_row++;
                     map[player_row][player_col] =6;
                     player_row--;

                   //  update_map();


                     numBoxOnFlag++;

                 }

          }


          //player flag
          else if(map[player_row+1][player_col]==4){
              map[player_row][player_col]=2;
              player_row++;
              map[player_row][player_col]=4;
             // update_map();


          }

          //player Fbox
           else if(map[player_row+1][player_col]==6 ){
                      //player Fbox ground
                   if(map[player_row+2][player_col]==2){
                    map[player_row][player_col]=2;

                    player_row++;
                    map[player_row][player_col]=4;
                    player_row++;
                    map[player_row][player_col]=3;
                    player_row--;
                   // update_map();
                   }
                   //player Fbox flag
                   else if(map[player_row+2][player_col]==4){
                       map[player_row][player_col]=2;
                       player_row++;
                       map[player_row][player_col]=4;
                       player_row++;
                       map[player_row][player_col]=6;
                       player_row--;
                    //   update_map();

                   }

            }


       }





         //flag ->
         else if(map[player_row][player_col]==4){
         StepCount++;
             //flag->flag
             if(map[player_row+1][player_col]==4 ) {
                       map[player_row][player_col]=4;

                       player_row++;
                       map[player_row][player_col]=4;
                   //    update_map();
             }
             //flag _>ground
            else if(map[player_row+1][player_col]==2){
                  map[player_row][player_col]=4;
                  player_row++;
                  map[player_row][player_col]=5;
                //  update_map();
              }

             //flag ->box
             else if(map[player_row+1][player_col]==3){
                  // ->ground
                 if(map[player_row+2][player_col]==2){
                 map[player_row][player_col]=4;

                 player_row++;
                 map[player_row][player_col]=5;
                 player_row++;
                 map[player_row][player_col]=3;
                 player_row--;
                // update_map();
                   }
                //->flag
                 else if(map[player_row+2][player_col]==4){

                  map[player_row][player_col]=4;

                  player_row++;
                  map[player_row][player_col]=5;
                  player_row++;
                  map[player_row][player_col]=6;
                  player_row--;

                 // update_map();
                 }


           }

             //flag ->Fbox
             else if(map[player_row+1][player_col]==6){
                  // ->ground
                 if(map[player_row+2][player_col]==2){
                 map[player_row][player_col]=4;

                 player_row++;
                 map[player_row][player_col]=4;
                 player_row++;
                 map[player_row][player_col]=3;
                 player_row--;
                // update_map();
                   }
                //->flag
                 else if(map[player_row+2][player_col]==4){

                  map[player_row][player_col]=4;

                  player_row++;
                  map[player_row][player_col]=4;
                  player_row++;
                  map[player_row][player_col]=6;
                  player_row--;
                 // update_map();
                 }

           }

       }

}


void MainWindow::keyleft(){


    //player
         if(  map[player_row][player_col]==5  ) {
            StepCount++;
               //player ground
              if(map[player_row][player_col-1]==2){

                    map[player_row][player_col]=2;
                    player_col--;
                    map[player_row][player_col]=5;


                    //update_map();


                }
              else if(map[player_row][player_col-1]==7)
             {
                map[player_row][player_col]=2;
                player_col--;
                map[player_row][player_col]=7;

              }
              // player box
              else if(map[player_row][player_col-1]==3 ){
                   // player box ground
                  if( map[player_row][player_col-2]==2){
                          map[player_row][player_col]= 2;
                          player_col--;
                          map[player_row][player_col]= 5;
                          player_col--;
                          map[player_row][player_col] =3;
                          player_col++;

                        //  update_map();
                    }

                  //player box flag
                     else if(map[player_row][player_col-2]==4 ){

                         map[player_row][player_col]= 2;
                         player_col--;
                         map[player_row][player_col]= 5;
                         player_col--;
                         map[player_row][player_col] =6;
                         player_col++;

                       //  update_map();


                         numBoxOnFlag++;

                     }

              }


              //player flag
              else if(map[player_row][player_col-1]==4){
                  map[player_row][player_col]=2;
                  player_col--;
                  map[player_row][player_col]=4;
                 // update_map();


              }

              //player Fbox
               else if(map[player_row][player_col-1]==6 ){
                          //player Fbox ground
                       if(map[player_row][player_col-2]==2){
                        map[player_row][player_col]=2;

                        player_col--;
                        map[player_row][player_col]=4;
                        player_col--;
                        map[player_row][player_col]=3;
                        player_col++;
                       // update_map();
                       }
                       //player Fbox flag
                       else if(map[player_row][player_col-2]==4){
                           map[player_row][player_col]=2;
                           player_col--;
                           map[player_row][player_col]=4;
                           player_col--;
                           map[player_row][player_col]=6;
                           player_col++;
                         // update_map();

                       }

                }


           }





             //flag ->
             else if(map[player_row][player_col]==4){
             StepCount++;
                 //flag->flag
                 if(map[player_row][player_col-1]==4 ) {
                           map[player_row][player_col]=4;

                           player_col--;
                           map[player_row][player_col]=4;
                         //  update_map();
                 }
                 //flag _>ground
                else if(map[player_row][player_col-1]==2){
                      map[player_row][player_col]=4;
                      player_col--;
                      map[player_row][player_col]=5;
                     // update_map();
                  }

                 //flag ->box
                 else if(map[player_row][player_col-1]==3){
                      // ->ground
                     if(map[player_row][player_col-2]==2){
                     map[player_row][player_col]=4;

                     player_col--;
                     map[player_row][player_col]=5;
                     player_col--;
                     map[player_row][player_col]=3;
                     player_col++;
                    // update_map();
                       }
                    //->flag
                     else if(map[player_row][player_col-2]==4){

                      map[player_row][player_col]=4;

                      player_col--;
                      map[player_row][player_col]=5;
                      player_col--;
                      map[player_row][player_col]=6;
                      player_col++;
                     // update_map();
                     }


               }

                 //flag ->Fbox
                 else if(map[player_row][player_col-1]==6){
                      // ->ground
                     if(map[player_row][player_col-2]==2){
                     map[player_row][player_col]=4;

                     player_col--;
                     map[player_row][player_col]=4;
                     player_col--;
                     map[player_row][player_col]=3;
                     player_col++;
                     //update_map();
                       }
                    //->flag
                     else if(map[player_row][player_col-2]==4){

                      map[player_row][player_col]=4;

                      player_col--;
                      map[player_row][player_col]=4;
                      player_col--;
                      map[player_row][player_col]=6;
                      player_col++;
                    //  update_map();
                     }

               }

           }



}

void MainWindow::keyright(){



 //player
  if(  map[player_row][player_col]==5  ) {
      StepCount++;

        //player ground
       if(map[player_row][player_col+1]==2){

             map[player_row][player_col]=2;
             player_col++;
             map[player_row][player_col]=5;


            // update_map();


         }

       // player box
       else if(map[player_row][player_col+1]==3 ){
            // player box ground
           if( map[player_row][player_col+2]==2){
                   map[player_row][player_col]= 2;
                   player_col++;
                   map[player_row][player_col]= 5;
                   player_col++;
                   map[player_row][player_col] =3;
                   player_col--;

                  // update_map();
             }

           //player box flag
              else if(map[player_row][player_col+2]==4 ){

                  map[player_row][player_col]= 2;
                  player_col++;
                  map[player_row][player_col]= 5;
                  player_col++;
                  map[player_row][player_col] =6;
                  player_col--;

                 // update_map();


                  numBoxOnFlag++;

              }

       }


       //player flag
       else if(map[player_row][player_col+1]==4){
           map[player_row][player_col]=2;
           player_col++;
           map[player_row][player_col]=4;
           //update_map();


       }

       //player Fbox
        else if(map[player_row][player_col+1]==6 ){
                   //player Fbox ground
                if(map[player_row][player_col+2]==2){
                 map[player_row][player_col]=2;

                 player_col++;
                 map[player_row][player_col]=4;
                 player_col++;
                 map[player_row][player_col]=3;
                 player_col--;
                // update_map();
                }
                //player Fbox flag
                else if(map[player_row][player_col+2]==4){
                    map[player_row][player_col]=2;
                    player_col++;
                    map[player_row][player_col]=4;
                    player_col++;
                    map[player_row][player_col]=6;
                    player_col--;
                   // update_map();

                }

         }


    }





      //flag ->
      else if(map[player_row][player_col]==4){
      StepCount++;
          //flag->flag
          if(map[player_row][player_col+1]==4 ) {
                    map[player_row][player_col]=4;

                    player_col++;
                    map[player_row][player_col]=4;
                    update_map();
          }
          //flag _>ground
         else if(map[player_row][player_col]==4 && map[player_row][player_col+1]==2){
               map[player_row][player_col]=4;
               player_col++;
               map[player_row][player_col]=5;
               update_map();
           }

          //flag ->box
          else if(map[player_row][player_col+1]==3){
               // ->ground
              if(map[player_row][player_col+2]==2){
              map[player_row][player_col]=4;

              player_col++;
              map[player_row][player_col]=5;
              player_col++;
              map[player_row][player_col]=3;
              player_col--;
              update_map();
                }
             //->flag
              else if(map[player_row][player_col+2]==4){

               map[player_row][player_col]=4;

               player_col++;
               map[player_row][player_col]=5;
               player_col++;
               map[player_row][player_col]=6;
               player_col--;
               update_map();
              }


        }

          //flag ->Fbox
          else if(map[player_row][player_col+1]==6){
               // ->ground
              if(map[player_row][player_col+2]==2){
              map[player_row][player_col]=4;

              player_col++;
              map[player_row][player_col]=4;
              player_col++;
              map[player_row][player_col]=3;
              player_col--;
              update_map();
                }
             //->flag
              else if(map[player_row][player_col+2]==4){

               map[player_row][player_col]=4;

               player_col++;
               map[player_row][player_col]=4;
               player_col++;
               map[player_row][player_col]=6;
               player_col--;
               update_map();
              }

        }

    }
}




void MainWindow::keyPressEvent(QKeyEvent *e){

    //if(Begin==1){
    switch(e->key()){

       case Qt::Key_Up:
            keyup();


        break;
     case Qt::Key_Down:
           keydown();


        break;

        case Qt::Key_Left:
            keyleft();



               break;

        case Qt::Key_Right:
            keyright();

        break;
   // }
    }
    update_map();
    CheckWin();

    QString Step = QString::number(StepCount);

    ui->label->setText(Step);




}



