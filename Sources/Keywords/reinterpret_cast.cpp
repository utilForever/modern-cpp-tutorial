/*************************************************************************
> File Name: reinterpret_cast.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2016/10/30
> Personal Blog: https://github.com/utilForever
> References: http://en.cppreference.com/w/cpp/language/reinterpret_cast
************************************************************************/
#include <iostream>
#include <cassert>

int f()
{
	return 42;
}

int main()
{
	// Syntax: reinterpret_cast <new_type> (expression)
	// reinterpret_cast converts between types by reinterpreting the underlying bit pattern.
	// Unlike static_cast, but like const_cast, the reinterpret_cast expression does not compile to any CPU instructions.
	// It is purely a compiler directive which instructs the compiler to treat the sequence of bits
	// (object representation) of "expression" as if it had the type "new_type".
	int i = 7;

	// Pointer to integer and back
	// static_cast is an error
	uintptr_t v1 = reinterpret_cast<uintptr_t>(&i);
	std::cout << "The value of &i is 0x" << std::hex << v1 << std::endl;
	int* p1 = reinterpret_cast<int*>(v1);
	assert(p1 == &i);

	// Pointer to function to another and back
	// fp1(): undefined behavior
	void(*fp1)() = reinterpret_cast<void(*)()>(f);
	// fp2(): safe
	int(*fp2)() = reinterpret_cast<int(*)()>(fp1);
	std::cout << std::dec << fp2() << std::endl;

	// Type aliasing through pointer
	char* p2 = reinterpret_cast<char*>(&i);
	if (p2[0] == '\x7')
	{
		std::cout << "This system is little-endian" << std::endl;
	}
	else
	{
		std::cout << "This system is big-endian" << std::endl;
	}

	// Type aliasing through reference
	reinterpret_cast<unsigned int&>(i) = 42;
	std::cout << i << std::endl;
}