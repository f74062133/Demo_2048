#ifndef GAMEOVERDIALOG_H
#define GAMEOVERDIALOG_H

#include "Dialog.h"

class GameoverDialog : public Dialog
{
public:
    GameoverDialog(QWidget* parent, QString msg);
    ~GameoverDialog();

private:
    QLabel* messageLabel;

};

#endif // GAMEOVERDIALOG_H
