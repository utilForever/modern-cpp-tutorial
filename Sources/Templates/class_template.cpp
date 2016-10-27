/*************************************************************************
> File Name: class_template.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2015/7/23
> Personal Blog: https://github.com/utilForever
************************************************************************/
#include <iostream>

//class Calc
//{
//public:
//	int add(int x, int y);
//	int multiply(int x, int y);
//};
//
//int Calc::add(int x, int y)
//{
//	return x + y;
//}
//
//int Calc::multiply(int x, int y)
//{
//	return x * y;
//}

template <typename T>
class Calc
{
public:
	T add(T x, T y);
	T multiply(T x, T y);
};

template <typename T>
T Calc<T>::add(T x, T y)
{
	return x + y;
}

template <typename T>
T Calc<T>::multiply(T x, T y)
{
	return x * y;
}

int main()
{
	//Calc c;
	//std::cout << "3 + 4 = " << c.add(3, 4) << std::endl;
	//std::cout << "7 * 8 = " << c.multiply(7, 8) << std::endl;
	//std::cout << "5.41 + 7.65 = " << c.add(5.41, 7.65) << std::endl;
	//std::cout << "3.14 * 4.5 = " << c.multiply(3.14, 4.5) << std::endl;

	Calc<int> intCalc;
	std::cout << "3 + 4 = " << intCalc.add(3, 4) << std::endl;
	std::cout << "7 * 8 = " << intCalc.multiply(7, 8) << std::endl;

	Calc<double> doubleCalc;
	std::cout << "5.41 + 7.65 = " << doubleCalc.add(5.41, 7.65) << std::endl;
	std::cout << "3.14 * 4.5 = " << doubleCalc.multiply(3.14, 4.5) << std::endl;
}