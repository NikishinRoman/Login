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




bool DbManager::insertDataToTable(QMap<users_accountTbl,QVariant> &data)
{
    QSqlQuery query(this->db);


    if(data.isEmpty()){
        qDebug() << "Data empty";
        return false;
    }


    query.prepare("INSERT INTO user_accounts (name, second_name, user_name, password, email, extra_mail, model, sex, age, birthday, time_zone) "
              "VALUES (:name, :second_name, :user_name, :password, :email, :extra_mail, :model, :sex, :age, :birthday, :time_zone)");



    //query.bindValue(":_id"          ,       data[_ID]);
    query.bindValue(":name"         ,       data[NAME]);
    query.bindValue(":second_name"  ,       data[SECOND_NAME]);

    query.bindValue(":user_name"    ,       data[USER_NAME]);
    query.bindValue(":password"     ,       data[PASSWORD]);
    query.bindValue(":email"        ,       data[EMAIL]);
    query.bindValue(":extra_mail"   ,       data[EXTRA_MAIL]);
    query.bindValue(":model"        ,       data[MODEL]);
    query.bindValue(":sex"          ,       data[SEX]);
    query.bindValue(":age"          ,       data[AGE]);
    query.bindValue(":birthday"     ,       data[BIRTHDAY]);
    query.bindValue(":time_zone"    ,       data[TIME_ZONE]);

    bool isOK = query.exec();

    if(!isOK){
      qDebug() << "Data was not insert";
      qDebug() << query.lastError().text();
    }

    return isOK;

}


/*
 * Получить ID пользователя, если совпала пара user_name  и password.
 * В случае ошибки возвращается -1
*/

qint64 DbManager::getId(const QVariant &username, const QVariant &password )
{
    QSqlQuery query(this->db);

    query.prepare("SELECT _id FROM user_accounts WHERE user_name = (:un) AND password = (:pw)");
    query.bindValue(":un", username.toString());
    query.bindValue(":pw", password.toString());

    if(!query.exec()){
        qDebug() << " Data was not select";
        qDebug() << query.lastError().text();
        return -1;
     }

    if (query.next())
        return query.value(DbManager::_ID).toInt();
    else
        return -1;

}





