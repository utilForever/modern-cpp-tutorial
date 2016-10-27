/*************************************************************************
> File Name: default_keyword.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2015/4/27
> Personal Blog: https://github.com/utilForever
> References: http://scottmeyers.blogspot.fr/2014/03/a-concern-about-rule-of-zero.html
************************************************************************/
// In rule of zero example, I quoted that Scott Meyers comment.
// Consider a class Widget that doesn't do resource management.
// Per the rule of zero, it declares none of the five special functions covered by the rule.
// Further assume that its data members are copyable and movable.
// Widget objects are therefore copyable and movable, too.
class Widget1
{
public:
	// No destructor or copy or move functions
};

// Now assume something in the software doesn't work the way it should.
// It could be a behavioral problem (i.e. your run-of-the-mill bug) or it could be a performance problem.
// Either way, debugging ensues. Let's assume that during debugging, it becomes convenient to temporarily
// add a destructor to do something like produce a log message for tracing purposes:
class Widget2
{
public:
	// Temporary destructor
	~Widget2() { }
	// No copy or move functions
};

// The addition of the destructor has the side effect of the disabling generation of the move functions,
// but because Widget is copyable, all the code that used to generate moves will now generate copies.
// In other words, adding a destructor to the class has caused presumably-efficient moves to be silently replaced with presumably-less-efficient copies.
// That strikes me as the kind of thing that (1) is likely to surprise people and (2) could really complicate debugging.

// Scott Meyers inclined to recommend that a better way to rely on the compiler-generated copy and move functions
// is to expressly say that they do the right thing -- to define them via "= default".
class Widget3
{
public:
	Widget3() = default;
	Widget3(const Widget3&) = default;
	Widget3(Widget3&&) = default;

	Widget3& operator=(const Widget3&) = default;
	Widget3& operator=(Widget3&&) = default;
};

// With this approach, the spirit of the rule of zero remains: classes that don't manage resources should be designed
// so that the compiler-generated functions for copying, moving, and destruction do the right things.
// But instead of expressing this by not declaring those functions, it's expressed by declaring them
// explicitly and equally explicitly opting in to the compiler-generated implementations.

int main(int argc, char* argv[])
{
	Widget1 widget1;
	Widget2 widget2;
	Widget3 widget3;

	return 0;
}