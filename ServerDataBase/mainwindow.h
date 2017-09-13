#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logregdialog.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void startFirstThread();
    void stratSecondThread();

private:
    Ui::MainWindow *ui;
    LogregDialog l;



public slots:
    void ShowId(qint64);
};

#endif // MAINWINDOW_H
