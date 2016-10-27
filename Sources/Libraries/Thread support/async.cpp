/*************************************************************************
> File Name: async.cpp
> Author: Chan-Ho Chris Ohk
> E-mail: utilForever@gmail.com
> Created Time: 2015/6/21
> Personal Blog: https://github.com/utilForever
> References: http://en.cppreference.com/w/cpp/thread/async
> References: http://www.cplusplus.com/reference/future/async/
> References: http://www.guyrutenberg.com/2014/05/03/c-mt19937-example/
************************************************************************/
/*
	(1) Unspecified policy
	template <class Fn, class... Args>
		future<typename result_of<Fn(Args...)>::type>
			async(Fn&& fn, Args&&... args);

	(2) Specified policy
	template <class Fn, class... Args>
		future<typename result_of<Fn(Args...)>::type>
			async(launch policy, Fn&& fn, Args&&... args);
*/
/*
	std::async, Call function asynchronously
	Calls fn (with args as arguments) at some point, returning without waiting for the execution of fn to complete.
	The value returned by fn can be accessed through the future object returned (by calling its member future::get).
	The second version (2) lets the caller select a specific launching policy, while the first version (1) uses automatic selection, as if calling (2) with launch::async | launch:::deferred as policy.
	The function temporarily stores in the shared state either the threading handler used or decay copies of fn and args (as a deferred function) without making it ready.
	Once the execution of fn is completed, the shared state contains the value returned by fn and is made ready.
*/
/*
	policy: A bitmask value of type launch indicating the launching policy
		- launch::async, Asynchronous
		Launches a new thread to call fn (as if a thread object is constructed with fn and args as arguments, and accessing the shared state of the returned future joins it).
		- launch::deferred, Deferred
		The call to fn is deferred until the shared state of the returned future is accessed (with wait or get).
		At that point, fn is called and the function is no longer considered deferred.
		When this call returns, the shared state of the returned future is made ready.
		- launch:async | launch:deferred, Automatic
		The function chooses the policy automatically (at some point).
		This depends on the system and library implementation, which generally optimizes for the current availability of concurrency in the system.
	Particular library implementations may support additional launching policies, with the proper label defined in type launch.
	Combining multiple values is possible, in which case, the function automatically chooses one among them.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <random>
#include <chrono>

template <typename RAIter>
int parallelSum(RAIter begin, RAIter end)
{
	// If length is less than 1000, accumulate all the values in range [begin, end) 
	auto len = end - begin;
	if (len < 1000)
		return std::accumulate(begin, end, 0);

	// Divide and Conquer in parallel
	RAIter mid = begin + len / 2;
	auto handle = std::async(std::launch::async, parallelSum<RAIter>, mid, end);
	int sum = parallelSum(begin, mid);
	return sum + handle.get();
}

int main()
{
	// Get current time using High resolution clock (C++11)
	// Count a duration with the time span between the epoch and tthe time_point (C++11)
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	// A random number generator based on Mersenne Twister algorithm (C++11)
	std::mt19937 mtRand(seed);

	// Create a vector with 10000 elements
	std::vector<int> v(10000);
	// Assign a random number (1 ~ 100)
	for (auto& value : v)
		value = mtRand() % 100 + 1;

	// Print result
	std::cout << "The sum is " << parallelSum(v.begin(), v.end()) << std::endl;

	return 0;
}