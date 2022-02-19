#include"qmath.h"
#include"qstring.h"
#include "calculator.hpp"
#include"ui_KYHcalculatorV1.h"
#include "KYHcalculatorV1.h"
#include<qmessagebox.h>
//
KYHcalculatorV1::KYHcalculatorV1(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //����
    connect(ui.pushButton_0, &QPushButton::clicked, this, &KYHcalculatorV1::setTextToLineEdit_0);
    connect(ui.pushButton_1, &QPushButton::clicked, this, &KYHcalculatorV1::setTextToLineEdit_1);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &KYHcalculatorV1::setTextToLineEdit_2);
    connect(ui.pushButton_3, &QPushButton::clicked, this, &KYHcalculatorV1::setTextToLineEdit_3);
    connect(ui.pushButton_4, &QPushButton::clicked, this, &KYHcalculatorV1::setTextToLineEdit_4);
    connect(ui.pushButton_5, &QPushButton::clicked, this, &KYHcalculatorV1::setTextToLineEdit_5);
    connect(ui.pushButton_6, &QPushButton::clicked, this, &KYHcalculatorV1::setTextToLineEdit_6);
    connect(ui.pushButton_7, &QPushButton::clicked, this, &KYHcalculatorV1::setTextToLineEdit_7);
    connect(ui.pushButton_8, &QPushButton::clicked, this, &KYHcalculatorV1::setTextToLineEdit_8);
    connect(ui.pushButton_9, &QPushButton::clicked, this, &KYHcalculatorV1::setTextToLineEdit_9);
    //������
    connect(ui.pushButton_plus, &QPushButton::clicked, this, &KYHcalculatorV1::setTextToLineEdit_plus);
    connect(ui.pushButton_minus, &QPushButton::clicked, this, &KYHcalculatorV1::setTextToLineEdit_minus);
    connect(ui.pushButton_multiple, &QPushButton::clicked, this, &KYHcalculatorV1::setTextToLineEdit_multiple);
    connect(ui.pushButton_division, &QPushButton::clicked, this, &KYHcalculatorV1::setTextToLineEdit_division);
    connect(ui.pushButton_clearall, &QPushButton::clicked, this, &KYHcalculatorV1::setTextToLineEdit_clearall);
    connect(ui.pushButton_clearone, &QPushButton::clicked, this, &KYHcalculatorV1::setTextToLineEdit_clearone);
    connect(ui.pushButton_back, &QPushButton::clicked, this, &KYHcalculatorV1::setTextToLineEdit_back);
    connect(ui.pushButton_equal, &QPushButton::clicked, this, &KYHcalculatorV1::setTextToLineEdit_equal);
    connect(ui.pushButton_change, &QPushButton::clicked, this, &KYHcalculatorV1::setTextToLineEdit_change);
}
void KYHcalculatorV1::setCaldata(QString str)
{
    /*-----------------------------------------------------------------------------------------------------------------------------------------------------------
                <<<1. Push Button Ŭ���� ����>>>
                - Push Button�� ������ ����, str�� �����Ѵ�.
                - str�� strprv�� �����Ͽ� �����Ѵ�. ex) '9'+'-' ==>9-
                - strprv ==> ui.lineEdit_prvȭ��, strcal ==> ui.lineEdit_calȭ�鿡 ���� ǥ���Ѵ�.
                - ����������� �Ǻ��ϱ� ���� ui.lineEdit_cal�� �ǳ� ���ڸ� ��ȯ�Ѵ�.
    ------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    auto strprv = ui.lineEdit_prv->text();
    auto strcal = ui.lineEdit_cal->text();
    strprv += str;
    QString findResult = strcal;             
    QString findStrprv = strprv;
    QString findRight = findResult.right(1);
    QString findLeft = findStrprv.left(1);
    QString change(strprv);
    int count = change.count();
    /*-----------------------------------------------------------------------------------------------------------------------------------------------------------
               <<<2. ����� �Ǻ���>>>
               - �Ǻ� ������ ����� ����� �̾ ������� �ʱ�ȭ�Ͽ� ���ο� ��������� �Ǵ��ϱ� ����.
               - ui.lineEdit_cal�� ���� ������ findRight ������ �����Ѵ�.
               - ui.lineEdit_cal�� ������ �ƴϰ�, findRight�� �����ڰ� �ƴҶ�, ������̶�� �����Ѵ�.
               - ����� �Ǻ��� ������, '3.'���� �Ѿ��.
   -------------------------------------------------------------------------------------------------------------------------------------------------------------*/
        if ((strcal!="")&&(findRight != "+") && (findRight != "-") && (findRight != "*") && (findRight != "/"))
        {

    /*-----------------------------------------------------------------------------------------------------------------------------------------------------------
                <<<2-1. ����� ���/�ʱ�ȭ �Ǻ���>>>
                - ����� ��� �� ù �Է°��� �ǿ����ڶ��, ������� �ʱ�ȭ�� �� ���ο� ����� �����Ѵ�.
                - ù�Է°��� �����ڶ��, ������� ����Ѵ�.
    -------------------------------------------------------------------------------------------------------------------------------------------------------------*/
            if ((strprv[0] == '0') || (strprv[0] == '1') || (strprv[0] == '2') || (strprv[0] == '3') || (strprv[0] == '4') ||                                                          
                (strprv[0] == '5') || (strprv[0] == '6') || (strprv[0] == '7') || (strprv[0] == '8') || (strprv[0] == '9'))
            {
                ui.lineEdit_cal->setText("");
                ui.lineEdit_prv->setText(strprv);
            }
            else
            {
                auto cal = QString(strcal);
                cal.append(strprv);
                ui.lineEdit_cal->setText(cal);
            }
        }

    /*-----------------------------------------------------------------------------------------------------------------------------------------------------------
                <<<3. ����� ���� �ʱ� ���³�, ��� ��� �� ����>>> 
    -------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    else
    {

    /*-----------------------------------------------------------------------------------------------------------------------------------------------------------
                <<<3-1. '0'�� ó�� �Էµɽ�>>>
                - '0'�� ó�� �ԷµǸ�, '0'�ڿ� �ǿ����ڰ� �ԷµǸ� �ȵȴ�. [�����ۿ���] 1��° �Է� '0' ==> ȭ�� '0', 2��° �Է� '1' ==> ȭ�� '01'
                - '0'�� �ǿ����� �Է½�, '0'�� ����� �ǿ����ڸ� ǥ���Ѵ�. [���ۿ���] 1��° �Է� '0' ==> ȭ�� '0', 2��° �Է� '1' ==> ȭ�� '1'
                - ù �Է°��� '0'�̸�, strprv�� ���ڿ��� ���� �ʰ�, �ԷµǴ� ���� ǥ���Ѵ�.
    -------------------------------------------------------------------------------------------------------------------------------------------------------------*/
        if (strprv[0] == '0')
        {
            if ((str=='+')|| (str == '-') || (str == '*') || (str == '/'))
            {
                ui.lineEdit_prv->setText("");
            }
            else
            {
                strprv = str;
                ui.lineEdit_prv->setText(strprv);
            }
        }

    /*-----------------------------------------------------------------------------------------------------------------------------------------------------------
                <<<3-2. �����ڰ� ó�� �Էµɽ�>>>
                - �����ڰ� �ʱ�ȭ ���¿��� �ԷµǸ�, �ǿ����ڰ� �����Ƿ� �����ڸ� ǥ������ �ʴ´�. [���ۿ���] �Է� '+' ==> ȭ�� ' '
                - �ʱ� ���¿��� ������ �Է½� ui.lineEdit_prv�� ����д�.
    -------------------------------------------------------------------------------------------------------------------------------------------------------------*/
        else if ((count==1)&&((strprv[0] == '+') || (strprv[0] == '-') || (strprv[0] == '*') || (strprv[0] == '/')))
        {
            ui.lineEdit_prv->setText("");
        }

    /*-----------------------------------------------------------------------------------------------------------------------------------------------------------
                <<<3-3. �����ڰ� �Էµɽ�>>>
                - �����ڰ� �Էµɶ�����, ui.lineEdit_cal ȭ�鿡 ���� �̾�پ�� �Ѵ�.
                - ����, �ǿ����ڸ� �ʱ�ȭ�ؾ��Ѵ�.
                - �ǿ����ڰ� �ݺ� �Էµɽ� ���� �����ڸ� �����ϰ� �Ѵ�.
                - �ǿ����� �ݺ� �Է��� �����ϱ� ���� ui.lineEdit_cal�� ����� cal���� �ݺ� �����ڸ� ã�´�.
                - �ݺ� �����ڰ� �߰ߵɽ�, cal ���ڿ� ������ ���� ���ڸ��� ������ �� ui.lineEdit_cal�� ��ȯ�Ѵ�. 
                - �̶�, ������ �ִٸ�, cal�� ������ ���ڸ��� �������� �ʰ� ui.lineEdit_cal�� ��ȯ�Ѵ�.
    -------------------------------------------------------------------------------------------------------------------------------------------------------------*/
        else
        {
            if ((str == '+') || (str == '-') || (str == '*') || (str == '/'))
            {
                ui.lineEdit_prv->setText("");
                auto cal = QString(strcal);
                cal.append(strprv);
                ui.lineEdit_cal->setText(cal);
                QString findRepeat = cal;
                bool RepeatPP = findRepeat.contains("++", Qt::CaseInsensitive); bool RepeatPM = findRepeat.contains("+-", Qt::CaseInsensitive);
                bool RepeatPm = findRepeat.contains("+*", Qt::CaseInsensitive); bool RepeatPD = findRepeat.contains("+/", Qt::CaseInsensitive);
                bool RepeatMM = findRepeat.contains("--", Qt::CaseInsensitive); bool RepeatMP = findRepeat.contains("-+", Qt::CaseInsensitive);
                bool RepeatMm = findRepeat.contains("-*", Qt::CaseInsensitive); bool RepeatMD = findRepeat.contains("-/", Qt::CaseInsensitive);
                bool Repeatmm = findRepeat.contains("**", Qt::CaseInsensitive); bool RepeatmP = findRepeat.contains("*+", Qt::CaseInsensitive);
                bool RepeatmM = findRepeat.contains("*-", Qt::CaseInsensitive); bool RepeatmD = findRepeat.contains("*/", Qt::CaseInsensitive);
                bool RepeatDD = findRepeat.contains("//", Qt::CaseInsensitive); bool RepeatDP = findRepeat.contains("/+", Qt::CaseInsensitive);
                bool RepeatDM = findRepeat.contains("/-", Qt::CaseInsensitive); bool RepeatDm = findRepeat.contains("/*", Qt::CaseInsensitive);

                if ((RepeatPP == true) || (RepeatPM == true) || (RepeatPm == true) || (RepeatPD == true) ||                                         
                    (RepeatMM == true) || (RepeatMP == true) || (RepeatMm == true) || (RepeatMD == true) ||
                    (Repeatmm == true) || (RepeatmP == true) || (RepeatmM == true) || (RepeatmD == true) ||
                    (RepeatDD == true) || (RepeatDP == true) || (RepeatDM == true) || (RepeatDm == true))
                {
                    if((findRight=='+')||(findRight == '-')||(findRight == '*')||(findRight == '/'))
                    {
                        ui.lineEdit_cal->setText(cal);
                    }
                    else
                    {
                        cal.chop(1);
                        ui.lineEdit_cal->setText(cal);
                    }
                }
            }

    /*-----------------------------------------------------------------------------------------------------------------------------------------------------------
                <<<3-4. '0'�� �ǿ�����ó��>>>
                - '0'�� �ǿ����ڴ� ui.lineEdit_prv�� ���ڿ��� ǥ�����ش�.
    -------------------------------------------------------------------------------------------------------------------------------------------------------------*/
            else
            {
                ui.lineEdit_prv->setText(strprv);                                                                                                                                     
            }
        }
    }
}

    /*---------------------------------------------------------------------------------------------------------------------------------------
                <<<Push Button Ŭ���� �Է°� ����>>>
    ---------------------------------------------------------------------------------------------------------------------------------------*/

