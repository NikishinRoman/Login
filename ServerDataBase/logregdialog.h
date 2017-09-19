#ifndef LOGREGDIALOG_H
#define LOGREGDIALOG_H

#include <QDialog>
#include <QMovie>
#include "loginmanager.h"
#include "clickablelabel.h"
#include "accountsCache.h"



namespace Ui {
class LogregDialog;
}

class LogregDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LogregDialog(QWidget *parent = 0);
    ~LogregDialog();

private slots:
    void signIn();
    void signUp();


private:
    Ui::LogregDialog *ui;
    QMovie LoaderGif;
    void showLoginStatus(const QString& msg);
    void showRegistrationStatus(const QString& msg);
    accountsCache m_accountsCache;
    void loadAccounts();
    void addAccountToCache();

    LoginManager LManager;

private slots:
    void showSignInPage(const QString &msg);
    void showSignUpPage(const QString &msg);
    void LoginOk(qint64 id);
    void userNameCompleter_activated(const QString& user);

    void on_PushButton_backLoginForm_clicked();

    //void test();


signals:
    void finished(qint64 id);

};

#endif // LOGREGDIALOG_H
