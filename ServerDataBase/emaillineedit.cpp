#include "emaillineedit.h"

EmailLineedit::EmailLineedit(QWidget* parent):QLineEdit(parent)
{
    /* Запретим вводить русские символы в поле email*/
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");

    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    QValidator *pEmailValidator =  new QRegExpValidator(mailREX, this);
    this->setValidator(pEmailValidator);
}


bool EmailLineedit::isValid()
{

}

EmailLineedit::~EmailLineedit()
{

}

