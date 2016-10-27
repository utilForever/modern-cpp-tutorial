/*************************************************************************
> File Name: try_catch_throw1.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2015/7/17
> Personal Blog: https://github.com/utilForever
************************************************************************/
#include <iostream>

int Divide(int num, int den)
{
	if (den == 0)
		throw std::invalid_argument("Divide by zero");
	return num / den;

}

int main()
{
	try
	{
		std::cout << Divide(5, 2) << std::endl;
		std::cout << Divide(10, 0) << std::endl;
		std::cout << Divide(3, 3) << std::endl;
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << "Caught exception: " << e.what() << std::endl;
	}

	return 0;
}