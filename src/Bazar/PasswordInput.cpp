#include "PasswordInput.h"
#include "PasswordInputUi.h"

PasswordInput::PasswordInput(QWidget *parent) :
    QDialog(parent),
    ui(new PasswordInputUi)
{
    ui->setupUi(this);
}

PasswordInput::~PasswordInput()
{
    delete ui;
}

QString PasswordInput::getPassword()
{
    return ui->lineEditPassword->text();
}
