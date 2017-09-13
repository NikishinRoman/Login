#include "loginmanager.h"



LoginManager::LoginManager()
{

}

void LoginManager::startAuthorization(const QString &username,const QString &password)
{

    CtrlDataBase.setUserName(username);
    CtrlDataBase.setPassword(password);
    int id =  CtrlDataBase.getId(OperationInfo);

    if(id != -1){
        emit AuthorizationOk(id);
    }
    else{
        emit AuthorizationBad("Пара логин/пароль не совпали");
    }
}


void LoginManager::startRegistration(const QString& username,const QString& password, const QString& email)
{
    bool isOK;

    CtrlDataBase.setUserName(username);
    CtrlDataBase.setPassword(password);
    CtrlDataBase.setEmail(email);
    isOK = CtrlDataBase.insertDataToTable(this->OperationInfo);


    if(isOK){
        emit RegistrationOk("Регистрация успешна");
    }
    else{
        qDebug() << "Data was not insert";
        emit RegistrationBad(this->OperationInfo);
    }
}
