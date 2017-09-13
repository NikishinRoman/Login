#include "examplethreads.h"

#include "QDebug"

QMutex	m_mutex;
ExampleThreads::ExampleThreads(QString threadName) :
    name(threadName),pntDb(threadName)
{

}

void ExampleThreads::run()
{

    for (int i = 0; i <= 150; i++ ) {

//        d[DbManager::USER_NAME] = name;
//        d[DbManager::PASSWORD] = i;
//        m_mutex.lock();
//        pntDb.insertDataToTable(d);
//        m_mutex.unlock();

        qDebug() << pntDb.getId(name,0);
        //qDebug() << name << " " << i;
    }

}
