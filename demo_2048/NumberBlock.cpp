#include "NumberBlock.h"

const int NumberBlock::boardX = 25;
const int NumberBlock::boardY = 240;
const int NumberBlock::blockGapSize = 100;
int NumberBlock:: colorH;

NumberBlock::NumberBlock(QWidget* parent, int r, int c)
    :QLabel(parent)
{
    size = 1;
    row = r;
    col = c;
    positionX = boardX + blockGapSize * col;
    positionY = boardY + blockGapSize * row;
    currentX = positionX;
    currentY = positionY;
    number = 2;
    trashTmp = NULL;
    collider = NULL;
    backgroundColorV = 255;
    textColorV = 100;

    setGeometry(positionX, positionY, size, size);
    setText(QString::number(number));
    setAlignment(Qt::AlignCenter);
    setColorH(colorH);
    setColorS(0);
    show();

    spawnTimer = new QTimer((QWidget*)this);
    connect(spawnTimer, SIGNAL(timeout()), this, SLOT(spawning()));
    moveTimer = new QTimer((QWidget*)this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(moving()));
    mergeTimer = new QTimer((QWidget*)this);
    connect(mergeTimer, SIGNAL(timeout()), this, SLOT(merging()));

    connect(this, SIGNAL(getScore(int)), parent, SLOT(addScore(int)));
    connect(this, SIGNAL(win()), parent, SLOT(win()));

    resizeState = 0;
    spawnTimer->start(20);
}

NumberBlock::~NumberBlock(){
    disconnect(spawnTimer, 0, 0, 0);
    disconnect(moveTimer, 0, 0, 0);
    disconnect(mergeTimer, 0, 0, 0);
    disconnect(this, 0, 0, 0);
    delete spawnTimer;
    delete moveTimer;
    delete mergeTimer;
}

void NumberBlock::setColorH(int hue){
    colorH = hue;
    QString bgc = "hsv(" + QString::number(colorH) + ", " + QString::number(colorS) + ", " + QString::number(backgroundColorV) + ")";
    QString txc = "hsv(" + QString::number(colorH) + ", " + QString::number(colorS) + ", " + QString::number(textColorV) + ")";
    QString s = "QLabel{background-color: " + bgc + "; color: " + txc + "; border-radius: 5px;}";
    setStyleSheet(s);
}

void NumberBlock::setColorS(int situration){
    colorS = situration;
    if(colorS > 160) textColorV = 200;
    else textColorV = 100;

    QString bgc = "hsv(" + QString::number(colorH) + ", " + QString::number(colorS) + ", " + QString::number(backgroundColorV) + ")";
    QString txc = "hsv(" + QString::number(colorH) + ", " + QString::number(colorS) + ", " + QString::number(textColorV) + ")";
    QString s = "QLabel{background-color: " + bgc + "; color: " + txc + "; border-radius: 5px;}";
    setStyleSheet(s);
}

void NumberBlock::spawning(){
    size += 9;
    ++resizeState;
    setGeometry(positionX + 5 * (10 - resizeState), positionY + 5 * (10 - resizeState), size, size);
    setFont(QFont("Waree", size/3, QFont::Bold));
    if(resizeState == 10){
        spawnTimer->stop();
    }
}

void NumberBlock::move(int targetRow, int targetCol, NumberBlock** targetBlock){
    isMerged = false;
    if(*targetBlock == this) return;
    if(*targetBlock != NULL){
        isMerged = true;
        number *= 2;
        trashTmp = *targetBlock;
    }
    *targetBlock = this;

    row = targetRow;
    col = targetCol;
    positionX = boardX + blockGapSize * col;
    positionY = boardY + blockGapSize * row;

    moveState = 0;
    moveTimer->start(10);
}

void NumberBlock::moving(){
    ++moveState;
    setGeometry(currentX + (positionX - currentX) / 20 * moveState, currentY + (positionY - currentY) / 20 * moveState, size, size);
    if(moveState == 20){
        moveTimer->stop();
        currentX = positionX;
        currentY = positionY;
        if(trashTmp != NULL) merge();
    }
}

void NumberBlock::merge(){
    // remove target block
    delete trashTmp;
    trashTmp = NULL;

    // set number of merged block and send message to mainwindow
    setText(QString::number(number));
    emit getScore(number);
    if(number == 2048) emit win();

    // change color
    if(log2(number) >= 10) setFont(QFont("Waree", size/4, QFont::Bold));
    setColorS(colorS + 16);

    // start merge animation
    mergeState = 0;
    mergeTimer->start(10);
}

void NumberBlock::merging(){
    ++mergeState;
    if(mergeState < 6)
        size += 1;
    else
        size -= 1;
    setGeometry(positionX, positionY, size, size);
    if(mergeState == 10){
        mergeTimer->stop();
    }
}
