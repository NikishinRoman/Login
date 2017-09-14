#include "logregdialog.h"
#include "ui_logregdialog.h"

LogregDialog::LogregDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogregDialog), LoaderGif(":/icons/resources/loader.gif")

{
    ui->setupUi(this);


    ui->Loader->setMovie(&LoaderGif);
    ui->Loader->movie()->start();

    /* Запретим вводить русские символы в поле email*/
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    QValidator *pEmailValidator =  new QRegExpValidator(mailREX, this);
    ui->emailRegLine->setValidator(pEmailValidator);



    this->showSignInPage(" ");

    /*Связываем кнопку входа с обработчиком входа*/
    connect(ui->PushButton_SignIn, SIGNAL(clicked(bool)), SLOT(signIn()));

    /* Связываем кнопку старта регистрации с обработчиком регистрации */
    connect(ui->PushButton_StartReg, SIGNAL(clicked(bool)), SLOT(signUp()));


    connect(&this->LManager, SIGNAL(AuthorizationBad(const QString &)),SLOT(showSignInPage(const QString &)));

    connect(&this->LManager, SIGNAL(AuthorizationOk(qint64)), SLOT(LoginOk(qint64)));

    connect(ui->RegistrationLink, SIGNAL(clicked(const QString &)), SLOT(showSignUpPage(const QString &)));

    connect(&this->LManager, SIGNAL(RegistrationOk(const QString &)), SLOT(showSignInPage(const QString &)));

    connect(&this->LManager, SIGNAL(RegistrationBad(const QString &)), SLOT(showSignUpPage(const QString &)));
}
LogregDialog::~LogregDialog()
{
    qDebug() << "end Logregdialog";
    delete ui;
}


void LogregDialog::showSignInPage(const QString &msg)
{
    this->showLoginStatus(msg);
    ui->Loader->hide();
    ui->PushButton_SignIn->setDisabled(false);
    ui->stackedWidget->setCurrentIndex(0);
}

void LogregDialog::showSignUpPage(const QString &msg)
{
    //ui->Loader->hide();
    showRegistrationStatus(msg);
    ui->PushButton_StartReg->setDisabled(false);
    ui->stackedWidget->setCurrentIndex(1);
}

void LogregDialog::signIn()
{
    ui->Loader->show();
    ui->PushButton_SignIn->setDisabled(true);
    this->LManager.startAuthorization(ui->usernameLine->text(),
                                      ui->passwordLine->text());
}



void LogregDialog::signUp()
{
    //ui->Loader->show();
    ui->PushButton_StartReg->setDisabled(true);


    this->LManager.startRegistration(ui->usernameRegLine->text(),
                                     ui->passwordRegLine->text(),
                                     ui->emailRegLine->text());
}



void LogregDialog::showLoginStatus(const QString &msg)
{
    ui->label_status->setText(msg);
}


void LogregDialog::showRegistrationStatus(const QString& msg)
{
    ui->label_reg_status->setText(msg);
}


/*
 *  Авторизация прошла успешно
*/
void LogregDialog::LoginOk(qint64 id)
{
    emit    finished(id);
    this->close();
}

void LogregDialog::on_PushButton_backLoginForm_clicked()
{
    showSignInPage(" ");
}


