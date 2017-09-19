#include "examplethreads.h"

#include "QDebug"

QMutex	m_mutex;
ExampleThreads::ExampleThreads(QString threadName) :
    name(threadName)
{

}

void ExampleThreads::run()
{
    QString d;
    QString f;
    for (int i = 0; i <= 150; i++ ) {

        f = QString::number(i) + this->name;
        pntDb.setUserName( f );
        pntDb.setPassword(f);
        pntDb.setEmail(f);



        pntDb.insertDataToTable(d);


       //qDebug() << name << " " << i;
    }

}
