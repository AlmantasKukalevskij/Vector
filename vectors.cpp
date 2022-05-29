#include <iostream>
#include <vector>
#include "timer.h"

template<class T>
class customVector
{
	int vsize, maxsize;
	T* array;

	void alloc_new();

public:
	customVector();
	customVector(int);
	customVector(const customVector&); // copy constructor
	~customVector();

	void push_back(const T&);
	int size();

	T operator[](int);
	customVector& operator= (const customVector&);
	customVector& operator+= (const T&);

	int at(T&);
};

template<class T>
customVector<T>::customVector()
{
	maxsize = 20;
	array = new T[maxsize];
	vsize = 0;
}

template<class T>
customVector<T>::customVector(int i)
{
	maxsize = i;
	array = new T[maxsize];
	vsize = 0;
}

template<class T>
customVector<T>::customVector(const customVector& v)
{
	maxsize = v.maxsize;
	vsize = v.vsize;
	array = new T[maxsize];

	for (int i = 0; i < v.vsize; i++) {
		array[i] = v.array[i];
	}
}

template<class T>
customVector<T>::~customVector()
{
	delete[] array;
}

template<class T>
void customVector<T>::push_back(const T& i)
{
	if (vsize + 1 > maxsize)
		alloc_new();

	array[vsize] = i;
	vsize++;
}

template<class T>
T customVector<T>::operator[](int i)
{
	return array[i];
}

template<class T>
int customVector<T>::at(T& i)
{
	if (i < vsize)
		return array[i];
	throw 10;
}

template<class T>
void customVector<T>::alloc_new()
{
	maxsize = vsize * 2;
	T* tmp = new T[maxsize];

	for (int i = 0; i < vsize; i++)
		tmp[i] = array[i];

	delete[] array;
	array = tmp;
}

template<class T>
int customVector<T>::size()
{
	return vsize;
}

template<class T>
customVector<T>& customVector<T>::operator+= (const T& i)
{
	this->push_back(i);

	return *this;
}

template<class T>
customVector<T>& customVector<T>::operator= (const customVector& v)
{
	if (this != &v) {

		maxsize = v.maxsize;
		vsize = v.vsize;
		delete[] array;
		array = new T[maxsize];

		for (int i = 0; i < v.vsize; i++) {
			array[i] = v.array[i];
		}
	}
	return *this;
}

int main()
{
	{
		Timer t("std::vector pildymas uztruko:");

		std::cout << "std::vector uzpildymo laikas pradetas..." << std::endl;
		unsigned int sz = 100000;  // 100000, 1000000, 10000000, 100000000
		std::vector<int> v1;
		for (int i = 1; i <= sz; ++i)
			v1.push_back(i);
		//v1.clear();
	}

	{
		Timer t("customVector pildymas uztruko:");

		std::cout << "customVector uzpildymo laikas pradetas..." << std::endl;
		unsigned int sz = 100000;  // 100000, 1000000, 10000000, 100000000
		customVector<int> v2;
		for (int i = 1; i <= sz; ++i)
			v2.push_back(i);

		//std::cout << v2[99999999] << std::endl;
	}

	return 0;
}