// '0' ����
void KYHcalculatorV1::setTextToLineEdit_0()
{
    setCaldata("0");
}

// '1' ����
void KYHcalculatorV1::setTextToLineEdit_1()
{
    setCaldata("1");
}

// '2' ����
void KYHcalculatorV1::setTextToLineEdit_2()
{
    setCaldata("2");
}

// '3' ����
void KYHcalculatorV1::setTextToLineEdit_3()
{
    setCaldata("3");
}

// '4' ����
void KYHcalculatorV1::setTextToLineEdit_4()
{
    setCaldata("4");
}

// '5' ����
void KYHcalculatorV1::setTextToLineEdit_5()
{
    setCaldata("5");
}

// '6' ����
void KYHcalculatorV1::setTextToLineEdit_6()
{
    setCaldata("6");
}

// '7' ����
void KYHcalculatorV1::setTextToLineEdit_7()
{
    setCaldata("7");
}

// '8' ����
void KYHcalculatorV1::setTextToLineEdit_8()
{
    setCaldata("8");
}

// '9' ����
void KYHcalculatorV1::setTextToLineEdit_9()
{
    setCaldata("9");
}

// '+' ����
void KYHcalculatorV1::setTextToLineEdit_plus()
{
    setCaldata("+");
}

// '-' ����
void KYHcalculatorV1::setTextToLineEdit_minus()
{
    setCaldata("-");
}

