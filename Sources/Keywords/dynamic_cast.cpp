/*************************************************************************
> File Name: dynamic_cast.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2015/7/15
> Updated Time: 2016/10/29
> Personal Blog: https://github.com/utilForever
> References: http://prostars.net/55
> References: http://en.cppreference.com/w/cpp/language/dynamic_cast
************************************************************************/
#include <iostream>

struct Animal
{
	virtual ~Animal()
	{

	}

	// Must be polymorphic to use runtime-checked dynamic_cast
	virtual void Identify()
	{
		std::cout << "Animal" << std::endl;
	};
};

struct Dog : Animal
{
	void Identify() override
	{
		std::cout << "Dog" << std::endl;
	}
};

struct Bird : Animal
{
	Bird(Animal* a, Dog* d) {
		// Casts during construction (see the call in the constructor of DogBird(mutant?) below)
		dynamic_cast<Bird*>(a); // well-defined: a of type Animal*, Animal base of Bird, results in Bird*
		dynamic_cast<Bird*>(d); // undefined behavior: d has type Dog*, Dog not a base of Bird
	}

	void Identify() override
	{
		std::cout << "Bird" << std::endl;
	}
};

struct DogBird : Dog, Bird
{
	DogBird() : Bird(static_cast<Dog*>(this), this)
	{
		
	}
};

struct Base
{
	virtual ~Base()
	{
		
	}
};

struct Derived : Base
{
	virtual void Name()
	{
		std::cout << "My name is Derived!" << std::endl;
	}
};

int main()
{
	// dynamic_cast safely converts pointers and references to classes up, down,
	// and sideways along the inheritance hierarchy.
	// The most derived object (Animal, Dog, Bird)
	DogBird db;
	// db.Identify() is ambiguous call (What is function to call? Dog::Identify()? Bird::Identify()?)
	// db.Identify();
	// Upcast, dynamic_cast may be used, but unnecessary
	Dog& d = db;
	// Prints "Dog"
	d.Identify();
	// Downcast
	DogBird& newDB = dynamic_cast<DogBird&>(d);
	// newDB's type is DogBird.
	// So, newDB.Identify() is ambiguous call (What is function to call? Dog::Identify()? Bird::Identify()?)
	// newDB.Identify();
	// Sidecast
	Bird& newB = dynamic_cast<Bird&>(d);
	// Prints "Bird"
	newB.Identify();
	std::cout << std::endl;

	Base* b1 = new Base;
	// b1 has type Base*, Base not a base of Base.
	// So dynamic_cast fails, and returns nullptr.
	if (Derived* d1 = dynamic_cast<Derived*>(b1))
	{
		std::cout << "Downcast from b1 to d1 successful\n";
		d1->Name();
	}

	Base* b2 = new Derived;
	// b2 has type Derived*, Derived base of Base.
	// So dynamic_cast successes, and returns Derived*.
	if (Derived* d2 = dynamic_cast<Derived*>(b2))
	{
		std::cout << "Downcast from b2 to d2 successful\n";
		d2->Name();
	}

	delete b1;
	delete b2;
}