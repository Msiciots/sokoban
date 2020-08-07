#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QLabel>
#include <iostream>
#include <fstream>

using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init_map(QString stage);
    void init_map2(QString stage);
    void draw_map(int row,int col);
    void keyPressEvent(QKeyEvent *e);
    void update_map();
    void CheckWin();
    void keyup();
    void keydown();
    void keyleft();
    void keyright();






private slots:
    void on_Start_clicked();

    void on_Restart_clicked();


private:
    Ui::MainWindow *ui;
    QList<QLabel *> labels;

    QPixmap pix_wall;    // index 1
    QPixmap pix_ground;        // index 2
    QPixmap pix_box;        // index 3
    QPixmap pix_flag;         // index 4
    QPixmap pix_player;  // index 5
    QPixmap pix_box_on_flag; // index 6

    int player_row,player_col;
    int box_row,box_col;
    int **map;



    int map_row,map_col;
    int countWin;
    int numBoxOnFlag;
    int StepCount;

    int current_map;



};

#endif // MAINWINDOW_H
