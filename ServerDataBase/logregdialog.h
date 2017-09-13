#ifndef LOGREGDIALOG_H
#define LOGREGDIALOG_H

#include <QDialog>
#include <QMovie>

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


private:
    Ui::LogregDialog *ui;
    QMovie LoaderGif;
    void showSignInPage();
    void showLoginStatus(const QString& msg);


};

#endif // LOGREGDIALOG_H
