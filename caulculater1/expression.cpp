#include "expression.h"
#include "stack.h"
#include <math.h>

//初始化
Expression::Expression(): state(START), decimal(0.1) {}
//获得在线状态
QString Expression::getStateStr() {
    switch(state) {
    case START:
        return "START";

    case OPERATOR:
        return "OPERATOR";

    case INTEGER:
        return "INTEGER";

    case DECIMAL_POINT:
        return "DECIMAL_POINT";

    case DECIMAL:
        return "DECIMAL";

    case FINISHED: // Never
        return "FINISHED";
    }
}

//更新状态
void Expression::setState(State state) {
    this->state = state;
}

//建立一个表达式
void Expression::setExpression(QString str) {
    exprStr = str;
    rebuildStack();
}

//获取表达式
QString Expression::getExpression() {
    return exprStr.replace("0-", "-");
}

//全部清空
void Expression::clearStack() {
    num.clear();
    op.clear();
    exprStr.clear();
    //清空完成后把计算机状态调回开始
    setState(START);
}
//重新构造栈
void Expression::rebuildStack(){
    QString tmpStr = exprStr;
    //清空原有栈
    clearStack();
    for(int i = 0; i < tmpStr.length(); i++){
        insert(tmpStr[i].toLatin1());
    }
}

void Expression::backspace() {
    //将组建好的字符串减一
    exprStr = exprStr.left(exprStr.size() - 1);
    //重新构造栈
    rebuildStack();
}
//确定优先级
int Expression::priority(char op){
    if(op == '+'||op == '-'){
        return 0;
    }else {
        if(op == '*'||op == '/'){
            return 1;
        }else{
            return -1;
        }
    }
}

//根据运算符进行计算
double Expression::calculate(const double& num1, const double& num2, const char& op){
    switch(op){
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        return num1 / num2;
    default:
        return 0;
    }
}

//更新栈里的数据
void Expression::updateStack(int opM = -1) {
    while(num.getSize() > 1 && !op.ifEmpty() && priority(op.top()) >= opM && op.top() != '('){
        //将两个数从操作符弹出
        double num2 = num.pop();
        double num1 = num.pop();
        char opc = op.pop();
        double res = calculate(num1, num2, opc);
        num.push(res);
    }
}

QString Expression::getProcssNum() {
    if (num.getSize() == 1) {
        return QString::number(num.top());
    }
    return "";
}
//表达式的加入与运算
void Expression::insert(const char c) {

    if (state == FINISHED) {
        clearStack();
    }
    //输入等号刷新数据
    if (c == '#') {
        updateStack();
        return;
    }

    if ('0' <= c && c <= '9') {
        count = 1;
        //压入个位数
        if(state == START){
            setState(OPERATOR);
        }
        if(state == OPERATOR){
            num.push(c - '0');
            setState(INTEGER);
        }else{
            if(state == INTEGER){
                num.push(num.pop() * 10 + c - '0');
            }
        }
        //计算小数
        if(state == DECIMAL_POINT) {
            setState(DECIMAL);
        }
       if(state == DECIMAL){
            num.push(num.pop() + decimal * (c - '0'));
            decimal *= 0.1;
        }

        //结束
       if(state ==  FINISHED) // Never
            return;

    } else if (c == '+' || c == '-' || c == '*' || c == '/') {//如果为运算符
       //如果在表达式开头输入'-'
       if(state == START){
            if (c == '-') {
                insert('0');
                insert('-');
            }
            if (c == '+') {
              exprStr.append(c);
            }
            if (c == '/') {
              exprStr.append(c);
            }
            if (c == '*') {
              exprStr.append(c);
            }
            if (c == ')') {
              exprStr.append(c);
            }
            return;
       }else{
            if(count == 1){
                count = 0;
                setState(OPERATOR);
                updateStack(priority(c));
                op.push(c);

                if(state == FINISHED)
                    return;
            }
       }

    } else if (c == '(') {
            op.push(c);
            setState(START);
            if(state == FINISHED)
            return;
    } else if (c == ')') {
            //先算括号里的
            updateStack();
            if (op.top() != '('){

            }else{
            op.pop();
            if(state == FINISHED)
                return;
            }
    }  else if (c == '.') {
            //此处设置如果现在计算器状态为DECIMAL则保持
            if(state ==  DECIMAL)
            {

            }else{
            //如果不是则设置为DECIMAL_POINT
            decimal= 0.1;
            setState(DECIMAL_POINT);
            if(state ==  FINISHED)
                return;
            }
        }
    else {
        return;
    }
    exprStr.append(c);
}


//衍生功能函数
double Expression::function(Function F){
    double num1 = num.top();
    switch (F) {
    //三角函数
    case SIN:
        num1 = sin(num1);
        return num1;
        break;
    case COS:
        num1 = cos(num1);
        return num1;
        break;
    case TAN:
        num1 = tan(num1);
        return num1;
        break;
    case ASIN:
        num1 = asin(num1);
        return num1;
        break;
    case ACOS:
        num1 = acos(num1);
        return num1;
        break;
    //平方与开方
    case SQRT:
        num1 = sqrt(num1);
        return num1;
        break;
    case SQU:
        num1 = num1 * num1;
        return num1;
        break;
    }
}





//获得最后结果
QString Expression::getResult(){
    if(op.ifEmpty() && num.getSize() == 1)
        //如果TOPNUM为无限
        if(num.top() == INFINITY){
            return "错误！！！！！！";
        }else {
            return QString::number(num.top());
        }
    else{
        return "错误！！！！！！";
    }

}
