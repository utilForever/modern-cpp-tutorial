/*************************************************************************
> File Name: stack_unwinding2.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2015/7/17
> Personal Blog: https://github.com/utilForever
************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <memory>

void funcOne() throw(std::exception);
void funcTwo() throw(std::exception);

int main()
{
	try
	{
		funcOne();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception caught!" << std::endl;
		return 1;
	}
	return 0;
}

void funcOne() throw(std::exception)
{
	std::string str1;
	std::unique_ptr<std::string> str2(new std::string(""));
	funcTwo();

	//string* str2 = new string();
	//try
	//{
	//	funcTwo();
	//}
	//catch (...) {
	//	delete str2;
	//	throw;	// Re-send exception
	//}
	//
	//delete str2;
}

void funcTwo() throw(std::exception)
{
	std::ifstream istr;
	istr.open("fileName");
	throw std::exception();
	istr.close();
}