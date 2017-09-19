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


    /*Валидацию необходимо перенести в отдельный метод*/
    if(username.isEmpty() || password.isEmpty() || email.isEmpty()){
        emit RegistrationBad("Ошибка: Введены не все данные");
        return;
    }

    if(CtrlDataBase.isUserNameSelected(username)){
        emit RegistrationBad("Ошибка:Имя пользователя занято");
        return;
    }

    if(CtrlDataBase.isEmailSelected(email)){
        emit RegistrationBad("Ошибка:Адрес почты занят");
        return;
    }

    CtrlDataBase.setUserName(username);
    CtrlDataBase.setPassword(password);
    CtrlDataBase.setEmail(email);
    isOK = CtrlDataBase.insertDataToTable(this->OperationInfo);

    if(isOK){
        emit RegistrationOk("Регистрация успешна");
    }
    else{
        qDebug() << "Ошибка регистрации";
        //emit RegistrationBad(this->OperationInfo);
    }
}


void LoginManager::errorHandleDb(const QString &msg)
{
    Q_UNUSED(msg);
}


