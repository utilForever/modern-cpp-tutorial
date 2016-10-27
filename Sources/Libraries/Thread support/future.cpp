/*************************************************************************
> File Name: future.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2015/6/20
> Personal Blog: https://github.com/utilForever
> References: http://en.cppreference.com/w/cpp/thread/future
> References: http://www.cplusplus.com/reference/future/future/
************************************************************************/
/*
	template <class T>	future;
	template <class R&>	future<R&>;		// Specialization : T is reference type (R&)
	template <>			future<void>;	// Specialization : T is void
*/
/*
	A future is an object that can retrieve a value from some provider object or function, properly synchronizing this access if in different threads.
	"Valid" futures are future objects associated to a shared state, and are constructed by calling one of the following functions.
	- async
	- promise::get_future
	- packaged_task::get_future
	future objects are only useful when they are valid.
	Default-constructed future objects are not valid (unless move-assigned a valid future).
	Calling future::get on a valid future blocks the thread until the provider makes the shared state ready (either by setting a value or an exception to it). This way, two threads can be synchronized by one waiting for the other to set a value.
	The lifetime of the shared state lasts at least until the last object with which it is associated releases it or is destroyed. Therefore, if associated to a future, the shared state can survive the object from which it was obtained in the first place (if any).
*/
#include <iostream>
#include <future>
#include <chrono>

// A non-optimized way of checking for prime numbers
bool isPrime(int x)
{
	for (int i = 2; i < x; ++i)
		if (x % i == 0) return false;
	return true;
}

int main()
{
	// Call function asynchronously
	std::future<bool> fut = std::async(isPrime, 2'100'000'011);

	// Do something while waiting for function to set future
	std::cout << "Checking, please wait!";
	std::chrono::milliseconds span(100);
	while (fut.wait_for(span) == std::future_status::timeout)
		std::cout << '.' << std::flush;

	// Retrieve return value
	bool x = fut.get();

	std::cout << "\n2'100'000'011 " << (x ? "is" : "is not") << " prime." << std::endl;

	return 0;
}