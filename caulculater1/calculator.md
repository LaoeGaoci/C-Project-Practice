# C++实训文档-Stack_Calculater
#### 作者：鄂日启   学号：22301145

## 问题描述 ：

1. 使用堆栈完成中缀表达式求值的计算
2. 完成自己定义的栈数据结构：C++使用类，C使用独立的文件；
  使用自己的栈，实现表达式求值。
3. GUI实现的计算器程序：计算器基本计算功能,包括：+ - * / 运算和（）, 回退、清除、基本的容错。复杂的容错、一元运算符（包括倒数、平方、开方、log、三角函数、进制转换等）、历史记录等为扩展功能。
   

## 设计思路 ：
### Stack数据结构 ：
``` cpp
#ifndef STACK_H
#define STACK_H

#include <QDebug>
#include <QString>
#include <iostream>

#define CAP 256
template <typename E>
class Stack
{
public:
    //构造器
    Stack();
    Stack(int capacity);
    ~Stack();

    void push(E element);//压入
    E top();//取首
    E pop();//弹出

    void clear();//清空
    int getSize();//取大小
    bool ifEmpty();//判断是否为空
private:

    //变量
    int capacity;//总容量
    int stackSize;//长度
    E* stack;

    //函数
    bool expansion(int capacity);//扩充
};

//初始化列表
// 构造器
template <typename E>
Stack<E>::Stack(): capacity(CAP), stackSize(0) {
    stack = (E*) malloc(sizeof(E) * CAP);
    if (!stack) { // Error
        qDebug() << "Stack Construction Error";
    }
}

template <typename E>
Stack<E>::Stack(int capacity): capacity(capacity), stackSize(0) {
    stack = (E*) malloc(sizeof(E) * capacity);
    if (!stack) { // Error
        qDebug() << "Stack Construction Error";
    }
}

template <typename E>
Stack<E>::~Stack() {
    free(stack);
    stack = nullptr;
}

//扩容
template <typename E>
bool Stack<E>::expansion(int capacity) {
    E* newStack;
    newStack = (E*) realloc(stack, sizeof(E) * capacity);
    if (newStack) {
        this->capacity = capacity;
        stack = newStack;
        return true;
    }
    return false;
}

//压入
template <typename E>
void Stack<E>::push(E element) {
    bool flag = true;
    if (stackSize + 1 == capacity) {
        flag = expansion(capacity * 2);
    }
    if (!flag) return; // Error
    stack[stackSize++] = element;
}

//取首
template <typename E>
E Stack<E>::top() {

    //判断一下是否为空
    E emptyElement;
    if (!stackSize)
    {
        return emptyElement;
    }
    //不为空就返回TOP
    //qDebug() << "6";
    return stack[stackSize - 1];
}

//弹出
template <typename E>
E Stack<E>::pop() {
    //判断一下是否为空
    E emptyElement;
    if (!stackSize) return emptyElement;
    //不为空就弹出
    stackSize--;
    return stack[stackSize];
}

//清空
template <typename E>
void Stack<E>::clear() {
    //到0就停止弹出
    while (stackSize) pop();
}

//获取大小
template <typename E>
int Stack<E>::getSize() {
    return stackSize;
}

//判断是否为空
template <typename E>
bool Stack<E>::ifEmpty() {
    //如果stackSize == 0就返回Ture, 反之False
    return stackSize == 0;
}
#endif // STACK_H

```
- 数据结构包括：
   - ***Public :*** 
     - 栈的构造器 [ Stack() 与 Stack(int capacity) ]
     - 摧毁栈 [ ~Stack() ]
     - 压入栈     [ void push(E element) ]
     - 从栈弹出   [ E top() ]
     - 取出栈顶   [ E pop() ]
     - 判断是否为空 [ bool ifEmpty() ]
     - 清空栈 [ void clear() ]
     - 查询栈的大小 [ int getSize() ]
  - ***Private :***
      - 栈对象   （ E* stack ）
      - 栈的总容量 （ capacity ）
      - 栈的大小  （ stackSize ）
      - 为栈进行扩容 [ bool expansion(int capacity) ]
- 该数据结构实现了Template所代表的泛型编程，方便于建立一个double类型的操作数栈，建立一个char类的运算符栈。

### Expression数据结构 ：
``` cpp
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
```
- 数据结构包括：
   - ***Public :*** 
     - 表达式的构造器 [ Expression() ]
     - enum状态标签 [ enum State 与 enum Function ]
     - 进行栈操作与表达式构建 [ void insert(char c) ]
     - 运算   
       [ double calculate(const double& num1, const double& numu2, const char& op) ]
     - 获取计算机在线状态   [ QString getStateStr() ]
     - 重组栈 [ rebuildStack() ]
     - 清空栈 [ void clearStack() ]
     - 删除表达式元素 [ void backspace() ]
     - 构建表达式 [ void setExpression(QString str) ]
     - 获得计算中的过程值 [ QString getProcssNum() ] 
     - 获得计算的最终结果 [ QString getResult() ]
     - 获得用户输入的公式表达式 [ QString getExpression() ]
     - 加分扩展内容 [ double function(Function F) ]
  - ***Private :***
      - 操作数栈对象 （Stack \<double> num）
      - 运算符栈对象 （ Stack \<char> op ）
      - 表达式对象  （QString exprStr）
      - 计算机在线状态对象 （State state）
      - 计算机区分操作数与运算符的flag （int count = 0）
      - 计算机进行小数计算时的flag  (double decimal)
      - 判断运算符优先级 [ int priority(const char op) ]
      - 置计算机在线状态 [ bool expansion(int capacity) ]
      - 更新栈 [ void updateStack(int opM) ]
- 数据结构中利用enum来设置了计算机的各种状态，实现了计算机在不同的状态下完成不同的逻辑与算法。
  

## 关键算法流程图 ：

1. handleInput 按键来获取操作数与运算符算法：

![Alt text](handleinput.png)

2. State状态流程图：

![Alt text](state.png)

3. insert表达式与栈的交互算法：

![Alt text](insert.png)


## 测试结果含运行截图：
 

#### 测试用例：

6 * (2 + 3 ) / 5 + 7 = 13

11.2+3*(5.1-0.5) =25

1+(-3) = -2 

1.5.5.           = 1.55

1++2             = 1 + 2 = 3

1/0              =错误！！！！！！

1+(-2)(2+3)      = 错误！！！！！！

#### 扩展功能：
三角函数，平方，开方，历史记录

#### 运行截图：

![Alt text](result.png)