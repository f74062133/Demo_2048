#include "MenuDialog.h"
const int MenuDialog::colors[8] = {10, 40, 60, 130, 185, 240, 280, 325};
const int MenuDialog::colorBtnSize = 50;
const int MenuDialog::colorBtnGapSize = 80;
const int MenuDialog::initX = 60;
const int MenuDialog::initY = 150;

MenuDialog::MenuDialog(QWidget* parent)
    :Dialog(parent, "Set Color", "ok")
{
    titleLabel->setGeometry(titleLabel->x(), titleLabel->y() - 50, titleLabel->width(), titleLabel->height());
    button->setGeometry(button->x(), button->y() + 80, button->width(), button->height());
    connect(button, SIGNAL(clicked(bool)), parent, SLOT(cancel()));

    for(int i = 0; i < 8; ++i){
        QPushButton* colorBtn = new QPushButton((QWidget*)this);
        QString c = "hsv(" + QString::number(colors[i]) + ", " + QString::number(120) + ", " + QString::number(245) + ")";
        QString s = "QPushButton{ border: solid 10px; border-color: rgb(255, 255, 255);  border-radius: 5px; outline: none; background-color: " + c + "; }";
        colorBtn->setFlat(true);
        colorBtn->setStyleSheet(s);
        colorBtn->setCursor(Qt::PointingHandCursor);
        colorBtn->setGeometry(initX + colorBtnGapSize * (i % (8 / 2)), initY + colorBtnGapSize * (i / (8 / 2)), colorBtnSize, colorBtnSize);
        colorBtn->show();
        connect(colorBtn, SIGNAL(clicked(bool)), &mapper, SLOT(map()));
        mapper.setMapping(colorBtn, colors[i]);
        colorBtns.push_back(colorBtn);
    }

    connect(&mapper, SIGNAL(mapped(int)), parent, SLOT(setColor(int)));
    show();
}

MenuDialog::~MenuDialog(){
    disconnect(&mapper, 0, 0, 0);
    while(!colorBtns.empty()) {
        delete colorBtns.back();
        colorBtns.pop_back();
    }
}
