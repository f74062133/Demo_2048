#ifndef DIALOG_H
#define DIALOG_H

#include <QLabel>
#include <QPushButton>
//#include "MainWindow.h"

class Dialog : public QLabel
{
public:

    static int textColor;
    static int backgroundColor;
    const static int boardX;
    const static int boardY;
    const static int boardSize;

    Dialog(QWidget* parent, QString titleText, QString buttonText);
    ~Dialog();
    void setLabelStyle(QLabel* label, int fontSize, int y);
    void setButtonStyle(QPushButton* btn, int fontSize, int y);

    QLabel* titleLabel;
    QPushButton* button;
};

#endif // DIALOG_H
