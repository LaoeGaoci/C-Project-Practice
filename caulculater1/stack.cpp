#include "stack.h"

// 构造器
template <typename E> Stack<E>::Stack() : capacity(DEFAULT_CAP), stackSize(0) {
  stack = (E *)malloc(sizeof(E) * DEFAULT_CAP);
  if (!stack) { // Error
    qDebug() << "Stack Construction Error";
  }
}

template <typename E>
Stack<E>::Stack(int capacity) : capacity(capacity), stackSize(0) {
  stack = (E *)malloc(sizeof(E) * capacity);
  if (!stack) { // Error
    qDebug() << "Stack Construction Error";
  }
}

template <typename E> Stack<E>::~Stack() {
  free(stack);
  stack = nullptr;
}

// 扩容
template <typename E> bool Stack<E>::expansion(int capacity) {
  E *newStack;
  newStack = (E *)realloc(stackSize, sizeof(E) * capacity);
  if (newStack) {
    this->capacity = capacity;
    stackSize = newStack;
    return true;
  }
  return false;
}

// 压入
template <typename E> void Stack<E>::push(E element) {
  bool flag = true;
  if (stackSize + 1 == capacity) {
    flag = expansion(capacity * 2);
  }
  if (!flag)
    return; // Error
  stack[stackSize++] = element;
}

// 取首
template <typename E> E Stack<E>::top() {
  // 判断一下是否为空
  E emptyElement;
  if (!stackSize)
    return emptyElement;
  // 不为空就返回TOP
  return stack[stackSize - 1];
}

// 弹出
template <typename E> E Stack<E>::pop() {
  // 判断一下是否为空
  E emptyElement;
  if (!stackSize)
    return emptyElement;
  // 不为空就弹出
  stackSize--;
  return stack[stackSize];
}

// 清空
template <typename E> void Stack<E>::clear() {
  // 到0就停止弹出
  while (stackSize)
    pop();
}

// 获取大小
template <typename E> int Stack<E>::getSize() { return stackSize; }

// 判断是否为空
template <typename E> bool Stack<E>::ifEmpty() {
  // 如果stackSize == 0就返回Ture, 反之False
  return stackSize == 0;
}
