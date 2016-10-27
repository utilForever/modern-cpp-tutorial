/*************************************************************************
> File Name: function_template.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2015/7/23
> Personal Blog: https://github.com/utilForever
************************************************************************/
#include <iostream>

//int max(int a, int b)
//{
//	return a > b ? a : b;
//}

//double max(double a, double b)
//{
//	return a > b ? a : b;
//}

template <typename T>
T max(T a, T b)
{
	return a > b ? a : b;
}

int main()
{
	int a = 300;
	int b = 400;
	// std::cout << "max(300, 400) = " << max(a, b) << std::endl;
	std::cout << "max(300, 400) = " << max<int>(a, b) << std::endl;

	double c = 14.8;
	double d = 21.5;
	// std::cout << "max(14.8, 21.5) = " << max(c, d) << std::endl;
	std::cout << "max(14.8, 21.5) = " << max<double>(c, d) << std::endl;
}