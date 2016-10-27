/*************************************************************************
> File Name: RAII-rule_of_zero.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2015/4/26
> Personal Blog: https://github.com/utilForever
> References: http://www.cppsamples.com/common-tasks/rule-of-zero.html
> References: http://scottmeyers.blogspot.fr/2014/03/a-concern-about-rule-of-zero.html
************************************************************************/
// Utilize the value semantics of existing types 
// to implement custom copy and move operations.
#include <memory>
#include <vector>

// The rule of zero states that we can avoid writing any custom copy / move constructors, assignment operators, or destructors 
// by using existing types that support the appropriate copy / move semantics.
// However, Scott Meyers inclined to recommend that a better way to rely on the complier-generated copy and move functions is
// to expressly say that they do the right thing -- to define them via = default (defaultKeyword.cpp).
// because the addition of the destructor has the side effect of disabling generation of the move functions.

// The class RO0_1, for example, does not perform any manual memory management,
// yet correctly supports copies and moves without any memory leaks.
// The defaulted copy / move constructors and assignment operators will simply copy or move each member.
class RO0_1
{
private:
	// For the int x, this will copy its value.
	int x = 10;
	// For v, which is a std::vector, all of its elements will be copied over.
	std::vector<int> v = { 1, 2, 3, 4, 5 };
};

// The class RO0_2 is not copyable by default because it has a std::unique_ptr member
// which itself is not copyable. However, it correctly supports move operations,
// which will transfer ownership of the dynamically allocated resource.
class RO0_2
{
public:
	std::unique_ptr<int> p = std::make_unique<int>(5);
};

int main(int argc, char* argv[])
{
	RO0_1 ro0_1;
	RO0_2 ro0_2;

	return 0;
}