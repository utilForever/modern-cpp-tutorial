/*************************************************************************
> File Name: scopedEnum.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com, utilForever@kaist.ac.kr
> Created Time: 2015/4/19
> Personal Blog: https://github.com/utilForever
************************************************************************/
#include <iostream>

enum Cpp98Color { RED, GREEN, BLUE };
enum Cpp98Job { WARRIOR, ARCHER, WIZARD };

enum class Cpp11Color { RED, GREEN, BLUE };
enum class Cpp11Job { WARRIOR, ARCHER, WIZARD };

enum Cpp98Altitude
{
	HIGH = 'h',
	LOW = 'l'
};

enum class Cpp11Altitude : char {
	HIGH = 'h',
	LOW = 'l',
};

enum UpperEnum : int16_t
{
	A,
	B,
	C
};

enum LowerEnum { D, E = 20, F = D + E + 3 };

std::ostream& operator<<(std::ostream& os, Cpp98Altitude altitude)
{
	return os << static_cast<char>(altitude);
}

std::ostream& operator<<(std::ostream& os, Cpp11Altitude altitude)
{
	return os << static_cast<char>(altitude);
}

int main(int argc, char* argv[])
{
	Cpp98Color cpp98Color = GREEN;
	Cpp98Job cpp98Job = ARCHER;

	if (cpp98Color == cpp98Job)
		std::cout << "Cpp98Color's GREEN equals Cpp98Job's ARCHER" << std::endl;

	int colorNum = cpp98Color;
	int jobNum = cpp98Job;

	Cpp11Color cpp11Color = Cpp11Color::GREEN;
	Cpp11Job cpp11Job = Cpp11Job::ARCHER;

	// if (cpp11Color == cpp11Job)
	//	std::cout << "Cpp11Color's GREEN equals Cpp11Job's ARCHER" << std::endl;

	// colorNum = cpp11Color;
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