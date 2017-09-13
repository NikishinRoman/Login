#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include    "dbmanager.h"
#include    <QObject>

class LoginManager : public QObject
{

    Q_OBJECT

public:
    LoginManager();

    void startAuthorization();

    void setPassword(const QString &);

    void setUsername(const QString &);


signals:
    void AuthorizationOk(qint64);
    void AuthorizationBad(const QString &);

private:
    DbManager CtrlDataBase;
    QString username;
    QString password;



};

#endif // LOGINMANAGER_H
