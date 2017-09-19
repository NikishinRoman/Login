#ifndef EMAILLINEEDIT_H
#define EMAILLINEEDIT_H


#include    <QLineEdit>
#include    <QValidator>

class EmailLineedit:public QLineEdit
{
    Q_OBJECT
public:
    explicit EmailLineedit(QWidget* parent=0 );
    ~EmailLineedit();

    bool isValid();

};

#endif // EMAILLINEEDIT_H
