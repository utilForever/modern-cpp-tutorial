/*************************************************************************
> File Name: RAII-rule_of_five.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2015/4/26
> Personal Blog: https://github.com/utilForever
> References: http://www.cppsamples.com/common-tasks/rule-of-five.html
************************************************************************/
// Safely and efficiently implement RAII to encapsulate the management of dynamically allocated resources.
// RAII = Resource Allocation is Initialization.
class Resource
{
private:
	int x = 0;
};

// In C++98, the rule of three specifies that if a class implements any of the following functions,
// it should implement all of them: copy constructor, copy assignment operator, destructor.
// These functions are usually required only when a class is manually managing a dynamically allocated resource,
// and so all of them must be implemented to manage the resource safely.
class RO3
{
private:
	Resource* pResource;

public:
	// Dynamically allocates a Resource object in its constructor.
	RO3()
		: pResource{ new Resource{} }
	{ }

	// The implementations of RO3's copy constructor, copy assignment operator, and destructor ensure that
	// the lifetime of this resource is safely managed by RO3 object that contains it, even in the event of an exception.
	// Copy constructor
	RO3(const RO3& rhs)
		: pResource{ new Resource(*(rhs.pResource)) }
	{ }

	// Copy assignment operator
	RO3& operator=(const RO3& rhs)
	{
		if (&rhs != this)
		{
			delete pResource;
			pResource = nullptr;
			pResource = new Resource(*(rhs.pResource));
		}

		return *this;
	}

	// Destructor
	~RO3()
	{
		delete pResource;
	}
};

// In C++11, the rule of five identifies that it usually appropriate to also provide the following functions
// to allow for optimized from temporary objects: move constructor, move assignment operator.
class RO5
{
private:
	Resource* pResource;

public:
	RO5()
		: pResource{ new Resource{} }
	{ }

	RO5(const RO5& rhs)
		: pResource{ new Resource(*(rhs.pResource)) }
	{ }

	// We have also implemented a move constructor and move assignment operator that provide
	// optimized copies from temporary objects.
	// Rather than copy the resource, they take the resource from the original RO5 and
	// set its internal pointer to nullptr, effectively stealing the resource.
	RO5(RO5&& rhs)
		: pResource{ rhs.pResource }
	{
		rhs.pResource = nullptr;
	}

	// Note: The copy and move assignment operators in this example provide only basic exception safety.
	// They may alternatively be implemented with the copy-and-swap idiom (copyAndSwap.cpp),
	// which provides strong exception safety at an optimization cost.
	RO5& operator=(const RO5& rhs)
	{
		if (&rhs != this)
		{
			delete pResource;
			pResource = nullptr;
			pResource = new Resource(*(rhs.pResource));
		}

		return *this;
	}

	RO5& operator=(RO5&& rhs)
	{
		if (&rhs != this)
		{
			delete pResource;
			pResource = rhs.pResource;
			rhs.pResource = nullptr;
		}

		return *this;
	}

	~RO5()
	{
		delete pResource;
	}
};

// Note: We can typically avoid manual memory management and having to write
// the copy constructor, assignment operator, and destructor entirely by using the rule of zero (ruleOfZero.cpp).
int main(int argc, char* argv[])
{
	RO3 ro3;
	RO5 ro5;

	return 0;
}