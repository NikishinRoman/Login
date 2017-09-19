#include "logregdialog.h"
#include "ui_logregdialog.h"
#include <QCompleter>

LogregDialog::LogregDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogregDialog), LoaderGif(":/icons/resources/loader.gif"),
    m_accountsCache(this)

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
    this->loadAccounts();

    /*Связываем кнопку входа с обработчиком входа*/
    connect(ui->PushButton_SignIn, SIGNAL(clicked(bool)), SLOT(signIn()));

    /* Связываем кнопку старта регистрации с обработчиком регистрации */
    connect(ui->PushButton_StartReg, SIGNAL(clicked(bool)), SLOT(signUp()));


    connect(&this->LManager, SIGNAL(AuthorizationBad(const QString &)),SLOT(showSignInPage(const QString &)));

    connect(&this->LManager, SIGNAL(AuthorizationOk(qint64)), SLOT(LoginOk(qint64)));

    connect(ui->RegistrationLink, SIGNAL(clicked(const QString &)), SLOT(showSignUpPage(const QString &)));

    connect(&this->LManager, SIGNAL(RegistrationOk(const QString &)), SLOT(showSignInPage(const QString &)));

    connect(&this->LManager, SIGNAL(RegistrationBad(const QString &)), SLOT(showSignUpPage(const QString &)));

    connect(ui->usernameLine->completer(),
                             SIGNAL(activated(QString)),
                             this, SLOT(userNameCompleter_activated(QString)));


    /*Захордкодил.Через дизайнер - не применяется*/
    QPalette p = ui->checkBox_rememberPasswd->palette( );
    QColor grey( 0xBA, 0xBD, 0xB6 );

    p.setColor( QPalette::Active, QPalette::Base, grey );
    p.setColor( QPalette::Inactive, QPalette::Base, grey );
    p.setColor( QPalette::Disabled, QPalette::Base, grey );
    ui->checkBox_rememberPasswd->setPalette( p );

}

LogregDialog::~LogregDialog()
{
    qDebug() << "end Logregdialog";
    delete ui;
}


void LogregDialog::showSignInPage(const QString &msg)
{

    this->showLoginStatus(msg);
    ui->usernameLine->clear();
    ui->passwordLine->clear();
    ui->Loader->hide();
    ui->PushButton_SignIn->setDisabled(false);
    ui->checkBox_rememberPasswd->setDisabled(false);
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
    ui->checkBox_rememberPasswd->setDisabled(true);
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
    this->addAccountToCache(); /*Сохраняем данные о пользователе*/
    this->close();
}

void LogregDialog::on_PushButton_backLoginForm_clicked()
{
    showSignInPage(" ");
}


void LogregDialog::loadAccounts()
{
    m_accountsCache.loadFromFile();
    QStringList list = m_accountsCache.getBareJids();
    QCompleter *completer = new QCompleter(list, this);
    completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->usernameLine->setCompleter(completer);

    if(!list.isEmpty())
    {
        ui->usernameLine->setText(list.last());
        QString passwd = m_accountsCache.getPassword(list.last());
        ui->passwordLine->setText(passwd);
        if(!passwd.isEmpty())
            ui->checkBox_rememberPasswd->setChecked(true);
    }
}

void LogregDialog::addAccountToCache()
{
    QString username = ui->usernameLine->text();
    QString passwd = ui->passwordLine->text();
    if(!ui->checkBox_rememberPasswd->isChecked())
        passwd = "";
    m_accountsCache.addAccount(username, passwd);
}


void LogregDialog::userNameCompleter_activated(const QString& user)
{
    QString passwd = m_accountsCache.getPassword(user);
    ui->passwordLine->setText(passwd);
    if(!passwd.isEmpty())
        ui->checkBox_rememberPasswd->setChecked(true);
}
