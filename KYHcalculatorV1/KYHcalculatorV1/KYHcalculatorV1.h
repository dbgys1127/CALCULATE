#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_KYHcalculatorV1.h"

class KYHcalculatorV1 : public QMainWindow
{
    Q_OBJECT

public:
    KYHcalculatorV1(QWidget *parent = Q_NULLPTR);
    //숫자
    void setTextToLineEdit_0();
    void setTextToLineEdit_1();
    void setTextToLineEdit_2();
    void setTextToLineEdit_3();
    void setTextToLineEdit_4();
    void setTextToLineEdit_5();
    void setTextToLineEdit_6();
    void setTextToLineEdit_7();
    void setTextToLineEdit_8();
    void setTextToLineEdit_9();
    //연산자
    void setTextToLineEdit_plus();
    void setTextToLineEdit_minus();
    void setTextToLineEdit_multiple();
    void setTextToLineEdit_division();
    void setTextToLineEdit_clearall();
    void setTextToLineEdit_clearone();
    void setTextToLineEdit_back();
    void setTextToLineEdit_equal();
    void setTextToLineEdit_change();
    void setCaldata(QString str);
private:
    Ui::KYHcalculatorV1Class ui;
};
