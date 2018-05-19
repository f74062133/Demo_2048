#include "GameoverDialog.h"

GameoverDialog::GameoverDialog(QWidget* parent, QString msg)
    :Dialog(parent, "Game Over", "Try Again")
{
    messageLabel = new QLabel(msg, (QWidget*)this);
    setLabelStyle(messageLabel, 14, 165);

    connect(button, SIGNAL(clicked(bool)), parent, SLOT(tryAgain()));

    show();

}

GameoverDialog::~GameoverDialog(){
    disconnect(button, 0, 0, 0);
    delete messageLabel;
}
