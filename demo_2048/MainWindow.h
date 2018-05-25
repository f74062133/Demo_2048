#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include <QFile>
#include <QTextStream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include "NumberBlock.h"
#include "GameoverDialog.h"
#include "RestartDialog.h"
#include "WinDialog.h"
#include "MenuDialog.h"
using namespace std;

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

public slots:
    void addScore(int s);
    void tryAgain();
    void cancel();
    void win();

private:
    void setup();
    bool spawnBlock();
    bool hasBlock(int row, int col);
    bool collide(int curRow, int curCol, int targetRow, int targetCol);
    void testOver();

    Ui::MainWindow *ui;
    NumberBlock* blocks[4][4];
    GameoverDialog* gameOverDialog;
    RestartDialog* restartDialog;
    WinDialog* winDialog;
    MenuDialog* menuDialog;
    QTimer* unlockTimer;
    int score;
    int bestScore;
    bool isMoving;
    bool hasOver;
    bool hasWon;

private slots:
    void unlockKeyboard();
    void restart();
    void openMenu();
    void setColor(int hue);

};

#endif // MAINWINDOW_H
