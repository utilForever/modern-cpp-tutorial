/*************************************************************************
> File Name: nullptr.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2015/4/16
> Personal Blog: https://github.com/utilForever
************************************************************************/
#include <iostream>

void func(char*);
void func(int*);
void func(int);
void func(std::nullptr_t);

int main(int argc, char* argv[])
{
	// In C++98, Call func(NULL) invokes func(int) because NULL means not "null pointer", but 0. (#define NULL 0)
	// However, it can be ambiguous overload: Three functions except func(int) are candidates.
	func(NULL);

	// In C++11, Call func(nullptr) invokes func(char*) because nullptr really means "null pointer". 
	// If two functions that take pointer argument are exist in code, however, it would be ambiguous without void func(std::nullptr_t).
	func(nullptr);

	// It is important that nullptr is not type. The type of nullptr is "std::nullptr_t".
	std::cout << typeid(nullptr).name() << std::endl;

	return 0;
}

void func(char* val)
{
	std::cout << "func(char*) Called!" << std::endl;
}

void func(int* val)
{
	std::cout << "func(int*) Called!" << std::endl;
}

void func(int val)
{
	std::cout << "func(int) Called!" << std::endl;
}

void func(std::nullptr_t val)
{
	std::cout << "func(std::nullptr_t) Called!" << std::endl;
}