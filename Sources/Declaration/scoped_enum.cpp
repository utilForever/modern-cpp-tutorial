/*************************************************************************
> File Name: scoped_enum.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2015/4/19
> Personal Blog: https://github.com/utilForever
************************************************************************/
#include <iostream>

// Unscoped enum in C++98 
enum Cpp98Color { RED, GREEN, BLUE };
enum Cpp98Job { WARRIOR, ARCHER, WIZARD };

// Scoped enum in C++11
enum class Cpp11Color { RED, GREEN, BLUE };
enum class Cpp11Job { WARRIOR, ARCHER, WIZARD };

// In C++98, declares an unscoped type
// whose underlying type is not fixed.
enum Cpp98Altitude
{
	HIGH = 'h',
	LOW = 'l'
};

// In C++11, declares an unscoped enumeration type
// whose underlying type is fixed.
// (includes an scoped enumeration type)
enum class Cpp11Altitude : char {
	HIGH = 'h',
	LOW = 'l'
};

// Enum that takes 16 bits in C++11
enum UpperEnum : int16_t
{
	A,
	B,
	C
};

// The constant D is 0, D is 20, F is 23
enum LowerEnum { D, E = 20, F = D + E + 3 };

// Unscoped enumeration types can have overloaded operators
std::ostream& operator<<(std::ostream& os, Cpp98Altitude altitude)
{
	return os << static_cast<char>(altitude);
}

// Scoped enumeration types can have overloaded operators
std::ostream& operator<<(std::ostream& os, Cpp11Altitude altitude)
{
	return os << static_cast<char>(altitude);
}

int main(int argc, char* argv[])
{
	Cpp98Color cpp98Color = GREEN;
	Cpp98Job cpp98Job = ARCHER;

	// cpp98Color's value is GREEN, cpp98Job's value is ARCHER.
	// Definitely, it is not same.
	// However, enumeration value is implicitly-converted to "int".
	// So, GREEN is converted to 2, ARCHER is converted to 2.
	// Therefore, cpp98Color == cpp98Job is true.
	if (cpp98Color == cpp98Job)
		std::cout << "Cpp98Color's GREEN equals Cpp98Job's ARCHER" << std::endl;

	// Values of unscoped enumeration type are
	// implicitly-convertible to integral types.
	int colorNum = cpp98Color;
	int jobNum = cpp98Job;

	Cpp11Color cpp11Color = Cpp11Color::GREEN;
	Cpp11Job cpp11Job = Cpp11Job::ARCHER;

	// Error: Cpp11Color does not a conversion to a type acceptable to the predefined operator
	// cpp11Color's type is Cpp11Color, cpp11Job's type is Cpp11Job.
	// if (cpp11Color == cpp11Job)
	//	std::cout << "Cpp11Color's GREEN equals Cpp11Job's ARCHER" << std::endl;

	// Error: No scoped enumeration to int conversion.
	// colorNum = cpp11Color;
	// Scoped enumeration can convert to int using "static_cast".
	colorNum = static_cast<int>(cpp11Color);
	jobNum = static_cast<int>(cpp11Job);

	Cpp98Altitude cpp98Altitude;
	cpp98Altitude = LOW;

	std::cout << "Cpp11's Altitude : " << cpp98Altitude << std::endl;

	Cpp11Altitude cpp11Altitude;
	cpp11Altitude = Cpp11Altitude::HIGH;

	std::cout << "Cpp11's Altitude : " << cpp11Altitude << std::endl;

	return 0;
}