
#include "mainwindow.h"
#include <QApplication>
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include <QDebug>
#include "dbmanager.h"
#include "examplethreads.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    //QMap<DbManager::users_accountTbl,QVariant> d;
    //d[DbManager::NAME] = "trete111";
//    d[DbManager::SECOND_NAME] = "Пантелеймон1";
//    d[DbManager::USER_NAME] = "Nikishyn122";
//    d[DbManager::PASSWORD] = "6666";



//    DbManager manager_db("1");




//    qDebug() << manager_db.getId("Romeo", "Nikishyn");
//    qDebug() << manager_db.getId("Carlito","1");


//        //qDebug() << QSql:sqlite3_threadsafe;


//    ExampleThreads threadA("thread A");
//    ExampleThreads threadB("thread B");
//    ExampleThreads threadC("thread C");

//    threadA.start();    // Запускаем потоки
//    threadB.start();    // и наблюдаем их параллельную работу
//    threadC.start();    // в выводе qDebug

    qDebug() << QSqlDatabase::drivers();
//    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
//    db.setHostName("localhost");
//    db.setDatabaseName("user_accounts");
//    db.setUserName("nikishyn");
//    db.setPassword("Qwerty123!");
//    if (!db.open())
//    {
//            qDebug() << QObject::trUtf8("Бд не найдена") << db.lastError().text();
//            return -1;
//    }


    /*
    DbManager manager_db;

    manager_db.insertDataToTable(d);

    qDebug() << manager_db.getId("Nikishyn1","6666");
*/
//     QSqlQuery query;
//    query.exec("SELECT _id, second_name FROM user_accounts");
//    while (query.next()) {
//         int id = query.value(0).toInt();
//         //QString name = query.value(1).toString();
//         QString sn = query.value(1).toString();
//         qDebug() << id <<  sn;
//       }

    w.show();

    return a.exec();
}
