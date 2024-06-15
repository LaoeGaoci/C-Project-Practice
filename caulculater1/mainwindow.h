#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "expression.h"
#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void InPut_textChanged(const QString &arg1);

private:
  // 输入显示与输出显示
  void Input();
  void Output();

  Ui::MainWindow *ui;
  Expression expr;

  // 按照按钮输入
  void handleInput(Expression::Function f);
  void handleInput(char c);
  // 更新
  void refreshProcessResult();
  void updateHistory();
};
#endif // MAINWINDOW_H
