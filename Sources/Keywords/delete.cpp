/*************************************************************************
> File Name: delete_keyword.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2015/4/15
> Personal Blog: https://github.com/utilForever
************************************************************************/
class DeleteTestCpp98
{
private:
	int i;

	// Copy constructor in private access modifier
	DeleteTestCpp98(const DeleteTestCpp98&) { };

public:
	static void tempAssign(const DeleteTestCpp98& rhs)
	{
		DeleteTestCpp98 temp = rhs;
	}

	DeleteTestCpp98(int _i = 10) : i(_i) { }
};

class DeleteTestCpp11
{
private:
	int i;

public:
	static void tempAssign(const DeleteTestCpp11& rhs)
	{
		// DeleteTestCpp11 temp = rhs;
	}

	DeleteTestCpp11(int _i = 10) : i(_i) { }
	// Deleted copy constructor in public access modifier
	DeleteTestCpp11(const DeleteTestCpp11&) = delete;
};

int main(int argc, char* argv [])
{
	// In C++98, declaring "tempAssign" functions private prevents clients from calling them.
	// If code that still has access to them uses them, linking will fail due to missing function definitions.
	DeleteTestCpp98 dtc98;
	DeleteTestCpp98::tempAssign(dtc98);

	// In C++11, deleted function will fail to compile if it tries to copy DeleteTestCpp11 objects.
	// That's an improvement over the C++98 behavior, where such improper usage wouldn't be diagnosed until link-time.
	DeleteTestCpp11 dtc11;
	DeleteTestCpp11::tempAssign(dtc11);
}