#include "Matrix.h"
#include <string>
#include <algorithm>
#include <functional>

using namespace std;
using namespace placeholders;

void addNumber(int& number, int i)
{
	number += i;
}
void addIndex(int& number, int& index)
{
	number += index++;
}
bool isSolution_1(int x, int k, int b)
{
	return k*x + b == 0;
}
bool isLess(int number, int bound)
{
	return number < bound;
}
bool isSolution_2(int x, int a, int b, int c)
{
	return a*x*x + b*x + c == 0;
}

void main()

{
	setlocale(LC_ALL, "Russian");
	int** matrix1 = new int*[2];
	for (int i = 0; i<2; i++)
		matrix1[i] = new int[2];
	int** matrix2 = new int*[2];
	for (int i = 0; i<2; i++)
		matrix2[i] = new int[1];

	matrix1[0][0] = 1;
	matrix1[0][1] = -1;
	matrix1[1][0] = 3;
	matrix1[1][1] = 4;

	matrix2[0][0] = 0;
	matrix2[0][1] = 2;
	matrix2[1][0] = 3;
	matrix2[1][1] = 4;

	Matrix<int> matr1(matrix1, 2, 2);
	Matrix<int> matr2(matrix2, 2, 2);

	int k = 1, l = 0;
	int bound = 3;
	int a = 1, b = 0, c = -4, value = 0, num = 3;
	// Сложение каждого элемента матрицы с заданным числом(foreach)
	for_each(matr1.begin(), matr1.end(), bind(addNumber, _1, a));
	cout << matr1 << endl;
	// Сложение каждого элемента матрицы с его порядковым номером (foreach), номера назначаются построчно
	for_each(matr2.begin(), matr2.end(), bind(addIndex, _1, 0));
	cout << matr2 << endl;
	// Найти количество элементов в матрице, равных заданному числу(count)
	cout << count(matr1.begin(), matr1.end(), num) << endl;
	// Найти количество элементов в матрице, удовлетворяющих решению уравнения kx + b = 0 (count_if)
	cout << count_if(matr2.begin(), matr2.end(), bind(isSolution_1, _1, k, l)) << endl;
	// Найти количество элементов в матрице меньше заданного числа(count_if, less())
	cout << count_if(matr1.begin(), matr1.end(), bind(isLess, _1, bound)) << endl;
	// Найти первый элемент, удовлетворяющий решению уравнения ax^2 + bx + c = 0 (find_if)
	cout << *find_if(matr1.begin(), matr1.end(), bind(isSolution_2, _1, a, b, c)) << endl;
	// Проверить в матрице наличие заданного элемента
	cout << *find(matr1.begin(), matr1.end(), value) << endl;

	Matrix<int> result1 = matr1 | matr2;
	Matrix<int> result2 = matr1*matr2;
	Matrix<int> result3 = !matr1;
	cout << matr1 << endl;
	// cout<<matr2<<endl;
	for (auto it = matr2.begin(); it != matr2.end();it++)
		cout << *it << ' ';
	cout << endl;
	cout << result1 << endl;
	cout << result2 << endl;
	cout << result3 << endl;



	/*	Matrix mat1(pm1, n, m), mat2(pm2, n, m),mat3,mat4, mat5;
	mat3=mat1+mat2;

	cout<<endl<<"Матрица 1:"<< endl;
	mat1.Print();
	cout<<endl<<"Матрица 2:"<< endl;
	mat2.Print();
	cout<< endl<<"Матрица1+Матрица2:"<< endl;
	mat3.Print();
	cout<<endl<<"Матрица перевернута"<<endl;
	mat5=!mat1;
	mat5.Print();
	cout<< endl<<"Конкатенация"<< endl;
	mat4=mat1|mat2;
	mat4.Print();
	/*cout<< "Элемент второй матрицы"<<endl;
	mat2.index(1,1).Print();
	cout<<endl;*/
	system("pause");
}