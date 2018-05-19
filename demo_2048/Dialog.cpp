#include "Dialog.h"

const int Dialog::boardX = 15;
const int Dialog::boardY = 230;
const int Dialog::boardSize = 411;
int Dialog::textColor = 180;
int Dialog::backgroundColor = 80;

Dialog::Dialog(QWidget* parent, QString titleText, QString buttonText)
    :QLabel(parent)
{    
    QString c = "rgba(" + QString::number(backgroundColor + 5) + ", " + QString::number(backgroundColor + 7) + ", " + QString::number(backgroundColor + 3) + ", 70%)";
    QString s = "QLabel{ border-radius: 10px; background-color: " + c + "; }";
    setStyleSheet(s);
    setGeometry(boardX, boardY ,boardSize ,boardSize);

    titleLabel = new QLabel(titleText, (QWidget*)this);
    setLabelStyle(titleLabel, 36, 100);

    button = new QPushButton(buttonText, (QWidget*)this);
    setButtonStyle(button, 24, 220);

}

Dialog::~Dialog(){
    delete titleLabel;
    delete button;
}

void Dialog::setLabelStyle(QLabel* label, int fontSize, int y){
    QString c = "rgb(" + QString::number(textColor + 5) + ", " + QString::number(textColor + 7) + ", " + QString::number(textColor + 3) + ")";
    QString s = "QLabel{ background-color: transparent; color: " + c + "; }";
    label->setStyleSheet(s);
    label->setFont(QFont("Waree", fontSize, QFont::Bold));

    int labelWidth = label->fontMetrics().width(label->text());
    int labelHeight = label->fontMetrics().height();
    label->setGeometry((boardSize - labelWidth) / 2, y, labelWidth, labelHeight);
}

void Dialog::setButtonStyle(QPushButton* btn, int fontSize, int y){
    QString c = "rgb(" + QString::number(textColor + 5) + ", " + QString::number(textColor + 7) + ", " + QString::number(textColor + 3) + ")";
    QString s = "QPushButton{ border: none; outline: none; background-color: transparent; color: " + c + "; }";
    btn->setFlat(true);
    btn->setStyleSheet(s);
    btn->setFont(QFont("Waree", fontSize, QFont::Bold));
    btn->setCursor(Qt::PointingHandCursor);

    int btnWidth = btn->fontMetrics().width(btn->text());
    int btnHeight = btn->fontMetrics().height();
    btn->setGeometry((boardSize - btnWidth) / 2, y, btnWidth, btnHeight);
}
