#include "relation.h"

int main()
{
	// 确定行列与维数
	int row, col, c;
	// 建立一个关系对象
	Relation r;
	// 提示环节
	cout << "Please enter the cardinality of the set: " << endl;
	cin >> c;
	cout << "Please enter collection elements: " << endl;
	int *data = new int[c];
	for (int i = 0; i < c; i++)
		cin >> data[i];

	// 建立关系矩阵
	int *M = new int[c * c];
	cout << "Relationship Matrix: " << endl;
	for (row = 0; row < c; row++)
		for (col = 0; col < c; col++)
			cin >> M[row * c + col];
	// 构造关系
	r = Relation(c, M);

	// （1）试使用关系性质判断的等价条件（如：自反、对称、传递）判断关系R是否是等价关系？
	cout << endl;

	if (r.IsEqual())
	{
		cout << "It is an equivalence relationship: " << endl;
	}
	else
	{
		cout << "It is not an equivalence relationship: " << endl;
	}

	// （2）若R是等价关系，则求由R诱导的集合A的划分。
	if (r.IsEqual())
	{
		int i, j;
		// 确定是否输完
		int flag = 0;
		int *EClass = new int[r.GetCardinality()];
		r.EqualClasses(EClass);
		cout << "Equivalence classes are divided into : " << endl;

		cout << "{";
		for (i = 0; i < r.GetCardinality(); i++)
		{
			cout << "{";
			for (j = 0; j < r.GetCardinality(); j++)
			{
				if (EClass[j] == i)
				{
					cout << " " << data[j];
					flag++;
				}
			}
			cout << " } ,";
			if (flag == r.GetCardinality())
				break;
		}
		cout << "}";
		cout << endl;
		// （4）求集合A上等价关系的个数。
		cout << "The number of equivalence classes is: " << endl;
		long long int sum = 0;
		for (int i = 1; i <= r.GetCardinality(); i++)
		{
			sum = r.numOfequalClasses(r.GetCardinality(), i) + sum;
		}
		cout << sum;
	}
	else
	{
		// (3) 若R不是等价关系，则求包含R最小的等价关系。
		cout << "The minimum equivalence relationship is: " << endl;
		Relation m = r.minEquivalence();
		m.Output();
	}
	return 0;
}