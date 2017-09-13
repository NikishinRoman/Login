#ifndef EXAMPLETHREADS_H
#define EXAMPLETHREADS_H

#include <QThread>
#include "dbmanager.h"

class ExampleThreads : public QThread
{
public:
    explicit ExampleThreads(QString threadName);

    // Переопределяем метод run(), в котором будет
    // располагаться выполняемый код
    void run();
    DbManager pntDb;
    QMap<DbManager::users_accountTbl,QVariant> d;
private:
    const QString name;   // Имя потока
};

#endif // EXAMPLETHREADS_H
