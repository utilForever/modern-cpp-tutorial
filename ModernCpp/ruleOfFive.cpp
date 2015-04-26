/*************************************************************************
> File Name: ruleOfFive.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com, utilForever@kaist.ac.kr
> Created Time: 2015/4/26
> Personal Blog: https://github.com/utilForever
************************************************************************/
#include <utility>

class Resource
{
private:
	int x = 0;
};

class RO3
{
private:
	Resource* pResource;
};

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

	RO5(RO5&& rhs)
		: pResource{ rhs.pResource }
	{
		rhs.pResource = nullptr;
	}

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