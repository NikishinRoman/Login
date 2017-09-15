#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>



class DbManager
{
public:

    DbManager();
    ~DbManager();

    void setPassword(const QString& password );
    void setUserName(const QString& username );
    void setEmail(const QString& Email);


    bool insertDataToTable(QString& OperationInfo);
    qint64 getId(QString& OperationInfo);
    bool isUserNameSelected(const QString &username);
    bool isEmailSelected(const QString &email);

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


    bool connectDataBase();
    bool disconnect();
    bool isAvailableData(const QString &columnName, QVariant data);


signals:
    void errorDb(const QString &);

};

#endif // DBMANAGER_H
