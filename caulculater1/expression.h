#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <QString>
#include <map>
#include "stack.h"

class Expression
{
public:
    enum State {
        START,
        OPERATOR,
        INTEGER,
        DECIMAL_POINT,
        DECIMAL,
        FINISHED
    };
    enum Function {
        SIN,
        COS,
        TAN,
        ASIN,
        ACOS,
        SQRT,
        SQU
    };

    //构造器
    Expression();

    void insert(char c);//表达式的构建
    double calculate(const double& num1, const double& numu2, const char& op);//运算

    QString getStateStr();//获取计算机在线状态

    void clearStack();//清空栈
    void rebuildStack();//重组栈
    void backspace();//删除

    void setExpression(QString str);
     QString getProcssNum();//获取过程值
    QString getResult();//获得结果
    QString getExpression();//获得公式

    double function(Function F);//扩展内容

private:

    //变量与对象
    int count = 0;
    State state;
    QString exprStr;
    //双栈操作
    Stack<char> op;//建立运算符栈
    Stack<double> num;//建立操作数栈
    //小数变化
    double decimal;

    //函数
    int priority(const char op);//判断运算符优先级
    void setState(State state);//设置计算机在线状态
    void updateStack(int opM);//更新栈

};

#endif // EXPRESSION_H
