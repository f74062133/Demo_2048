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
    void setColorH(int hue);

    const static int boardX;
    const static int boardY;
    const static int blockGapSize;
    static int colorH;

    int number;
    bool isMerged;

signals:
    void getScore(int s);
    void win();

private:
    void merge();
    void setColorS(int situration);

    QTimer* spawnTimer;
    QTimer* moveTimer;
    QTimer* mergeTimer;
    NumberBlock** collider;
    NumberBlock* trashTmp;

    int size;
    int row;
    int col;
    int positionX;
    int positionY;
    int currentX;
    int currentY;

    int colorS;
    int backgroundColorV;
    int textColorV;

    int resizeState;
    int moveState;
    int mergeState;

private slots:
    void spawning();
    void moving();
    void merging();

};

#endif // NUMBERBLOCK_H
