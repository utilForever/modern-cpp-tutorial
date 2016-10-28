/*************************************************************************
> File Name: static_cast.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2016/10/28
> Personal Blog: https://github.com/utilForever
> References: http://en.cppreference.com/w/cpp/language/static_cast
************************************************************************/
#include <iostream>

struct Base
{
	void PrintName() const
	{
		std::cout << "This is Base!" << std::endl;
	}
};

struct Derived : Base
{
	void PrintName() const
	{
		std::cout << "This is Derived!" << std::endl;
	}
};

int main(int argc, char* argv[])
{
	// 1. C-style cast vs C++-style cast
	// C-style cast: (type)
	// (type) converts between types using a combination of implicit and user-defined conversion
	// regardless of constness or volatility.
	int n1 = (int)3.14;
	std::cout << "n1 = " << n1 << std::endl;
	// C++-style cast: static_cast
	// static_cast converts between types using a combination of implicit and user-defined conversions
	// except when conversions would cast away constness or volatility.
	int n2 = static_cast<int>(3.14);
	std::cout << "n2 = " << n2 << std::endl;
	std::cout << std::endl;

	// 2. Static downcast
	Derived d;
	// Upcast via implicit conversion
	Base& b = d;
	b.PrintName();
	// Downcast
	Derived& anotherD = static_cast<Derived&>(b);
	anotherD.PrintName();

	// 3. Lvalue to Xvalue

}