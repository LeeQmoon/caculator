#include "calculator.h"
#include "ui_calculator.h"
#include<iostream>
#include<sstream>
#include<string>
#include<cmath>
#include"QDebug"
using namespace std;

const double PI = 3.14;


calculator::calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::calculator)
{
    ui->setupUi(this);
    check_equal = false;
    memset(history, 0, sizeof(history));//initialize
    history_amount++;//初始化第一个为0, 从第二个开始保存

    connect(ui->digitButton_0,SIGNAL(clicked(bool)),this,SLOT(digitClicked()));
    connect(ui->digitButton_1,SIGNAL(clicked(bool)),this,SLOT(digitClicked()));
    connect(ui->digitButton_2,SIGNAL(clicked(bool)),this,SLOT(digitClicked()));
    connect(ui->digitButton_3,SIGNAL(clicked(bool)),this,SLOT(digitClicked()));
    connect(ui->digitButton_4,SIGNAL(clicked(bool)),this,SLOT(digitClicked()));
    connect(ui->digitButton_5,SIGNAL(clicked(bool)),this,SLOT(digitClicked()));
    connect(ui->digitButton_6,SIGNAL(clicked(bool)),this,SLOT(digitClicked()));
    connect(ui->digitButton_7,SIGNAL(clicked(bool)),this,SLOT(digitClicked()));
    connect(ui->digitButton_8,SIGNAL(clicked(bool)),this,SLOT(digitClicked()));
    connect(ui->digitButton_9,SIGNAL(clicked(bool)),this,SLOT(digitClicked()));
    connect(ui->dotButton,SIGNAL(clicked(bool)),this,SLOT(digitClicked()));
    connect(ui->leftButton,SIGNAL(clicked(bool)),this,SLOT(digitClicked()));
    connect(ui->rightButton,SIGNAL(clicked(bool)),this,SLOT(digitClicked()));
    connect(ui->plusButton,SIGNAL(clicked(bool)),this,SLOT(digitClicked()));
    connect(ui->subButton,SIGNAL(clicked(bool)),this,SLOT(digitClicked()));
    connect(ui->multiButton,SIGNAL(clicked(bool)),this,SLOT(digitClicked()));
    connect(ui->divisionButton,SIGNAL(clicked(bool)),this,SLOT(digitClicked()));

    connect(ui->circleButton,SIGNAL(clicked(bool)),this,SLOT(circleClicked()));

    connect(ui->equalButton,SIGNAL(clicked(bool)),this,SLOT(equalClicked()));

    connect(ui->clearOneButton,SIGNAL(clicked(bool)),this,SLOT(clearOneClicked()));
    connect(ui->clearEnterButton,SIGNAL(clicked(bool)),this,SLOT(clearEnterClicked()));
    connect(ui->clearHistoryButton,SIGNAL(clicked(bool)),this,SLOT(clearHistoryClicked()));
}

//字符串转换为相应的数值
double calculator::TransformDigit(NumberStack& number){
    int count = 0;//记录小数点后面的位数
    bool flag = false;//检查是否含有小数点
    char temp = '\0';
    int k = 1;
    int value = 0;//无论小数还是整数，都先保存为整数
    while(number.Pop(temp) && temp != '#' && number.GetSize() >= 0){
        if(temp == '.'){
            flag = true;//标记为含有小数点
            continue;
        }
        if(temp == '-'){
            value = - value;
            continue;
        }
        if(!flag)//还没出现小数点，计算可能的小数点后的位数
            count++;
        value += (temp - '0')*k;
        k *= 10;
    }

    if(flag)
        return value / pow(10, count);//返回数值
    else
        return value;
}


//把计算结果存入数字栈中
void calculator::SaveResultToStack(double temp, NumberStack& number){
    stringstream ss;
    string transform;
    ss << temp;
    ss >> transform;
    for(int i = 0; i < transform.length(); i++){
        number.Push(transform[i]);
    }
}


//计算结果
double calculator::Caculate(char ch, NumberStack& number){
    double temp[3] = {0, 0 ,0};//存放操作数
    for(int i = 0; i < 2; i++)//都是二元运算符，就从数字栈执行两大次取出数值
        temp[i] = TransformDigit(number);
    number.Push('#');
    switch(ch){
        case '+':
            return temp[1] + temp[0];
        case '-':
            return temp[1] - temp[0];
        case '*':
            return temp[1] * temp[0];
        case '/':
            return temp[1] / temp[0];
    }
}


