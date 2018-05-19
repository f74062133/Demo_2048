#ifndef NUMBERBLOCK_H
#define NUMBERBLOCK_H

#include <QLabel>
#include <QTimer>
#include <cmath>
using namespace std;

class NumberBlock : public QLabel
{
    Q_OBJECT

public:
    NumberBlock(QWidget* parent, int r, int c);
    ~NumberBlock();
    void move(int targetRow, int targetCol, NumberBlock** collider = NULL);

    int number;
    bool isMerged;

signals:
    void getScore(int s);
    void win();

private:
    QTimer* spawnTimer;
    QTimer* moveTimer;
    QTimer* mergeTimer;

    int bgColor;
    int textColor;
    int size;
    int row;
    int col;
    int posX;
    int posY;
    int curX;
    int curY;
    int resizeState;
    int moveState;
    int mergeState;

    NumberBlock** collider;
    NumberBlock* trashTmp;

    void merge();
    void setColor();

private slots:
    void spawning();
    void moving();
    void merging();

};

#endif // NUMBERBLOCK_H
