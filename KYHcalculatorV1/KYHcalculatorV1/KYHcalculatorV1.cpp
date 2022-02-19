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
    //숫자
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
    //연산자
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
                <<<1. Push Button 클릭시 수신>>>
                - Push Button을 누를때 마다, str에 저장한다.
                - str을 strprv에 누적하여 저장한다. ex) '9'+'-' ==>9-
                - strprv ==> ui.lineEdit_prv화면, strcal ==> ui.lineEdit_cal화면에 각각 표현한다.
                - 결과값인지를 판별하기 위해 ui.lineEdit_cal에 맨끝 문자를 반환한다.
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
               <<<2. 결과값 판별법>>>
               - 판별 이유는 결과값 출력후 이어서 계산할지 초기화하여 새로운 계산할지를 판단하기 위함.
               - ui.lineEdit_cal에 가장 끝값을 findRight 변수에 저장한다.
               - ui.lineEdit_cal이 공백이 아니고, findRight가 연산자가 아닐때, 결과값이라고 정의한다.
               - 결과값 판별이 끝나면, '3.'으로 넘어간다.
   -------------------------------------------------------------------------------------------------------------------------------------------------------------*/
        if ((strcal!="")&&(findRight != "+") && (findRight != "-") && (findRight != "*") && (findRight != "/"))
        {

    /*-----------------------------------------------------------------------------------------------------------------------------------------------------------
                <<<2-1. 결과값 계승/초기화 판별법>>>
                - 결과값 출력 후 첫 입력값이 피연산자라면, 결과값을 초기화한 후 새로운 계산을 시작한다.
                - 첫입력값이 연산자라면, 결과값을 계승한다.
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
                <<<3. 결과가 없는 초기 상태나, 결과 출력 후 로직>>> 
    -------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    else
    {

    /*-----------------------------------------------------------------------------------------------------------------------------------------------------------
                <<<3-1. '0'이 처음 입력될시>>>
                - '0'이 처음 입력되면, '0'뒤에 피연산자가 입력되면 안된다. [오동작예시] 1번째 입력 '0' ==> 화면 '0', 2번째 입력 '1' ==> 화면 '01'
                - '0'외 피연산자 입력시, '0'을 지운뒤 피연산자를 표현한다. [동작예시] 1번째 입력 '0' ==> 화면 '0', 2번째 입력 '1' ==> 화면 '1'
                - 첫 입력값이 '0'이면, strprv에 문자열을 잇지 않고, 입력되는 값만 표현한다.
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
                <<<3-2. 연산자가 처음 입력될시>>>
                - 연산자가 초기화 상태에서 입력되면, 피연산자가 없으므로 연산자를 표현하지 않는다. [동작예시] 입력 '+' ==> 화면 ' '
                - 초기 상태에서 연산자 입력시 ui.lineEdit_prv를 비워둔다.
    -------------------------------------------------------------------------------------------------------------------------------------------------------------*/
        else if ((count==1)&&((strprv[0] == '+') || (strprv[0] == '-') || (strprv[0] == '*') || (strprv[0] == '/')))
        {
            ui.lineEdit_prv->setText("");
        }

    /*-----------------------------------------------------------------------------------------------------------------------------------------------------------
                <<<3-3. 연산자가 입력될시>>>
                - 연산자가 입력될때마다, ui.lineEdit_cal 화면에 값에 이어붙어야 한다.
                - 또한, 피연산자를 초기화해야한다.
                - 피연산자가 반복 입력될시 이전 연산자를 유지하게 한다.
                - 피연산자 반복 입력을 방지하기 위해 ui.lineEdit_cal이 저장된 cal에서 반복 연산자를 찾는다.
                - 반복 연산자가 발견될시, cal 문자열 오른쪽 끝에 한자리를 삭제한 후 ui.lineEdit_cal에 반환한다. 
                - 이때, 음수가 있다면, cal의 오른쪽 한자리를 제거하지 않고 ui.lineEdit_cal에 반환한다.
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
                <<<3-4. '0'외 피연산자처리>>>
                - '0'외 피연산자는 ui.lineEdit_prv에 문자열로 표현해준다.
    -------------------------------------------------------------------------------------------------------------------------------------------------------------*/
            else
            {
                ui.lineEdit_prv->setText(strprv);                                                                                                                                     
            }
        }
    }
}

    /*---------------------------------------------------------------------------------------------------------------------------------------
                <<<Push Button 클릭시 입력값 전달>>>
    ---------------------------------------------------------------------------------------------------------------------------------------*/

// '0' 전달
void KYHcalculatorV1::setTextToLineEdit_0()
{
    setCaldata("0");
}

// '1' 전달
void KYHcalculatorV1::setTextToLineEdit_1()
{
    setCaldata("1");
}

// '2' 전달
void KYHcalculatorV1::setTextToLineEdit_2()
{
    setCaldata("2");
}

// '3' 전달
void KYHcalculatorV1::setTextToLineEdit_3()
{
    setCaldata("3");
}

