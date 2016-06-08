#pragma once
#include <iostream>
#include <memory>
using namespace std;

template <class T>
class Matrix
{
	T **pm;
	int n, m; //n-строки, m-столбцы

public:

	class Iterator : public iterator<input_iterator_tag, T>
	{
	private:
		T** database;
		size_t n1;
		size_t m1;
		size_t ind;
	public:
		Iterator(T** data, size_t n, size_t m, size_t index) :
			database(data), n1(n), m1(m), ind(index) { }
		Iterator(const Iterator& it) :
			database(it.database), n1(it.n1), m1(it.m1), ind(it.ind) { }
		Iterator& operator++(int)
		{
			ind++; return *this;
		}
		Iterator& operator++()
		{
			++ind; return *this;
		}

		Iterator& operator+(size_t i)
		{
			ind += i;
			return *this;
		}
		T& operator*() const
		{
			return database[ind / m1][ind % m1];
		}
		bool operator==(const Iterator& it) const
		{
			return ind == it.ind;
		}
		bool operator!=(const Iterator& it) const
		{
			return ind != it.ind;
		}
	};


	//	myelement& index(int n1, int m1);
	Matrix(void);
	Matrix(T **p, int n1, int m1);
	Matrix(const Matrix<T>& matrix);
     Matrix<T>& operator=(const Matrix<T> & matrix);
     void Print();
	Matrix<T> operator* (Matrix<T> &mat1);
	Matrix<T> operator| (Matrix<T> &mat1);
	Matrix<T> operator! ();
	
     Iterator begin()
	{
		return Iterator(pm, n, m, 0);
	}
	
     Iterator end()
	{
		return Iterator(pm, n, m, n*m);
	}

	friend  ostream& operator<< (ostream& out, Matrix<T>& mat1)
	{
		for (int i = 0; i<mat1.n; i++)
		{
			for (int j = 0; j<mat1.m; j++)
				out << mat1.pm[i][j] << " ";
			out << endl;
		}
		return out;
	}

	friend istream& operator >> (istream& in, Matrix<T>& mat1)
	{
		in >> mat1.n;
		cout << " ";
		in >> mat1.m;
		for (int i = 0; i<mat1.n; i++)
		{
			for (int j = 0; j<mat1.m; j++)
				in >> mat1.pm[i][j];
			cout << " ";
		}
		return in;
	}

	~Matrix(void);
};




template<class T>
Matrix<T>::Matrix(void)
{
}

template<class T>
Matrix<T>::Matrix(T **p, int n1, int m1)
{
	n = n1;
	m = m1;
	pm = new T*[n];
	for (int i = 0; i<n; i++)
	{
		pm[i] = new T[m];

		//	memcpy(pm[i], p[i], sizeof(int)*m);
	}

	for (int i = 0;i<n; i++)
	{
		for (int j = 0; j<m; j++)
			pm[i][j] = p[i][j];
	}

}

template<class T> 
Matrix<T>::Matrix(const Matrix<T>& matrix) 
{ 
     pm = new T*[matrix.n]; 
     for (int i = 0; i < matrix.n; i++) 
          pm[i] = new T[matrix.m]; 
     n = matrix.n; 
     m = matrix.m; 
     for (int i = 0; i < n; i++) 
          for (int j = 0; j < m; j++) 
               pm[i][j] = matrix.pm[i][j]; 
}

template<class T> 
Matrix<T>& Matrix<T>::operator=(const Matrix<T> & matrix) 
{ 
     if (this == &matrix) 
          return *this; 

     pm = new T*[matrix.n]; 
     for (int i = 0; i < matrix.n; i++) 
          pm[i] = new T[matrix.m]; 
     n = matrix.n; 
     m = matrix.m; 
     for (int i = 0; i < n; i++) 
          for (int j = 0; j < m; j++) 
               pm[i][j] = matrix.pm[i][j]; 
     return *this; 
}


template<class T>
void Matrix<T>::Print()

{
	for (int i = 0; i<n; i++)
	{
		cout << endl;
		for (int j = 0; j<m; j++)

			//cout << pm[i][j] << " ";
			pm[i][j].PrintForMatr();

	}
}



template<class T>
Matrix<T> Matrix<T>::operator* (Matrix<T> &mat1)// Сложение матриц
{
	T ** pM = new T*[n];

	for (int i = 0; i<n; i++)
	{
		pM[i] = new T[m];
		for (int j = 0; j<m; j++)
			pM[i][j] = pm[i][j] * mat1.pm[i][j];
	}
	Matrix<T> p(pM, n, m);
	//for (int i = 0; i<n; i++) delete[] pM[i];
	//delete[] pM;
	return p;
}


template<class T>
Matrix<T> Matrix<T>::operator| (Matrix<T> &mat1)// Конкатенация матриц
{
	T ** pM = new T*[n];

	for (int i = 0; i<n; i++)
	{
		pM[i] = new T[m + mat1.m];
		for (int j = 0; j<m; j++)
			pM[i][j] = pm[i][j];
		for (int j = m; j<m + mat1.m; j++)
			pM[i][j] = mat1.pm[i][j - m];
	}
	Matrix<T> p(pM, n, m + mat1.m);
	//	for (int i=0; i<n; i++) delete [] pM[i];
	//	delete [] pM;
	return p;

}


template<class T>
Matrix<T> Matrix<T>::operator! ()// Поворот матриц
{
	T ** pM = new T*[m];

	for (int i = 0; i<m; i++)
	{
		pM[i] = new T[n];
		for (int j = 0; j<n; j++)
			pM[i][j] = pm[n - 1 - j][i];
	}
	Matrix<T> p(pM, m, n);
	//for (int i = 0; i<m; i++) delete[] pM[i];
	//delete[] pM;
	return p;
}

template<class T>
Matrix<T>::~Matrix(void)
{
for (int i = 0; i<n; i++) delete[] pm[i];
delete[] pm;
}

