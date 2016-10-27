/*************************************************************************
> File Name: try_catch_throw2.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2015/7/17
> Personal Blog: https://github.com/utilForever
************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

void readFile(const std::string& fileName, std::vector<int>& dest) throw (std::invalid_argument, std::runtime_error)
{
	std::ifstream istr;
	int temp;
	istr.open(fileName.c_str());
	if (istr.fail())
		// Exception: file open error
		throw std::invalid_argument("");
	// Read each value and store it into vector
	while (istr >> temp)
		dest.push_back(temp);
	if (istr.eof())
		istr.close();
	else {
		// Exception: unknown error
		istr.close();
		throw std::runtime_error("");
	}
}

int main()
{
	std::vector<int> myInts;
	const std::string fileName = "numbers.txt";

	try
	{
		readFile(fileName, myInts);
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << "Unable to open file " << fileName << std::endl;
		return 1;
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << "Error reading file " << fileName << std::endl;
		return 1;
	}

	for (size_t i = 0; i < myInts.size(); i++)
		std::cout << myInts[i] << " ";
	std::cout << std::endl;
}