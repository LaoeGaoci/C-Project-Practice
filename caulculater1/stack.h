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
