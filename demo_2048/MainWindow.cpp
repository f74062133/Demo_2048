#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand( time(NULL) );
    isMoving = false;
    hasOver = false;
    hasWon = false;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            blocks[i][j] = NULL;

    while(!spawnBlock());
    while(!spawnBlock());
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::spawnBlock(){
    int r = rand()%4;
    int c = rand()%4;
    if(blocks[r][c] == NULL){
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
    else{
        if(!isMoving){
            isMoving = true;
            if(event->key() == Qt::Key_Up){
                for(int j = 0; j < 4; j++){
                    for(int i = 0; i < 4; i++){
                        if(blocks[i][j] != NULL){
                            int targetR = i;
                            for(int k = i - 1; k >= 0; k--){
                                if(blocks[k][j] == NULL){
                                    targetR = k;
                                    continue;
                                }
                                else{
                                    if(collide(i,j,k,j)) targetR = k;
                                    else targetR = k + 1;
                                    break;
                                }
                            }
                            blocks[i][j]->move(targetR, j, &blocks[targetR][j]);
                            if(targetR != i){
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
                        if(blocks[i][j] != NULL){
                            int targetR = i;
                            for(int k = i + 1; k < 4; k++){
                                if(blocks[k][j] == NULL){
                                    targetR = k;
                                    continue;
                                }
                                else{
                                    if(collide(i,j,k,j)) targetR = k;
                                    else targetR = k - 1;
                                    break;
                                }
                            }
                            blocks[i][j]->move(targetR, j, &blocks[targetR][j]);
                            if(targetR != i){
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
                        if(blocks[i][j] != NULL){
                            int targetC = j;
                            for(int k = j - 1; k >= 0; k--){
                                if(blocks[i][k] == NULL){
                                    targetC = k;
                                    continue;
                                }
                                else{
                                    if(collide(i,j,i,k)) targetC = k;
                                    else targetC = k + 1;
                                    break;
                                }
                            }
                            blocks[i][j]->move(i, targetC, &blocks[i][targetC]);
                            if(targetC != j){
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
                        if(blocks[i][j] != NULL){
                            int targetC = j;
                            for(int k = j + 1; k < 4; k++){
                                if(blocks[i][k] == NULL){
                                    targetC = k;
                                    continue;
                                }
                                else{
                                    if(collide(i,j,i,k)) targetC = k;
                                    else targetC = k - 1;
                                    break;
                                }
                            }
                            blocks[i][j]->move(i, targetC, &blocks[i][targetC]);
                            if(targetC != j){
                                blocks[i][j] = NULL;
                                updated = true;
                            }
                        }
                    }
                }
            }
            isMoving = false;
        }
        if(updated)
            while(!spawnBlock());
        else
            testOver();
    }
}

bool MainWindow::collide(int curR, int curC, int targetR, int targetC){
    if(blocks[curR][curC] == NULL || blocks[targetR][targetC] == NULL) return false;
    if(blocks[targetR][targetC]->isMerged) return false;
    if(blocks[curR][curC]->number == blocks[targetR][targetC]->number) return true;
    else return false;

}

bool MainWindow::testOver(){
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(blocks[i][j] == NULL) return false;
    hasOver = true;
    cout<<"Game Over"<<endl;
    return true;
}
