#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>



class DbManager
{
public:

    DbManager(const QString &connectionName);
    DbManager();
    ~DbManager();

    void setPassword(const QString& password );
    void setUserName(const QString& username );
    void setEmail(const QString& Email);


    bool insertDataToTable(QString& OperationInfo);
    qint64 getId(QString& OperationInfo);

    QSqlDatabase db;
private:
    /*Table*/
    enum users_accountTbl{
        _ID = 0,
        NAME,
        SECOND_NAME,
        USER_NAME,
        PASSWORD,
        EMAIL,
        EXTRA_MAIL,
        MODEL,
        SEX,
        AGE,
        BIRTHDAY,
        TIME_ZONE,
    };
    QMap<users_accountTbl,QVariant> userInfo;

    bool connectDataBase(const QString &path,const QString &connectionName);
    bool connectDataBase();
    bool disconnect();

};

#endif // DBMANAGER_H
