#include "loginmanager.h"



LoginManager::LoginManager()
{

}

void LoginManager::startAuthorization()
{

    int id =  CtrlDataBase.getId(username,password);

    if(id != -1){
        emit AuthorizationOk(id);
    }
    else{
        emit AuthorizationBad("Пара логин/пароль не совпали");
    }

}


void LoginManager::setPassword(const QString &pass)
{
    this->password = pass;
}

void LoginManager::setUsername(const QString &user)
{
    this->username = user;
}
