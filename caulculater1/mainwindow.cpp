#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

//将InPut里的公式传入
void MainWindow::Input() {
    ui->InPut->setText(expr.getExpression());
}

//将结果显示在OutPut里
void MainWindow::Output(){
    ui->OutPut->setText(expr.getResult());
}
void MainWindow::refreshProcessResult() {
    QString tmpAns = expr.getProcssNum();
    if (tmpAns.size()) {
        ui->OutPut->setText(tmpAns);
    }
}


//按下特殊扩展按钮后的捕捉
void MainWindow::handleInput(Expression::Function f) {
    double num = expr.function(f);
    ui->InPut->setText(QString::number(num));
    ui->OutPut->setText(QString::number(num));
}


//根据按钮进行操作
void MainWindow::handleInput(char c) {
    switch(c) {
    //清屏操作
    case 'x':
        expr.clearStack();
        ui->InPut->clear();
        ui->OutPut->clear();
        break;
    //删除操作
    case '<':{
        expr.backspace();
        ui->OutPut->clear();
        refreshProcessResult();
        break;
    }
    default:
        expr.insert(c);
        refreshProcessResult();
        ui->OutPut->clear();
        if (c == '#') {
            updateHistory();
            Output();
            expr.clearStack();
        }
    }
    Input();
}

//更新历史记录区域
void MainWindow::updateHistory() {
    ui->History->setPlainText(
        expr.getExpression().append("\n").append(expr.getResult()).append("\n").append("\n").append(ui->History->toPlainText()));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置窗口标题
    setWindowTitle("鄂老师的计算器啊");
    //符号数
    connect(ui->Button0,   &QPushButton::clicked, this ,[=](){handleInput('0');});
    connect(ui->Button1,   &QPushButton::clicked, this ,[=](){handleInput('1');});
    connect(ui->Button2,   &QPushButton::clicked, this ,[=](){handleInput('2');});
    connect(ui->Button3,   &QPushButton::clicked, this ,[=](){handleInput('3');});
    connect(ui->Button4,   &QPushButton::clicked, this ,[=](){handleInput('4');});
    connect(ui->Button5,   &QPushButton::clicked, this ,[=](){handleInput('5');});
    connect(ui->Button6,   &QPushButton::clicked, this ,[=](){handleInput('6');});
    connect(ui->Button7,   &QPushButton::clicked, this ,[=](){handleInput('7');});
    connect(ui->Button8,   &QPushButton::clicked, this ,[=](){handleInput('8');});
    connect(ui->Button9,   &QPushButton::clicked, this ,[=](){handleInput('9');});
    connect(ui->ButtonDot, &QPushButton::clicked, this ,[=](){handleInput('.');});
    //运算符
    connect(ui->ButtonAdd, &QPushButton::clicked, this ,[=](){handleInput('+');});
    connect(ui->ButtonSubtract, &QPushButton::clicked, this ,[=](){handleInput('-');});
    connect(ui->ButtonMul, &QPushButton::clicked, this ,[=](){handleInput('*');});
    connect(ui->ButtonDiv, &QPushButton::clicked, this ,[=](){handleInput('/');});
    connect(ui->ButtonLeft,  &QPushButton::clicked, this ,[=](){handleInput('(');});
    connect(ui->ButtonRight,  &QPushButton::clicked, this ,[=](){handleInput(')');});
    connect(ui->ButtonEqual,     &QPushButton::clicked, this ,[=](){handleInput('#');});
    //清屏，撤回
    connect(ui->ButtonAC,     &QPushButton::clicked, this ,[=](){handleInput('x');});
    connect(ui->ButtonDLE, &QPushButton::clicked, this ,[=](){handleInput('<');});
    //三角函数
    connect(ui->ButtonSin, &QPushButton::clicked, this ,[=](){handleInput(Expression::Function::SIN);});
    connect(ui->ButtonCos, &QPushButton::clicked, this ,[=](){handleInput(Expression::Function::COS);});
    connect(ui->ButtonTan, &QPushButton::clicked, this ,[=](){handleInput(Expression::Function::TAN);});
    connect(ui->ButtonAsin, &QPushButton::clicked, this ,[=](){handleInput(Expression::Function::ASIN);});
    connect(ui->ButtonAcos, &QPushButton::clicked, this ,[=](){handleInput(Expression::Function::ACOS);});
    //平方开方
    connect(ui->ButtonSqrt, &QPushButton::clicked, this ,[=](){handleInput(Expression::Function::SQRT);});
    connect(ui->ButtonSqu, &QPushButton::clicked, this ,[=](){handleInput(Expression::Function::SQU);});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InPut_textChanged(const QString &arg1)
{
    expr.setExpression(arg1);
    Input();
    refreshProcessResult();
}

