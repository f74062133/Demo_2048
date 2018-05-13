#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "NumberBlock.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <QLabel>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    NumberBlock* blocks[4][4];
    QLabel* gameOverDialog;
    QLabel* winGameDialog;
    bool isMoving;
    bool hasOver;
    bool hasWon;

    bool spawnBlock();
    bool collide(int curR, int curC, int targetR, int targetC);
    bool testOver();
    void gameOver();
    void win();
};

#endif // MAINWINDOW_H