// '4' 전달
void KYHcalculatorV1::setTextToLineEdit_4()
{
    setCaldata("4");
}

// '5' 전달
void KYHcalculatorV1::setTextToLineEdit_5()
{
    setCaldata("5");
}

// '6' 전달
void KYHcalculatorV1::setTextToLineEdit_6()
{
    setCaldata("6");
}

// '7' 전달
void KYHcalculatorV1::setTextToLineEdit_7()
{
    setCaldata("7");
}

// '8' 전달
void KYHcalculatorV1::setTextToLineEdit_8()
{
    setCaldata("8");
}

// '9' 전달
void KYHcalculatorV1::setTextToLineEdit_9()
{
    setCaldata("9");
}

// '+' 전달
void KYHcalculatorV1::setTextToLineEdit_plus()
{
    setCaldata("+");
}

// '-' 전달
void KYHcalculatorV1::setTextToLineEdit_minus()
{
    setCaldata("-");
}

// '*' 전달
void KYHcalculatorV1::setTextToLineEdit_multiple()
{
    setCaldata("*");
}

// '/' 전달
void KYHcalculatorV1::setTextToLineEdit_division()
{
    setCaldata("/");
}

/*---------------------------------------------------------------------------------------------------------------------------------------
            <<< '+/-' Push Button 클릭시 입력값>>>
            - ui.lineEdit_cal 화면에 입력된 첫문자가 '-'라면 '-'를 지워서 양수를 표현한다.
            - ui.lineEdit_cal 화면에 입력된 첫문자가 숫자라면 '-'를 더해서 음수를 표현한다.
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
                <<< 'AC' Push Button 클릭시 입력값>>>
                - 기입력된 모든 값을 지운다.
                - ui.lineEdit_prv와 ui.lineEdit_cal에 입력된 텍스트를 모두 지운다.
    ---------------------------------------------------------------------------------------------------------------------------------------*/
void KYHcalculatorV1::setTextToLineEdit_clearall()
{
    ui.lineEdit_prv->setText("");
    ui.lineEdit_cal->setText("");
}

    /*---------------------------------------------------------------------------------------------------------------------------------------
                <<< 'CE' Push Button 클릭시 입력값>>>
                - ui.lineEdit_prv-> ui.lineEdit_cal 순으로 입력된 텍스트를 지운다.
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
                <<<'Backspace' Push Button 클릭시 입력값>>>
                - ui.lineEdit_prv에 텍스트가 있을시 우측 텍스트부터 1개씩 지운다.
                - ui.lineEdit_prv에 텍스트가 비워질시 ui.lineEdit_cal에 우측 텍스트부터 1개씩 지운다.
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
                <<<'=' Push Button 클릭시 입력값>>>
                - ui.lineEdit_cal 기입력된 텍스트를 strExcal에 저장한다.
                - ui.lineEdit_prv 기입력된 텍스트를 strExprv에 저장한다.
                - accum에 strExcal과 strExprv에 저장된 값을 하나의 문자열로 바꾼다.
                - accum을 표준문자열로 변환한 후 calculator에 대입하여, 얻은 결과값을 nResult에 정수형으로 저장한다.
                - nResult에 저장된 정수형 결과값을 QString 문자열로 변환하여, ui.lineEdit_cal에 표현한다.
    ---------------------------------------------------------------------------------------------------------------------------------------*/
void KYHcalculatorV1::setTextToLineEdit_equal()
{

    auto strExcal = ui.lineEdit_cal->text();
    auto strExprv = ui.lineEdit_prv->text();
    /*---------------------------------------------------------------------------------------------------------------------------------------
                <<<예외처리>>>
    ---------------------------------------------------------------------------------------------------------------------------------------*/
    QString findResult = strExcal;
    QString findRight = findResult.right(1);
    QString findLeft = findResult.left(1);
  
    /*---------------------------------------------------------------------------------------------------------------------------------------
                <예외 1>
                - 연산자가 ui.lineEdit_cal에 끝에 기입된 상황에서 '='를 클릭 시 '연산자를 입력하라'는 QMessageBox를 연다.
    ---------------------------------------------------------------------------------------------------------------------------------------*/
    if ((strExprv=="")&&((findRight == "+") || (findRight == "-") || (findRight == "*") || (findRight == "/")))
    {
        QMessageBox msgBox;
        msgBox.setDefaultButton(QMessageBox::warning(this, "error", "Please enter the operand"));
    }
    /*---------------------------------------------------------------------------------------------------------------------------------------
                 <예외 2>
                 - '3/0'과 같이 무한대임을 안내한다.
    ---------------------------------------------------------------------------------------------------------------------------------------*/
    else if ((findLeft != "0")&&(findRight == "/") && (strExprv == "0"))
    {
        QMessageBox msgBox;
        msgBox.setDefaultButton(QMessageBox::warning(this, "result", "result is 'infinity'"));
    }
    /*---------------------------------------------------------------------------------------------------------------------------------------
                 <예외 3>
                 - '0/0'은 불가능한 계산값임을 안내한다.
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