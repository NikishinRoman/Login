#include "logregdialog.h"
#include "ui_logregdialog.h"

LogregDialog::LogregDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogregDialog), LoaderGif(":/icons/resources/loader.gif")
{
    ui->setupUi(this);


    ui->Loader->setMovie(&LoaderGif);
    ui->Loader->movie()->start();


    this->showSignInPage();


    connect(ui->PushButton_SignIn, SIGNAL(clicked(bool)), SLOT(signIn()));

}
LogregDialog::~LogregDialog()
{
    delete ui;
}



void LogregDialog::showSignInPage()
{
    ui->Loader->hide();
    ui->PushButton_SignIn->setDisabled(false);

    ui->stackedWidget->setCurrentIndex(0);
}

void LogregDialog::signIn()
{
    ui->Loader->show();
    ui->PushButton_SignIn->setDisabled(true);

    QString username = ui->usernameLine->text();
    QString password = ui->passwordLine->text();

/*
    if(ui->usernameLine->text().isEmpty()|| ui->passwordLine->text().isEmpty()){
        showLoginStatus("Введите данные для авторизации");\
        return;
    }
*/
/*

*/
}


void LogregDialog::showLoginStatus(const QString& msg)
{
    ui->label_status->setText(msg);
}
