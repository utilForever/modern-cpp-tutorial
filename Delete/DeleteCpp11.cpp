class DeleteTestCpp11
{
public:
	static void tempAssign(const DeleteTestCpp11& rhs)
	{
		DeleteTestCpp11 temp = rhs;
	}

	DeleteTestCpp11(int _i = 10) : i(_i) { }
	DeleteTestCpp11(const DeleteTestCpp11&) = delete;

private:
	int i;
};

int main(int argc, char* argv [])
{
	// In C++11, deleted function will fail to compile if it tries to copy DeleteTestCpp11 objects.
	// That's an improvement over the C++98 behavior, where such improper usage wouldn't be diagnosed until link-time.
	DeleteTestCpp11 dtc11;
	DeleteTestCpp11::tempAssign(dtc11);
}