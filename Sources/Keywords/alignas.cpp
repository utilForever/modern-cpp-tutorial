/*************************************************************************
> File Name: alignas.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2016/10/30
> Personal Blog: https://github.com/utilForever
> References: http://en.cppreference.com/w/cpp/language/alignas
> References: http://egloos.zum.com/sweeper/v/3147985
************************************************************************/
#include <iostream>
#include <string>

// alignas specifies the alignment requirement of a type or an object.
// Every object type has the property called alignment requirement,
// which is an integer value (of type std::size_t, always a power of 2)
// representing the number of bytes between successive addresses
// at which objects of this type can be allocated.
struct alignas(4) Student
{
	std::string name;
	int grade;
};

// Valid non-zero alignments that are are weaker than another alignas on the same declaration are ignored.
// alignas(0) is always ignored.
// Invalid non-zero alignments, such as alignas(3) are ill-formed.
// C4359: Alignment specifier is less than actual alignment (8), and will be ignored.
struct alignas(1) Rectangle
{
	double width;
	double height;
};

int main()
{
	std::cout << "Alignment of Student = " << alignof(Student) << std::endl;
	std::cout << "Alignment of Rectangle = " << alignof(Rectangle) << std::endl;
}