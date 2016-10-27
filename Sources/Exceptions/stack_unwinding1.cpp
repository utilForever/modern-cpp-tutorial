/*************************************************************************
> File Name: stack_unwinding1.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2015/7/17
> Personal Blog: https://github.com/utilForever
************************************************************************/

#include <iostream>

void f1() { throw 0; }
void f2() { f1(); }
void f3() { f2(); }
void f4() { f3(); }

int main()
{
	try
	{
		f4();
	}
	catch (int e)
	{
		std::cout << e << std::endl;
	}
}