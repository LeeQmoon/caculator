#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include"C:\Users\Fullmoon\Desktop\vscode\caculator\Stack.h"

namespace Ui {
class calculator;
}

class calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit calculator(QWidget *parent = nullptr);
    ~calculator();

private:
    Ui::calculator *ui;
    bool check_equal;//检查'='是否已经出现
    double history[100];//记录每个式子的结果
    int history_amount = 0;//累计记录的个数
    void trans();
    double TransformDigit(NumberStack& number);//把数字字符串转化为数值
    void SaveResultToStack(double temp, NumberStack& number);//把计算结果存入数字栈中
    double Caculate(char ch, NumberStack& number);//计算结果
    double GetResult(NumberStack& number, SignStack& sign);//取得结果

private slots:
    void clearOneClicked();
    void clearEnterClicked();
    void clearHistoryClicked();
    void circleClicked();
    void digitClicked();
    void equalClicked();
};

#endif // CALCULATOR_H