double calculator::GetResult(NumberStack& number, SignStack& sign){
    char temp = '\0';//保存从运算栈中pop出运算符进行操作计算
    sign.Pop(temp);//取出运算符
    switch(temp){
        case '+':
            SaveResultToStack(Caculate('+', number), number);
            return 0;
        case '-':
            SaveResultToStack(Caculate('-', number), number);
            return 0;
        case '*':
            SaveResultToStack(Caculate('*', number), number);
            return 0;
        case '/':
            SaveResultToStack(Caculate('/', number), number);
            return 0;
        case '(':
            //计算完后，把一个'('取出
            return 1;
        case '#':
            //若是分隔符，直接取出结果
            return TransformDigit(number);
    }
}

void calculator::clearOneClicked()
{
    QString str1 = ui->lineEdit->text();
    if(!str1.isNull()){
     QString str2 = str1.left(str1.length()-1);
     ui->lineEdit->setText(str2);
    }
}

void calculator::clearEnterClicked()
{
    ui->lineEdit->clear();
}

void calculator::circleClicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + QString::number(PI));
}

void calculator::clearHistoryClicked()
{
    memset(history, 0, sizeof(history));
    history_amount = 1;
}

void calculator::digitClicked()
{
    if(check_equal){
        ui->lineEdit->clear();
        check_equal = false;
    }
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    ui->lineEdit->setText(ui->lineEdit->text()+clickedButton -> text());
}

void calculator::equalClicked()
{
   check_equal = true;
   trans();
}

void calculator::trans()
{
    if(check_equal){
        NumberStack number;//存放数字的栈
        SignStack sign;//存放运算符的栈
        sign.Push('#');//栈底存放分隔符'#'
        string str = ui->lineEdit->text().toStdString();
        int num = 0;//记录字符串中已经被取出的字符
        int length = str.length();
        int count = 0;//记录'('的个数，避免')'的输入超过阈值
        if(str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/'){
            SaveResultToStack(history[history_amount - 1], number);
            number.Push('#');
        }
        bool first = false;//判断一开始是不是就是运算符，如果是，就直接把history中的记录入栈
        if(str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/')
            first = true;

        //判断条件: 计算式子的字符是否被完全取出以及运算符栈是否只剩下分隔符'#'
        while(num != length || sign.GetSize() > 0){
            char ch = '\0';//从字符串中取出字符赋值在ch中
            if(num != length){//情况一: 字符串还未被完全取出
                ch = str[num];//取出字符
                if((ch >= '0' && ch <='9') || ch == '.'){//如果是数字
                    number.Push(ch);//存进数字栈中
                    num++;
                }
                else if(ch == '+' || ch == '-'){//如果是'+'或者'-'[两者是同等级的]
                    if(first){
                        SaveResultToStack(history[history_amount-1], number);
                        first = false;
                    }
                    if(sign.Compare(ch)){//比较优先级
                        sign.Push(ch);//优先级足够高，存入运算符栈中
                        number.Push('#');//此时，运算符一个操作数已经存入数字栈中，'#'作为操作数的分隔
                        num++;
                    }
                    else{//优先级不够高的,出栈，进行计算
                        GetResult(number, sign);//取得计算结果
                    }
                }
                else if(ch == '*' || ch == '/'){//注释同上
                    if(first){
                        SaveResultToStack(history[history_amount-1], number);
                        first = false;
                    }
                    if(sign.Compare(ch)){//比较优先级
                        sign.Push(ch);//优先级足够高，存入运算符栈中
                        number.Push('#');//此时，运算符一个操作数已经存入数字栈中，'#'作为操作数的分隔
                        num++;
                     }
                    else //优先级不够高的,出栈，进行计算
                        GetResult(number, sign);//取得计算结果

                }
                else if(ch == '('){//如果遇到左括号'('，则直接存入运算符栈
                    sign.Push(ch);
                    count++;
                    num++;
                }
                else if(ch == ')'){//遇到右括号')'，则直接计算结果
                    if(count > 0){//如果数目还少继续
                        int check = GetResult(number, sign);
                        if(check == 0)
                            sign.Pop(ch);
                        if(check == 1);
                        num++;
                        count--;
                    }
                    else//如果已经足够了，就直接跳多余的
                        num++;
                }
            }
            else{//情况二: 字符串完全被取出了
                while(sign.GetSize() > 0)//判断: 运算符栈是否为空
                    if(sign.GetSize() == 1){
                        history[history_amount++] = GetResult(number, sign);
                        ui->lineEdit->clear();
                        ui->lineEdit->setText(QString::number(history[history_amount-1]));
                    }
                    else
                        GetResult(number, sign);//计算结果
            }
        }
    }
}

calculator::~calculator()
{
    delete ui;
}
