/*************************************************************************
> File Name: polymorphism.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2015/7/2
> Personal Blog: https://github.com/utilForever
************************************************************************/
#include <iostream>

class Shape
{
protected:
	std::string name;
	int width;
	int height;

public:
	Shape(std::string _name, int _width, int _height)
		: name(std::move(_name)), width(_width), height(_height) { }
	void printArea() { std::cout << "The area of " << name.c_str() << " is " << getArea() << std::endl; }
	virtual double getArea() = 0;
};

class Circle : public Shape
{
protected:
	const double PI = 3.14;
public:
	Circle(std::string _name, int _width, int _height)
		: Shape(std::move(_name), _width, _height) { }
	virtual double getArea() { return PI * std::pow(width * 0.5, 2); };
};

class Rect : public Shape
{
public:
	Rect(std::string _name, int _width, int _height)
		: Shape(std::move(_name), _width, _height) { }
	virtual double getArea() { return width * height; };
};

class Triangle : public Shape
{
public:
	Triangle(std::string _name, int _width, int _height)
		: Shape(std::move(_name), _width, _height) { }
	virtual double getArea() { return width * height * 0.5; };
};

int main()
{
	Shape* s = new Circle("Circle", 5, 5);
	s->printArea();

	s = new Circle("Circle", 5, 5);
	s->printArea();

	s = new Rect("Rectangle", 5, 5);
	s->printArea();

	s = new Triangle("Triangle", 5, 5);
	s->printArea();

	return 0;
}