/*************************************************************************
> File Name: dynamic_cast.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2015/7/15
> Personal Blog: https://github.com/utilForever
> References: http://prostars.net/55 
************************************************************************/
#include <iostream>

class Base
{
public:
	virtual void print() { std::cout << "Base" << std::endl; }
};

class Derived : public Base
{
public:
	virtual void print() { std::cout << "Derived" << std::endl; }
};

int main()
{
	Base* base1 = new Base;
	Base* base2 = new Derived;
	Derived* derived1 = new Derived;
	Derived* derived2 = nullptr;

	// Compile Error: Can't convert type
	// derived2 = base1;

	// Compile Success: Fail to convert type and return nullptr at run-time
	derived2 = dynamic_cast<Derived*>(base1);
	if (derived2 == nullptr)
		std::cout << "Runtime Error" << std::endl;

	// Compile Error: Can't convert type
	// derived2 = base2;

	// Compile Success: Success to convert type and return Derived* at run-time
	derived2 = dynamic_cast<Derived*>(base2);
	if (derived2)
		derived2->print();

	// Compile Success: Don't need casting in this case
	derived2 = derived1;
}