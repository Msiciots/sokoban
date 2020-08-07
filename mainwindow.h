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

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init_map(QString stage);
    void keyPressEvent(QKeyEvent *e);
    void update_map();
    void CheckWin();
    void key_move(int ud,int lr);

  private slots:
    void on_Start_clicked();
    void on_Restart_clicked();

  private:
    Ui::MainWindow *ui;

    QPixmap pix_wall;              // index 1
    QPixmap pix_ground;            // index 2
    QPixmap pix_box;               // index 3
    QPixmap pix_flag;              // index 4
    QPixmap pix_player;            // index 5
    QPixmap pix_box_on_flag;       // index 6
    QPixmap pix_player_on_flag;    // index 7

    int **map;
    QList<QLabel *> labels;
    int player_row,player_col;
    int box_row,box_col;
    int map_row,map_col;
    int countWin;
    int numBoxOnFlag;
    int StepCount;
    int current_map;
};

#endif // MAINWINDOW_H
