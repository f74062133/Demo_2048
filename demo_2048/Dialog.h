#ifndef DIALOG_H
#define DIALOG_H

#include <QLabel>
#include <QPushButton>

class Dialog : public QLabel
{
public:

    Dialog(QWidget* parent, QString titleText, QString buttonText);
    ~Dialog();
    void setColor(int hue);
    void setLabelStyle(QLabel* label, int fontSize, int y);
    void setButtonStyle(QPushButton* btn, int fontSize, int y);

    QLabel* titleLabel;
    QPushButton* button;

    static int colorH;
    const static int backgroundColorS;
    const static int backgroundColorV;
    const static int textColorS;
    const static int textColorV;
    const static int boardX;
    const static int boardY;
    const static int boardSize;

};

#endif // DIALOG_H
