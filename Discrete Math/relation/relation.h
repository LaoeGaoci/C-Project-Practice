#include "stdio.h"
#include <iostream>
#include <string.h>

using namespace std;

class Relation {
protected:
  int cardinality;
  int *Matrix;

public:
  Relation(int c = 1); // 构造基数为c的空关系，如果不输入c的值，则默认为1
  Relation(
      int c,
      const int *M); // 由输入的关系矩阵的数与一个关系矩阵的值的数组构造关系
  Relation(const Relation &r); // 拷贝构造函数
  ~Relation();                 // 析构函数

  Relation &operator=(const Relation &r); // 赋值运算符重载
  int GetCardinality() const;             // 返回关系矩阵的基数
  int GetPosition(int row, int column)
      const; // 得到关系矩阵的第row行第column列的值，如果越界则返回-1
  // 如果越界则返回-1
  bool GetMatrix(int *result) const; // 得到关系矩阵的值
  void Output() const;               // 在屏幕显示该关系的关系矩阵

  bool IsReflexive() const;  // 判断该关系是否自反
  bool IsSymmetric() const;  // 判断该关系是否对称
  bool IsTransitive() const; // 判断该关系是否传递

  Relation ReflexiveClosure() const;  // 返回自反闭包的关系矩阵
  Relation SymmetricClosure() const;  // 返回对称闭包的关系矩阵
  Relation TransitiveClosure() const; // 返回传递闭包的关系矩阵

  bool IsEqual() const; // 判断该关系是否是一个等价关系

  Relation minEquivalence() const; // 求最小的等价关系

  long long int numOfequalClasses(int n, int m);

  void EqualClasses(int *result) const; // 等价类
};

// 构造一个基数为c的空关系
Relation::Relation(int c) {
  cardinality = c;
  Matrix = new int[cardinality * cardinality];
  memset(Matrix, 0, sizeof(int) * cardinality * cardinality);
}

// 由关系矩阵的基数和一个关系矩阵的值的数组构造关系
Relation::Relation(int c, const int *M) {
  cardinality = c;
  Matrix = new int[cardinality * cardinality];
  memcpy(Matrix, M, sizeof(int) * cardinality * cardinality);
}

Relation::~Relation() {
  // 析构函数
  delete[] Matrix;
}

// 拷贝构造函数
Relation::Relation(const Relation &r) {
  cardinality = r.cardinality;
  Matrix = new int[cardinality * cardinality];
  memcpy(Matrix, r.Matrix, sizeof(int) * cardinality * cardinality);
}

// 赋值运算符重载
Relation &Relation::operator=(const Relation &r) {
  cardinality = r.cardinality;
  Matrix = new int[cardinality * cardinality];
  memcpy(Matrix, r.Matrix, sizeof(int) * cardinality * cardinality);
  return *this;
}

// 得到关系矩阵的基数
int Relation::GetCardinality() const { return cardinality; }

// 得到关系矩阵的第row行第column列的值，如果越界则返回-1
int Relation::GetPosition(int row, int column) const {
  if (row >= 0 && row < cardinality && column >= 0 && column < cardinality)
    return Matrix[row * cardinality + column];
  else
    return -1;
}

// 得到关系矩阵的值
bool Relation::GetMatrix(int *result) const {

  if (result != NULL) {
    memcpy(result, Matrix, sizeof(int) * cardinality * cardinality);
    return true;
  }
  return false;
}

// 在控制台显示该关系的关系矩阵
void Relation::Output() const {
  int row, column;
  // cout << cardinality << encl;
  for (row = 0; row < cardinality; row++) {
    for (column = 0; column < cardinality; column++) {
      cout << Matrix[row * cardinality + column];
    }
    cout << "\n";
  }
}

// 自反性
bool Relation::IsReflexive() const {
  for (int i = 0; i < cardinality; ++i) {
    if (GetPosition(i, i) == 0)
      return false;
  }
  return true;
}

// 对称性
bool Relation::IsSymmetric() const {
  for (int i = 0; i < cardinality - 1; ++i) {
    for (int j = i; j < cardinality; ++j) {
      if (GetPosition(i, j) != GetPosition(j, i)) {
        return false;
      }
    }
  }
  return true;
}

// 传递性
bool Relation::IsTransitive() const {
  // Toco：判断该关系的性质
  for (int i = 0; i < cardinality; ++i) {
    for (int j = 0; j < cardinality; ++j) {
      for (int k = 0; k < cardinality; ++k) {
        if (GetPosition(i, j) == 1 && GetPosition(j, k) == 1 &&
            GetPosition(i, k) != 1) {
          return false;
        }
      }
    }
  }
  return true;
}

// 判断该关系是否是一个等价关系
bool Relation::IsEqual() const {
  return IsReflexive() && IsSymmetric() && IsTransitive();
}

// 返回自反闭包的关系矩阵
Relation Relation::ReflexiveClosure() const {
  int *m = new int[cardinality * cardinality];
  GetMatrix(m);

  for (int i = 0; i < cardinality; i++) {
    if (m[i * cardinality + i] != 1)
      m[i * cardinality + i] = 1;
  }

  Relation r(cardinality, m);
  return r;
}

// 返回对称闭包的关系矩阵
Relation Relation::SymmetricClosure() const {
  int *m = new int[cardinality * cardinality];
  GetMatrix(m);
  int *temp = new int[cardinality * cardinality];
  for (int i = 0; i < cardinality; ++i) {
    for (int j = 0; j < cardinality; ++j) {
      temp[i * cardinality + j] = temp[j * cardinality + i] =
          m[i * cardinality + j] || m[j * cardinality + i];
    }
  }

  Relation r(cardinality, temp);
  return r;
}

// 返回传递闭包的关系矩阵
Relation Relation::TransitiveClosure() const {
  int *m = new int[cardinality * cardinality];
  GetMatrix(m);

  for (int i = 0; i < cardinality; i++) {
    for (int j = 0; j < cardinality; j++) {
      if (m[j * cardinality + i] == 1) {
        for (int k = 0; k < cardinality; k++) {
          m[j * cardinality + k] =
              (m[j * cardinality + k] || m[i * cardinality + k]);
        }
      }
    }
  }
  Relation r(cardinality, m);
  return r;
}

// 先求自反闭包，再求对称闭包，最后求传递闭包
Relation Relation::minEquivalence() const {
  return ReflexiveClosure().SymmetricClosure().TransitiveClosure();
}
// 等价关系的数目
long long int Relation::numOfequalClasses(int n, int m) {
  if (m == 1 || n == m)
    return 1;
  else
    return numOfequalClasses(n - 1, m - 1) + numOfequalClasses(n - 1, m) * m;
}

void Relation::EqualClasses(int *result) const {
  for (int h = 0; h < cardinality; h++) {
    result[h] = 0;
  }
  if (IsEqual()) {
    int min = 0;                            // 当前的最大等价类编号
    for (int i = 0; i < cardinality; i++) { // 目标列编号
      for (int j = 0; j <= i; j++) {        // 当前扫描的列的编号
        bool flag = false;
        for (int k = 0; k < cardinality; k++) { // 行对比的循环
          if (GetPosition(k, i) != GetPosition(k, j)) {
            flag = true;
            break;
          }
        }
        if (!flag) {    // 存在相同的列
          if (j != i) { // 与之前某列相同
            result[i] = result[j];
          } else { // 自己与自己相同
            result[i] = min;
            min++;
          }
          break;
        }
      }
    }
  } else {
    memset(result, 255, sizeof(int) * cardinality);
  }
}
