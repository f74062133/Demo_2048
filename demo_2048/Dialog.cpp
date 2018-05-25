#include "Dialog.h"

const int Dialog::boardX = 15;
const int Dialog::boardY = 230;
const int Dialog::boardSize = 411;
const int Dialog::backgroundColorS = 32;
const int Dialog::backgroundColorV = 200;
const int Dialog::textColorS = 240;
const int Dialog::textColorV = 80;
int Dialog::colorH;

Dialog::Dialog(QWidget* parent, QString titleText, QString buttonText)
    :QLabel(parent)
{
    titleLabel = new QLabel(titleText, (QWidget*)this);
    setLabelStyle(titleLabel, 36, 100);

    button = new QPushButton(buttonText, (QWidget*)this);
    setButtonStyle(button, 24, 220);

    setColor(colorH);
    setGeometry(boardX, boardY ,boardSize ,boardSize);
}

Dialog::~Dialog(){
    delete titleLabel;
    delete button;
}

void Dialog::setLabelStyle(QLabel* label, int fontSize, int y){
    QString c = "hsv(" + QString::number(colorH) + ", " + QString::number(textColorS) + ", " + QString::number(textColorV) + ")";
    QString s = "QLabel{ background-color: transparent; color: " + c + "; }";
    label->setStyleSheet(s);
    label->setFont(QFont("Waree", fontSize, QFont::Bold));

    int labelWidth = label->fontMetrics().width(label->text());
    int labelHeight = label->fontMetrics().height();
    label->setGeometry((boardSize - labelWidth) / 2, y, labelWidth, labelHeight);
}

void Dialog::setButtonStyle(QPushButton* btn, int fontSize, int y){
    QString c = "hsv(" + QString::number(colorH) + ", " + QString::number(textColorS) + ", " + QString::number(textColorV) + ")";
    QString s = "QPushButton{ border: none; outline: none; background-color: transparent; color: " + c + "; }";
    btn->setFlat(true);
    btn->setStyleSheet(s);
    btn->setFont(QFont("Waree", fontSize, QFont::Bold));
    btn->setCursor(Qt::PointingHandCursor);

    int btnWidth = btn->fontMetrics().width(btn->text());
    int btnHeight = btn->fontMetrics().height();
    btn->setGeometry((boardSize - btnWidth) / 2, y, btnWidth, btnHeight);
}

void Dialog::setColor(int hue){
    colorH = hue;

    QString c = "hsva(" + QString::number(colorH) + ", " + QString::number(backgroundColorS) + ", " + QString::number(backgroundColorV) + ", 50%)";
    QString s = "QLabel{ border-radius: 10px; background-color: " + c + "; }";
    setStyleSheet(s);
    setLabelStyle(titleLabel, 36, titleLabel->y());
    setButtonStyle(button, 24, button->y());
}
