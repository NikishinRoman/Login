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
 //   qint64 checkUserInDataBase(const QString &username, const QString &password);

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

    bool insertDataToTable(QMap<users_accountTbl,QVariant> &data/*QVariantList &data const QString &table*/);
    qint64 getId(const QVariant &username, const QVariant &password );

QSqlDatabase db;
private:

    bool connectDataBase(const QString &path,const QString &connectionName);
    bool connectDataBase();
    bool disconnect();




};

#endif // DBMANAGER_H
