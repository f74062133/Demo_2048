#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(NULL));
    bestScore = 0;
    hasOver = false;
    gameOverDialog = NULL;
    restartDialog = NULL;
    winDialog = NULL;
    unlockTimer = new QTimer();

    ui->bestScoreTextLabel->setText(QString::number(bestScore));

    connect(unlockTimer, SIGNAL(timeout()), this, SLOT(unlockKeyboard()));
    connect(ui->restartBtn, SIGNAL(clicked(bool)), this, SLOT(restart()));

    setup();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setup(){
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++){
            if(hasBlock(i, j) && hasOver) delete blocks[i][j];
            blocks[i][j] = NULL;
        }

    score = 0;
    ui->scoreTextLabel->setText(QString::number(score));
    isMoving = false;
    hasOver = false;
    hasWon = false;

    while(!spawnBlock());
    while(!spawnBlock());
}

bool MainWindow::hasBlock(int row, int col){
    if(row < 0 || row > 3 || col < 0 || col > 3) return false;
    if(blocks[row][col] == NULL) return false;
    else return true;
}

bool MainWindow::spawnBlock(){
    int r = rand()%4;
    int c = rand()%4;
    if(!hasBlock(r, c)){
        NumberBlock* nb = new NumberBlock(this, r, c);
        blocks[r][c] = nb;
        return true;
    }
    else
        return false;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    bool updated = false;
    if(hasOver) return;

    if(isMoving) return;
    isMoving = true;
    if(event->key() == Qt::Key_Up){
        for(int j = 0; j < 4; j++){
            for(int i = 0; i < 4; i++){
                if(hasBlock(i, j)){
                    int targetRow = i;
                    for(int k = i - 1; k >= 0; k--){
                        if(!hasBlock(k, j)){
                            targetRow = k;
                            continue;
                        }
                        else{
                            if(collide(i, j, k, j)) targetRow = k;
                            else targetRow = k + 1;
                            break;
                        }
                    }
                    blocks[i][j]->move(targetRow, j, &blocks[targetRow][j]);
                    if(targetRow != i){
                        blocks[i][j] = NULL;
                        updated = true;
                    }
                }
            }
        }
    }
    else if(event->key()==Qt::Key_Down){
        for(int j = 0; j < 4; j++){
            for(int i = 3; i >= 0; i--){
                if(hasBlock(i, j)){
                    int targetRow = i;
                    for(int k = i + 1; k < 4; k++){
                        if(!hasBlock(k, j)){
                            targetRow = k;
                            continue;
                        }
                        else{
                            if(collide(i, j, k, j)) targetRow = k;
                            else targetRow = k - 1;
                            break;
                        }
                    }
                    blocks[i][j]->move(targetRow, j, &blocks[targetRow][j]);
                    if(targetRow != i){
                        blocks[i][j] = NULL;
                        updated = true;
                    }
                }
            }
        }
    }
    else if(event->key()==Qt::Key_Left){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(hasBlock(i, j)){
                    int targetCol = j;
                    for(int k = j - 1; k >= 0; k--){
                        if(!hasBlock(i, k)){
                            targetCol = k;
                            continue;
                        }
                        else{
                            if(collide(i, j, i, k)) targetCol = k;
                            else targetCol = k + 1;
                            break;
                        }
                    }
                    blocks[i][j]->move(i, targetCol, &blocks[i][targetCol]);
                    if(targetCol != j){
                        blocks[i][j] = NULL;
                        updated = true;
                    }
                }
            }
        }
    }
    else if(event->key()==Qt::Key_Right){
        for(int i = 0; i < 4; i++){
            for(int j = 3; j >= 0; j--){
                if(hasBlock(i, j)){
                    int targetCol = j;
                    for(int k = j + 1; k < 4; k++){
                        if(!hasBlock(i, k)){
                            targetCol = k;
                            continue;
                        }
                        else{
                            if(collide(i, j, i, k)) targetCol = k;
                            else targetCol = k - 1;
                            break;
                        }
                    }
                    blocks[i][j]->move(i, targetCol, &blocks[i][targetCol]);
                    if(targetCol != j){
                        blocks[i][j] = NULL;
                        updated = true;
                    }
                }
            }
        }
    }

    if(updated)
        while(!spawnBlock());
    else
        testOver();

    unlockTimer->start(250);

}

bool MainWindow::collide(int curRow, int curCol, int targetRow, int targetCol){
    if(!hasBlock(curRow, curCol) || !hasBlock(targetRow, targetCol)) return false;
    if(blocks[targetRow][targetCol]->isMerged) return false;
    if(blocks[curRow][curCol]->number == blocks[targetRow][targetCol]->number) return true;
    else return false;
}

void MainWindow::testOver(){
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++){
            if(!hasBlock(i, j)) return;
            if(hasBlock(i-1, j) && blocks[i-1][j]->number == blocks[i][j]->number) return;
            if(hasBlock(i+1, j) && blocks[i+1][j]->number == blocks[i][j]->number) return;
            if(hasBlock(i, j-1) && blocks[i][j-1]->number == blocks[i][j]->number) return;
            if(hasBlock(i, j+1) && blocks[i][j+1]->number == blocks[i][j]->number) return;
        }
    hasOver = true;
    gameOverDialog = new GameoverDialog(this, "You got " + QString::number(score) + " points.");
}

void MainWindow::unlockKeyboard(){
    unlockTimer->stop();
    isMoving = false;
}

void MainWindow::addScore(int s){
    score += s;
    ui->scoreTextLabel->setText(QString::number(score));
    if(score > bestScore){
        bestScore = score;
        ui->bestScoreTextLabel->setText(QString::number(bestScore));
    }
}

void MainWindow::tryAgain(){
    if(gameOverDialog != NULL){
        delete gameOverDialog;
        gameOverDialog = NULL;
    }

    if(restartDialog != NULL){
        delete restartDialog;
        restartDialog = NULL;
    }

    hasOver = true;
    setup();
}

void MainWindow::restart(){
    restartDialog = new RestartDialog(this);
}

void MainWindow::cancel(){
    if(restartDialog != NULL){
        delete restartDialog;
        restartDialog = NULL;
    }
    if(winDialog != NULL){
        delete winDialog;
        winDialog = NULL;
    }
}

void MainWindow::win(){
    if(hasWon) return;
    hasWon = true;
    winDialog = new WinDialog(this);
}