// '*' ����
void KYHcalculatorV1::setTextToLineEdit_multiple()
{
    setCaldata("*");
}

// '/' ����
void KYHcalculatorV1::setTextToLineEdit_division()
{
    setCaldata("/");
}

/*---------------------------------------------------------------------------------------------------------------------------------------
            <<< '+/-' Push Button Ŭ���� �Է°�>>>
            - ui.lineEdit_cal ȭ�鿡 �Էµ� ù���ڰ� '-'��� '-'�� ������ ����� ǥ���Ѵ�.
            - ui.lineEdit_cal ȭ�鿡 �Էµ� ù���ڰ� ���ڶ�� '-'�� ���ؼ� ������ ǥ���Ѵ�.
---------------------------------------------------------------------------------------------------------------------------------------*/
void KYHcalculatorV1::setTextToLineEdit_change()
{
    auto strChangeCal = ui.lineEdit_cal->text();
    auto strChangePrv = ui.lineEdit_prv->text();
    QString findStrprv=strChangePrv;
    bool c = findStrprv.contains("-", Qt::CaseInsensitive);
    auto change = QString(strChangePrv);
    if ((strChangePrv != "")&&(strChangePrv!="0"))
    {
        if (c == false)
        {
            change.prepend("-");
            ui.lineEdit_prv->setText(change);
        }
        else
        {
            QString remove = strChangePrv;
            strChangeCal = remove.remove(QRegularExpression("-"));
            ui.lineEdit_prv->setText(remove);
        }
    }
    else
    {
        ui.lineEdit_prv->setText("");
    }
}

    /*---------------------------------------------------------------------------------------------------------------------------------------
                <<< 'AC' Push Button Ŭ���� �Է°�>>>
                - ���Էµ� ��� ���� �����.
                - ui.lineEdit_prv�� ui.lineEdit_cal�� �Էµ� �ؽ�Ʈ�� ��� �����.
    ---------------------------------------------------------------------------------------------------------------------------------------*/
