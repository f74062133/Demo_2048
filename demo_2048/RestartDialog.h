#ifndef RESTARTDIALOG_H
#define RESTARTDIALOG_H

#include "Dialog.h"

class RestartDialog : public Dialog
{
public:
    RestartDialog(QWidget* parent);
    ~RestartDialog();

private:
    QPushButton* cancelButton;

};

#endif // RESTARTDIALOG_H
