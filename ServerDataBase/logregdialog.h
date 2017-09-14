#ifndef LOGREGDIALOG_H
#define LOGREGDIALOG_H

#include <QDialog>
#include <QMovie>
#include "loginmanager.h"
#include "clickablelabel.h"

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


    LoginManager LManager;


private slots:
    void showSignInPage(const QString &msg);
    void showSignUpPage(const QString &msg);
    void LoginOk(qint64 id);


    void on_PushButton_backLoginForm_clicked();


signals:
    void finished(qint64 id);

};

#endif // LOGREGDIALOG_H
