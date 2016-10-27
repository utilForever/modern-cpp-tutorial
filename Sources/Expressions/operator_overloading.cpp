/*************************************************************************
> File Name: operator_overloading.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2015/7/2
> Personal Blog: https://github.com/utilForever
> References: http://en.cppreference.com/w/cpp/language/operators
> References: http://en.cppreference.com/w/cpp/language/friend
************************************************************************/
#include <string>

using tempC = std::pair<double, double>;

class Complex
{
private:
	double real;
	double imaginary;

public:
	Complex()
		: real(0.0), imaginary(0.0) { }
	Complex(double _real, double _imaginary)
		: real(_real), imaginary(_imaginary) { }
	Complex(tempC c)
		: real(c.first), imaginary(c.second) { }

	friend const Complex operator+(const Complex& lhs, const Complex& rhs);
	friend const Complex operator-(const Complex& lhs, const Complex& rhs);
	friend const Complex operator*(const Complex& lhs, const Complex& rhs);
	friend const Complex operator/(const Complex& lhs, const Complex& rhs);

	Complex& operator+=(const Complex& rhs);
	Complex& operator-=(const Complex& rhs);
	Complex& operator*=(const Complex& rhs);
	Complex& operator/=(const Complex& rhs);

	friend bool operator==(const Complex& lhs, const Complex& rhs);
};

const Complex operator+(const Complex& lhs, const Complex& rhs)
{
	Complex addedComplex;
	addedComplex.real = lhs.real + rhs.real;
	addedComplex.imaginary = lhs.imaginary + rhs.imaginary;
	return addedComplex;
}

const Complex operator-(const Complex& lhs, const Complex& rhs)
{
	Complex subtractedComplex;
	subtractedComplex.real = lhs.real - rhs.real;
	subtractedComplex.imaginary = lhs.imaginary - rhs.imaginary;
	return subtractedComplex;
}

// (a, b)(c, d) = (ac-bd, ad+bc)
const Complex operator*(const Complex& lhs, const Complex& rhs)
{
	Complex multipliedComplex;
	multipliedComplex.real = lhs.real * rhs.real - lhs.imaginary * rhs.imaginary;
	multipliedComplex.imaginary = lhs.real * rhs.imaginary + lhs.imaginary * rhs.real;
	return multipliedComplex;
}

// If (c, d) is not equal (0, 0),
// (a, b)/(c, d) = ((ac+bd)/(c^2+d^2), (bc-ad)/(c^2+d^2))
const Complex operator/(const Complex& lhs, const Complex& rhs)
{
	if (rhs.real == 0 && rhs.imaginary == 0)
		throw std::invalid_argument("Divide by zero.");
	Complex multipliedComplex;
	multipliedComplex.real = lhs.real * rhs.real - lhs.imaginary * rhs.imaginary;
	multipliedComplex.imaginary = lhs.real * rhs.imaginary + lhs.imaginary * rhs.real;
	return multipliedComplex;
}

Complex& Complex::operator+=(const Complex& rhs)
{
	real += rhs.real;
	imaginary += rhs.imaginary;
	return *this;
}

Complex& Complex::operator-=(const Complex& rhs)
{
	real -= rhs.real;
	imaginary -= -rhs.imaginary;
	return *this;
}

Complex& Complex::operator*=(const Complex& rhs)
{
	Complex temp;
	temp.real = real * rhs.real - imaginary * rhs.imaginary;
	temp.imaginary = real * rhs.imaginary + imaginary * rhs.real;
	real = temp.real;
	imaginary = temp.imaginary;
	return *this;
}

Complex& Complex::operator/=(const Complex& rhs)
{
	if (rhs.real == 0 && rhs.imaginary == 0)
		throw std::invalid_argument("Divide by zero.");
	Complex temp;
	temp.real = real * rhs.real - imaginary * rhs.imaginary;
	temp.imaginary = real * rhs.imaginary + imaginary * rhs.real;
	real = temp.real;
	imaginary = temp.imaginary;
	return *this;
}

bool operator==(const Complex& lhs, const Complex& rhs)
{
	return ((lhs.real == rhs.real) && (lhs.imaginary == rhs.imaginary));
}

int main()
{
	Complex c1(10.0, 5.0), c2(4.0, 3.0);
	Complex c3 = c1 + c2;	// 14.0, 8.0

	Complex c4 = c3 + tempC(2.0, 4.0);	// 16.0, 12.0
	Complex c5 = tempC(2.0, 4.0) + c3;	// 16.0, 12.0

	Complex c6(3.0, 2.0), c7(8.0, 3.0);
	c7 -= c6;				// 5.0, 1.0
	c7 += tempC(5.0, 4.0);	// 10.0, 5.0

	return 0;
}