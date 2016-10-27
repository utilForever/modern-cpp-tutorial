/*************************************************************************
> File Name: typeid.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2015/7/15
> Personal Blog: https://github.com/utilForever
************************************************************************/
#include <iostream>
#include <typeinfo>

class Animal
{
	virtual void something() { }
};

class Dog : public Animal { };
class Bird : public Animal { };

void speak(const Animal& animal)
{
	if (typeid(animal) == typeid(Dog&))
		std::cout << "Woof!" << std::endl;
	else if (typeid(animal) == typeid(Bird&))
		std::cout << "Chirp!" << std::endl;
}

int main()
{
	Dog dog;
	Bird bird;

	Animal& animal = dog;
	speak(animal);
	animal = bird;
	speak(bird);
}