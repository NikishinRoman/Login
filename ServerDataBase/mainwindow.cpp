#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&l, SIGNAL(finished(qint64)), SLOT(ShowId(qint64)));

    l.show();
    l.exec();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: ShowId(qint64 id)
{
    QString msg = QString::number(id);;

    ui->label->setText(msg);
}
