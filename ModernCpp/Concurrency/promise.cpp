/*************************************************************************
> File Name: promise.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com, utilForever@kaist.ac.kr
> Created Time: 2015/4/27
> Personal Blog: https://github.com/utilForever
> References: http://en.cppreference.com/w/cpp/thread/promise
> References: http://www.cplusplus.com/reference/future/promise/
************************************************************************/
#include <iostream>
#include <thread>
#include <future>


void printInt(std::future<int>& fut)
{
	int x = fut.get();
	std::cout << "Value : " << x << std::endl;
}

int main(int argc, char* argv[])
{
	std::promise<int> prom;

	std::future<int> fut = prom.get_future();

	std::thread t(printInt, std::ref(fut));

	prom.set_value(10);

	t.join();

	return 0;
}