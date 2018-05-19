#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "NumberBlock.h"
#include "GameoverDialog.h"
#include "RestartDialog.h"
#include "WinDialog.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <QLabel>
#include <QTimer>
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

public slots:
    void addScore(int s);
    void tryAgain();
    void cancel();
    void win();

private slots:
    void unlockKeyboard();
    void restart();

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
    QTimer* unlockTimer;
    int score;
    int bestScore;
    bool isMoving;
    bool hasOver;
    bool hasWon;

};

#endif // MAINWINDOW_H
