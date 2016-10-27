/*************************************************************************
> File Name: promise.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2015/4/27
> Personal Blog: https://github.com/utilForever
> References: http://en.cppreference.com/w/cpp/thread/promise
> References: http://www.cplusplus.com/reference/future/promise/
************************************************************************/
/*
	template <class T>	promise;
	template <class R&>	promise<R&>;	// Specialization : T is a reference type (R&)
	template <>			promise<void>;	// Specialization : T is void
*/
/*
	A promise is an object that can store a value of type T to be retrieved by a future object (possibly in another thread), offering a synchronization point.
	On construction, promise objects are associated to a new shared state on which they can store either a value of type T or an exception derived from std::exception.
	This shared state can be associated to a future object by calling member get_future.
	After the call, both objects share the same shared state:
	- The promise object is the asynchronous provider and is expected to set a value for the shared state, at some point.
	- The future object is an asynchronous return object that can retrieve the value of the shared state, waiting for it to be ready, if necessary.
	The lifetime of the shared state lasts at least until the last object with which it is associated releases it or is destroyed.
	Therefore it can survive the promise object that obtained it in the first place if associated also to a future.
*/
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
	// Create promise
	std::promise<int> prom;

	// Engagement with future
	std::future<int> fut = prom.get_future();

	// Send future to new thread
	std::thread t(printInt, std::ref(fut));

	// Fulfill promise (synchronizes with getting the future)
	prom.set_value(10);

	t.join();

	return 0;
}