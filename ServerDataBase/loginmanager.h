#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include    "dbmanager.h"

class LoginManager
{
public:
    LoginManager();
    //startConnection()
private:
    DbManager CtrlDataBase;
    QString username;
    QString password;

};

#endif // LOGINMANAGER_H
