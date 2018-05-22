#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include "Dialog.h"
#include <vector>
#include <QSignalMapper>
using namespace std;

class MenuDialog : public Dialog
{
public:
    MenuDialog(QWidget* parent);
    ~MenuDialog();

private:
    const static int colors[8];
    const static int colorBtnSize;
    const static int colorBtnGapSize;
    const static int initX;
    const static int initY;
    vector<QPushButton*> colorBtns;
    QSignalMapper mapper;

};

#endif // MENUDIALOG_H
