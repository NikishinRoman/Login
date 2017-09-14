#include    "dbmanager.h"
#include    <QDebug>



DbManager::DbManager(const QString &connectionName)
{

    QString pathToBd = qApp->applicationDirPath() + QDir::separator() + "AssistantDBlsql" ;
    this->connectDataBase(pathToBd,connectionName);
}



DbManager::DbManager()
{

    this->connectDataBase();
}


DbManager::~DbManager()
{

    if(this->disconnect()){
        qDebug() << "Disconnect DB";
    }
    else{
        qDebug() << "Error DB";
    }
}

/*
 *      Отключение от БД
 *
 */

bool DbManager::disconnect()
{

    bool ret = this->db.isOpen();

    if (ret){
        this->db.close();
    }else{
        qDebug() << this->db.lastError();
    }

    return ret;

}

/*
 *      Метод соедение с БД.
 *  path - ссылка на строку с путемм к файлу БД sqlite
 */

bool DbManager::connectDataBase(const QString &path, const QString &connectionName)
{
    bool ret;

    this->db = QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE",connectionName));
    this->db.setDatabaseName(path);
    ret = this->db.open();

    if (ret){
        qDebug() << "Успешное соединение с базой данных";

    }
    else{
        qDebug() << "Ошибка: Не возможно соединиться с базой данных";
        qDebug() << this->db.lastError().text();
    }
    return ret;
}

bool DbManager::connectDataBase()
{
    bool ret;


    this->db = QSqlDatabase::addDatabase("QPSQL");
    this->db.setHostName("localhost");
    this->db.setDatabaseName("user_accounts");
    this->db.setUserName("nikishyn");
    this->db.setPassword("Qwerty123!");


    ret = this->db.open();

    if (ret){
        qDebug() << "Успешное соединение с базой данных";

    }
    else{
        qDebug() << "Ошибка: Не возможно соединиться с базой данных";
        qDebug() << this->db.lastError().text();
    }
    return ret;
}




bool DbManager::insertDataToTable(QString& OperationInfo)
{
    QSqlQuery query(this->db);


    if(userInfo.isEmpty()){
        qDebug() << "Data empty";
        OperationInfo = "Data empty";
        return false;
    }


    query.prepare("INSERT INTO user_accounts (name, second_name, user_name, password, email, extra_mail, model, sex, age, birthday, time_zone) "
              "VALUES (:name, :second_name, :user_name, :password, :email, :extra_mail, :model, :sex, :age, :birthday, :time_zone)");



    //query.bindValue(":_id"          ,       userInfo[_ID]);
    query.bindValue(":name"         ,       userInfo[NAME]);
    query.bindValue(":second_name"  ,       userInfo[SECOND_NAME]);

    query.bindValue(":user_name"    ,       userInfo[USER_NAME]);
    query.bindValue(":password"     ,       userInfo[PASSWORD]);
    query.bindValue(":email"        ,       userInfo[EMAIL]);
    query.bindValue(":extra_mail"   ,       userInfo[EXTRA_MAIL]);
    query.bindValue(":model"        ,       userInfo[MODEL]);
    query.bindValue(":sex"          ,       userInfo[SEX]);
    query.bindValue(":age"          ,       userInfo[AGE]);
    query.bindValue(":birthday"     ,       userInfo[BIRTHDAY]);
    query.bindValue(":time_zone"    ,       userInfo[TIME_ZONE]);

    bool isOK = query.exec();

    if(!isOK){
        qDebug() << "Data was not insert";
        qDebug() << query.lastError().text();
        OperationInfo = query.lastError().text();
    }
    else{
        OperationInfo = "Ok";
    }

    userInfo.clear();               /*Очищаем данные*/

    return isOK;

}


/*
 * Получить ID пользователя, если совпала пара user_name  и password.
 * В случае ошибки возвращается -1
*/

qint64 DbManager::getId(QString& OperationInfo)
{
    QSqlQuery query(this->db);
    qint64 retId;
    query.prepare("SELECT _id FROM user_accounts WHERE user_name = (:un) AND password = (:pw)");
    query.bindValue(":un", this->userInfo[USER_NAME].toString());
    query.bindValue(":pw", this->userInfo[PASSWORD].toString());


    if(!query.exec()){
        qDebug() << " Data was not select";
        qDebug() << query.lastError().text();
        OperationInfo = query.lastError().text();
        retId = -1;
    }

    if (query.next()){
        retId =  query.value(DbManager::_ID).toInt();
        OperationInfo = "Ok";
    }
    else{
        retId = -1;
    }

    this->userInfo.clear();

    return retId;
}



bool DbManager::isUserNameSelected(const QString &username)
{


    return isAvailableData("user_name",username);

}

bool DbManager::isEmailSelected(const QString &email)
{

    return isAvailableData("email",email);

}


/*
 * return  false данных в таблице нет, true - существуют
*/
bool DbManager::isAvailableData(const QString &columnName, QVariant data)
{
    //bool ret;
    QSqlQuery query(this->db);

    qDebug() <<  "SELECT " + columnName + " FROM user_accounts WHERE "+columnName + " = (:key)";

    query.prepare("SELECT " + columnName + " FROM user_accounts WHERE "+columnName + " = (:key)");
    query.bindValue(":key", data.toString());

    query.exec();  /* обработку не успешного запроса надо сделать*/

    qDebug() << query.lastError().text() ;//<< ret;

    return query.next();
}



void DbManager:: setPassword(const QString& password )
{
    this->userInfo[PASSWORD] = password;
}

void DbManager:: setUserName(const QString& username )
{
    this->userInfo[USER_NAME] = username;
}

void DbManager::setEmail(const QString& Email)
{
    this->userInfo[EMAIL] = Email;
}