void KYHcalculatorV1::setTextToLineEdit_clearall()
{
    ui.lineEdit_prv->setText("");
    ui.lineEdit_cal->setText("");
}

    /*---------------------------------------------------------------------------------------------------------------------------------------
                <<< 'CE' Push Button Ŭ���� �Է°�>>>
                - ui.lineEdit_prv-> ui.lineEdit_cal ������ �Էµ� �ؽ�Ʈ�� �����.
    ---------------------------------------------------------------------------------------------------------------------------------------*/
void KYHcalculatorV1::setTextToLineEdit_clearone()
{
    if (QString::compare(ui.lineEdit_prv->text(), "") != 0)
    {
        ui.lineEdit_prv->setText("");
    }
    else if (QString::compare(ui.lineEdit_cal->text(), "") != 0)
    {
        ui.lineEdit_cal->setText("");
    }
}

    /*---------------------------------------------------------------------------------------------------------------------------------------
                <<<'Backspace' Push Button Ŭ���� �Է°�>>>
                - ui.lineEdit_prv�� �ؽ�Ʈ�� ������ ���� �ؽ�Ʈ���� 1���� �����.
                - ui.lineEdit_prv�� �ؽ�Ʈ�� ������� ui.lineEdit_cal�� ���� �ؽ�Ʈ���� 1���� �����.
    ---------------------------------------------------------------------------------------------------------------------------------------*/
