#include "WinDialog.h"

WinDialog::WinDialog(QWidget* parent)
    :Dialog(parent, "You Win!", "continue")
{
    connect(button, SIGNAL(clicked(bool)), parent, SLOT(cancel()));
    show();
}

WinDialog::~WinDialog(){
    disconnect(button, 0, 0, 0);
}
