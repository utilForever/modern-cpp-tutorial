#include <iostream>

class DeleteTestCpp98
{
public:
	static void tempAssign(const DeleteTestCpp98& rhs)
	{
		DeleteTestCpp98 temp = rhs;
	}

	DeleteTestCpp98(int _i = 10) : i(_i) { }

private:
	int i;

	DeleteTestCpp98(const DeleteTestCpp98&);
};

int main(int argc, char* argv [])
{
	// In C++98, declaring "tempAssign" functions private prevents clients from calling them.
	// If code that still has access to them uses them, linking will fail due to missing function definitions.
	DeleteTestCpp98 dtc98;
	DeleteTestCpp98::tempAssign(dtc98);
}