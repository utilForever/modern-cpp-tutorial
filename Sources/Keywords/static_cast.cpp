/*************************************************************************
> File Name: static_cast.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2016/10/28
> Personal Blog: https://github.com/utilForever
> References: http://en.cppreference.com/w/cpp/language/static_cast
************************************************************************/
#include <iostream>
#include <vector>

struct Base
{
	void PrintName() const
	{
		std::cout << "This is Base!" << std::endl;
	}

	int m_age = 28;
};

struct Derived : Base
{
	void PrintName() const
	{
		std::cout << "This is Derived!" << std::endl;
	}
};

enum class E1 { ZERO, ONE, TWO };
enum class E2 { FIRE, WATER, EARTH };

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
	std::cout << std::endl;

	// 3. Lvalue to Xvalue
	// Lvalue is a GLvalue that is not an Xvalue.
	// Xvalue is a GLvalue that denotes an object or bit-field whose resources can be reused.
	// For more information, see "value_categories.cpp".
	// '&&' is Rvalue reference. For more information, see "rvalue_reference.cpp".
	std::vector<int> v1 = static_cast<std::vector<int>>(10);
	std::cout << "v1.size() = " << v1.size() << std::endl;
	std::vector<int> v2 = static_cast<std::vector<int>&&>(v1);
	std::cout << "After move, v2.size() = " << v2.size() << std::endl;
	std::cout << std::endl;

	// 4. Inverse of implicit conversion
	// (Don't recommend that way.)
	int val = 89;
	void* nvVal = &val;
	int* niVal = static_cast<int*>(nvVal);
	std::cout << "*niVal = " << *niVal << std::endl;
	std::cout << std::endl;

	// 5. array-to-pointer followed by upcast
	Derived dArr[10];
	Base* pArr = static_cast<Base*>(dArr);

	// 6. Scoped-enum to int or float
	// In Scoped-enum, there are no implicit conversions from the values of a scoped enumerator to integral types,
	// although static_cast may be used to obtain the numeric value of the enumerator.
	// For more information, see "scoped_enum.cpp".
	E1 e = E1::ONE;
	int one = static_cast<int>(e);
	std::cout << one << std::endl;
	std::cout << std::endl;

	// 7. int to enum, enum to another enum
	E1 e1 = static_cast<E1>(e);
	E2 e2 = static_cast<E2>(e1);

	// 8. Pointer to member upcast
	int Derived::*pAge = &Derived::m_age;
	std::cout << b.*static_cast<int Base::*>(pAge) << std::endl;
	std::cout << std::endl;

	// 9. void* to any type
	// (Don't recommend that way.)
	void* pVoid = &e;
	std::vector<int>* pvInt = static_cast<std::vector<int>*>(pVoid);
}