void KYHcalculatorV1::setTextToLineEdit_back()
{
    if (QString::compare(ui.lineEdit_prv->text(), "") != 0)
    {
        QString back(ui.lineEdit_prv->text());
        back.chop(1);
        ui.lineEdit_prv->setText(back);
    }
    else if (QString::compare(ui.lineEdit_cal->text(), "") != 0)
    {
        QString back(ui.lineEdit_cal->text());
        back.chop(1);
        ui.lineEdit_cal->setText(back);
    }
}

    /*---------------------------------------------------------------------------------------------------------------------------------------
                <<<'=' Push Button Ŭ���� �Է°�>>>
                - ui.lineEdit_cal ���Էµ� �ؽ�Ʈ�� strExcal�� �����Ѵ�.
                - ui.lineEdit_prv ���Էµ� �ؽ�Ʈ�� strExprv�� �����Ѵ�.
                - accum�� strExcal�� strExprv�� ����� ���� �ϳ��� ���ڿ��� �ٲ۴�.
                - accum�� ǥ�ع��ڿ��� ��ȯ�� �� calculator�� �����Ͽ�, ���� ������� nResult�� ���������� �����Ѵ�.
                - nResult�� ����� ������ ������� QString ���ڿ��� ��ȯ�Ͽ�, ui.lineEdit_cal�� ǥ���Ѵ�.
    ---------------------------------------------------------------------------------------------------------------------------------------*/
void KYHcalculatorV1::setTextToLineEdit_equal()
{

    auto strExcal = ui.lineEdit_cal->text();
    auto strExprv = ui.lineEdit_prv->text();
    /*---------------------------------------------------------------------------------------------------------------------------------------
                <<<����ó��>>>
    ---------------------------------------------------------------------------------------------------------------------------------------*/
    QString findResult = strExcal;
    QString findRight = findResult.right(1);
    QString findLeft = findResult.left(1);
  
    /*---------------------------------------------------------------------------------------------------------------------------------------
                <���� 1>
                - �����ڰ� ui.lineEdit_cal�� ���� ���Ե� ��Ȳ���� '='�� Ŭ�� �� '�����ڸ� �Է��϶�'�� QMessageBox�� ����.
    ---------------------------------------------------------------------------------------------------------------------------------------*/
    if ((strExprv=="")&&((findRight == "+") || (findRight == "-") || (findRight == "*") || (findRight == "/")))
    {
        QMessageBox msgBox;
        msgBox.setDefaultButton(QMessageBox::warning(this, "error", "Please enter the operand"));
    }
    /*---------------------------------------------------------------------------------------------------------------------------------------
                 <���� 2>
                 - '3/0'�� ���� ���Ѵ����� �ȳ��Ѵ�.
    ---------------------------------------------------------------------------------------------------------------------------------------*/
    else if ((findLeft != "0")&&(findRight == "/") && (strExprv == "0"))
    {
        QMessageBox msgBox;
        msgBox.setDefaultButton(QMessageBox::warning(this, "result", "result is 'infinity'"));
    }
    /*---------------------------------------------------------------------------------------------------------------------------------------
                 <���� 3>
                 - '0/0'�� �Ұ����� ��갪���� �ȳ��Ѵ�.
    ---------------------------------------------------------------------------------------------------------------------------------------*/
    else if ((findLeft == "0") && (strExprv == "0"))
    {
        QMessageBox msgBox;
        msgBox.setDefaultButton(QMessageBox::warning(this, "error", "You entered the impossible calculation"));
    }
    else
    {
        auto accum = QString(strExcal);
        accum.append(strExprv);
        auto stdExpr = accum.toStdString();
        auto nResult = calculator::eval(stdExpr);
        ui.lineEdit_prv->setText("");
        ui.lineEdit_cal->setText(QString::number(nResult));
    }
}