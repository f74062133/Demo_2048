#include "RestartDialog.h"

RestartDialog::RestartDialog(QWidget* parent)
    :Dialog(parent, "Restart?", "Yes")
{
    cancelButton = new QPushButton("No", (QWidget*)this);
    setButtonStyle(cancelButton, 24, 220);

    button->setGeometry(button->x() - 95, button->y(), button->width(), button->height());
    cancelButton->setGeometry(cancelButton->x() + 100, cancelButton->y(), cancelButton->width(), cancelButton->height());

    connect(button, SIGNAL(clicked(bool)), parent, SLOT(tryAgain()));
    connect(cancelButton, SIGNAL(clicked(bool)), parent, SLOT(cancel()));

    show();

}

RestartDialog::~RestartDialog(){
    disconnect(button, 0, 0, 0);
    disconnect(cancelButton, 0, 0, 0);
    delete cancelButton;
}
