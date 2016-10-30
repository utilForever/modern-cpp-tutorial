/*************************************************************************
> File Name: const_cast.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2016/10/30
> Personal Blog: https://github.com/utilForever
> References: http://en.cppreference.com/w/cpp/language/const_cast
************************************************************************/
#include <iostream>

struct Type
{
	Type() : m_i(3)
	{
		
	}

	void RemoveConst(int v) const
	{
		// Compile error: this is a pointer to const
		// this->m_i = v;
		// Compile success: the Type object isn't const
		const_cast<Type*>(this)->m_i = v;
	}

	int m_i;
};

int main()
{
	// const_cast converts between types with different cv-qualification.
	// and sideways along the inheritance hierarchy.
	int i = 3;
	const int& cref_i = i;
	const_cast<int&>(cref_i) = 4;
	std::cout << "i = " << i << std::endl;

	// Note: if this is const Type t, then t.RemoveConst(4); is undefined behavior.
	Type t;
	t.RemoveConst(4);
	std::cout << "Type::m_i = " << t.m_i << std::endl;

	// j is declared const
	const int j = 3;
	int* p_j = const_cast<int*>(&j);
	// Undefined behavior
	*p_j = 4;

	// Note: pointers to functions and pointers to member functions are not subject to const_cast
	// Pointer to member function
	void (Type::*m_fp)(int) const = &Type::RemoveConst;
	// Compile error: const_cast doesn't work on function pointers
	// const_cast<void(Type::*)(int)>(m_fp);
}