#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include    "dbmanager.h"
#include    <QObject>

class LoginManager : public QObject
{

    Q_OBJECT

public:

    LoginManager();
    void startAuthorization(const QString &username,const QString &password);
    void startRegistration(const QString& username,const QString& password, const QString& email);


signals:
    void AuthorizationOk(qint64);
    void AuthorizationBad(const QString &);
    void RegistrationOk(const QString &);
    void RegistrationBad(const QString &);

private:
    DbManager CtrlDataBase;
    QString OperationInfo;



};

#endif // LOGINMANAGER_H
