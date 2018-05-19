#include "NumberBlock.h"
#include <iostream>
using namespace std;

NumberBlock::NumberBlock(QWidget* parent, int r, int c)
    :QLabel(parent)
{
    size = 1;
    resizeState = 0;
    row = r; col = c;
    posX = 25 + 100 * col;
    posY = 240 + 100 * row;
    curX = posX; curY = posY;
    bgColor = 240;
    textColor = 80;
    number = 2;
    trashTmp = NULL;
    QString n = QString::number(number);

    setGeometry(posX, posY, size, size);
    setText(n);
    setColor();
    setAlignment(Qt::AlignCenter);
    show();

    spawnTimer = new QTimer(parent);
    connect(spawnTimer, SIGNAL(timeout()), this, SLOT(spawning()));
    moveTimer = new QTimer(parent);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(moving()));
    mergeTimer = new QTimer(parent);
    connect(mergeTimer, SIGNAL(timeout()), this, SLOT(merging()));

    connect(this, SIGNAL(getScore(int)), parent, SLOT(addScore(int)));
    connect(this, SIGNAL(win()), parent, SLOT(win()));

    spawnTimer->start(20);
}

NumberBlock::~NumberBlock(){
    disconnect(spawnTimer, 0, 0, 0);
    disconnect(moveTimer, 0, 0, 0);
    disconnect(mergeTimer, 0, 0, 0);
    delete spawnTimer;
    delete moveTimer;
    delete mergeTimer;
}

void NumberBlock::setColor(){
    QString bgc = "rgb(" + QString::number(bgColor + 5) + ", " + QString::number(bgColor + 7) + ", " + QString::number(bgColor + 3) + ")";
    QString txc = "rgb(" + QString::number(textColor + 5) + ", " + QString::number(textColor + 7) + ", " + QString::number(textColor + 3) + ")";
    QString s = "QLabel{background-color: " + bgc + "; color: " + txc + "; border-radius: 5px;}";
    setStyleSheet(s);
}

void NumberBlock::spawning(){
    size += 9;
    ++resizeState;
    setGeometry(posX + 5 * (10 - resizeState), posY + 5 * (10 - resizeState), size, size);
    setFont(QFont("Waree", size/3, QFont::Bold));
    if(resizeState == 10){
        spawnTimer->stop();
    }
}

void NumberBlock::move(int targetRow, int targetCol, NumberBlock** collider){
    isMerged = false;
    if(targetRow == row && targetCol == col) return;
    if(*collider != NULL){
        isMerged = true;
        number *= 2;
        trashTmp = *collider;
    }
    *collider = this;
    moveState = 0;
    row = targetRow;
    col = targetCol;
    posX = 25 + 100 * col;
    posY = 240 + 100 * row;
    moveTimer->start(10);
}

void NumberBlock::moving(){
    ++moveState;
    setGeometry(curX + (posX - curX) / 20 * moveState, curY + (posY - curY) / 20 * moveState, size, size);
    if(moveState == 20){
        moveTimer->stop();
        curX = posX;
        curY = posY;
        if(trashTmp != NULL) merge();
    }
}

void NumberBlock::merge(){
    delete trashTmp;
    trashTmp = NULL;
    QString n = QString::number(number);
    setText(n);
    emit getScore(number);
    if(number == 2048) emit win();

    int expo = ((int)log2(number) - 1);
    bgColor -= 16;
    if(expo > 5) textColor = 240;
    if(expo > 8) setFont(QFont("Waree", size/4, QFont::Bold));
    setColor();
    mergeState = 0;
    mergeTimer->start(10);
}

void NumberBlock::merging(){
    ++mergeState;
    if(mergeState < 6)
        size += 1;
    else
        size -= 1;
    setGeometry(posX, posY, size, size);
    if(mergeState == 10){
        mergeTimer->stop();
    }
}
