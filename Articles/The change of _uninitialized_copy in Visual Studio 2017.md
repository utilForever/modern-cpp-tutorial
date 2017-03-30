# Visual Studio 2017에서 변경된 _uninitialized_copy 함수

- 작성자 : Chan-Ho Chris Ohk (utilForever@gmail.com)

## 발단

어떤 분이 Visual C++ STL 관련 질문을 해오셨다.
책에 있는 코드가 Visual C++ 2015에서는 잘 실행되는데, Visual C++ 2017에서는 컴파일이 되지 않는다는 것이었다.
그래서 나는 먼저 코드를 살펴보기로 했다. 코드는 다음과 같았다.

### Numeric_Range.h
```C++
// Numeric_Range.h for Ex2_07
// 범위를 위한 클래스 템플릿과 범위 지정을 위한 반복자 클래스 템플릿을 정의
#ifndef NUMERIC_RANGE_H
#define NUMERIC_RANGE_H

#include <exception>                             // 표준 익셉션 타입
#include <iterator>                              // 반복자 타입
#include <type_traits>                           // 컴파일 타임 타입 체킹

template <typename T> class Numeric_Iterator;    // 템플릿 타입 정의

// 숫자 범위를 정의
template<typename T>
class Numeric_Range
{
	static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value,
		"Numeric_Range type argument must be numeric.");

	friend class Numeric_Iterator <T>;

private:
	T start;                                       // 범위에서 첫 번째 값
	T step;                                        // 연속 값의 증가값
	size_t count;                                  // 범위에 있는 값의 개수

public:
	explicit Numeric_Range(T first = 0, T incr = 1, size_t n = 2) : start{ first }, step{ incr }, count{ n } {}

	// 범위에 대한 시작 반복자를 반환
	Numeric_Iterator<T> begin() { return Numeric_Iterator<T>(*this); }

	// 범위에 대한 끝 반복자를 반환
	Numeric_Iterator<T> end()
	{
		Numeric_Iterator<T> end_iter(*this);
		end_iter.value = start + count*step;          // 끝 반복자 값은 마지막에서 하나 더 지나간 값
		return end_iter;
	}
};

// 반복자 클래스 템플릿 - 순방향 반복자
template<typename T>
class Numeric_Iterator : public std::iterator <std::forward_iterator_tag, T>
{
	friend class Numeric_Range <T>;

private:
	Numeric_Range<T>& range;                       // 이 반복자 범위에 대한 참조
	T value;                                       // 참조가 가리키는 값

public:
	explicit Numeric_Iterator(Numeric_Range<T>& a_range) : range{ a_range }, value{ a_range.start } {};

	// 할당 연산자
	Numeric_Iterator& operator=(const Numeric_Iterator& src)
	{
		range = src.range;
		value = src.value;
	}

	// 반복자를 역참조한다
	T& operator*()
	{
		// 값이 마지막에서 하나 더 뒤라면 이 값은 끝 반복자다
		if (value == static_cast<T>(range.start + range.count*range.step))
		{
			throw std::logic_error("Cannot dereference an end iterator.");
		}
		return value;
	}

	// 전치 증가 연산자
	Numeric_Iterator& operator++()
	{
		// 값이 마지막에서 하나 더 뒤라면 이 값은 끝 반복자다
		if (value == static_cast<T>(range.start + range.count*range.step))
		{
			throw std::logic_error("Cannot increment an end iterator.");
		}
		value += range.step;                         // 범위 스텝만큼 값을 증가
		return *this;
	}

	// 후치 증가 연산자
	Numeric_Iterator operator++(int)
	{
		// 값이 마지막에서 하나 더 뒤라면 이 값은 끝 반복자다
		if (value == static_cast<T>(range.start + range.count*range.step))
		{
			throw std::logic_error("Cannot increment an end iterator.");
		}
		auto temp = *this;
		value += range.step;                         // 범위 스텝만큼 값을 증가
		return temp;                                 // 증가되기 전의 반복자
	}

	// 비교
	bool operator<(const Numeric_Iterator& iter) const { return value < iter.value; }
	bool operator==(const Numeric_Iterator& iter) const { return value == iter.value; }
	bool operator!=(const Numeric_Iterator& iter) const { return value != iter.value; }
	bool operator>(const Numeric_Iterator& iter) const { return value > iter.value; }
	bool operator<=(const Numeric_Iterator& iter) const { *this < iter || *this == iter; }
	bool operator>=(const Numeric_Iterator& iter) const { *this > iter || *this == iter; }
};
#endif
```

### Ex2_07.cpp
```C++
// Ex2_07.cpp
// Numeric_Range 템플릿 사용해보기
#include <algorithm>                         // copy()
#include <numeric>                           // accumulate()
#include <iostream>                          // 표준 스트림
#include <vector>                            // 벡터 컨테이너
#include "Numeric_Range.h"                   // Numeric_Range<T> & Numeric_Iterator<T>

int main()
{
  Numeric_Range<double> range {1.5, 0.5, 5};
  auto first = range.begin();
  auto last = range.end();
  std::copy(first, last, std::ostream_iterator<double>(std::cout, "  "));
  std::cout << "\nSum = " << std::accumulate(std::begin(range), std::end(range), 0.0) << std::endl;

  // Numeric_Range에서 컨테이너를 초기화
  Numeric_Range<long> numbers {15L, 4L, 10};
  std::vector<long> data {std::begin(numbers), std::end(numbers)};
  std::cout << "\nValues in vector are:\n";
  std::copy(std::begin(data), std::end(data), std::ostream_iterator<long>(std::cout, "  "));
  std::cout << std::endl;

  // 범위에 있는 값을 출력하기
  std::cout << "\nThe values in the numbers range are:\n";
  for (auto n : numbers)
    std::cout << n << " ";
  std::cout << std::endl;
}
```

사용자 정의 반복자를 구현한 코드였는데, 언뜻 보기에 큰 문제는 없어보였다.
그래서 Visual Studio 2017에서 위 코드를 컴파일해 보았다.
그랬더니, 다음과 같은 컴파일 오류가 발생했다.

```C++
1>------ Build started: Project: Test, Configuration: Debug Win32 ------
1>Ex2_07.cpp
1>c:\program files (x86)\microsoft visual studio\2017\enterprise\vc\tools\msvc\14.10.25017\include\xmemory(126): error C2678: binary '*': no operator found which takes a left-hand operand of type 'const Numeric_Iterator<T>' (or there is no acceptable conversion)
1>        with
1>        [
1>            T=long
1>        ]
1>c:\users\utilforever\documents\visual studio 2017\projects\test\test\numeric_range.h(62): note: could be 'long &Numeric_Iterator<T>::operator *(void)'
1>        with
1>        [
1>            T=long
1>        ]
1>c:\program files (x86)\microsoft visual studio\2017\enterprise\vc\tools\msvc\14.10.25017\include\xmemory(126): note: while trying to match the argument list '(const Numeric_Iterator<T>)'
1>        with
1>        [
1>            T=long
1>        ]
1>c:\program files (x86)\microsoft visual studio\2017\enterprise\vc\tools\msvc\14.10.25017\include\vector(1859): note: see reference to function template instantiation '_FwdIt *std::_Uninitialized_copy<_Iter,long*,std::allocator<_Ty>>(_InIt,_InIt,_FwdIt,std::_Wrap_alloc<std::allocator<_Ty>> &)' being compiled
1>        with
1>        [
1>            _FwdIt=long *,
1>            _Iter=Numeric_Iterator<long>,
1>            _Ty=long,
1>            _InIt=Numeric_Iterator<long>
1>        ]
1>c:\program files (x86)\microsoft visual studio\2017\enterprise\vc\tools\msvc\14.10.25017\include\vector(779): note: see reference to function template instantiation 'long *std::vector<long,std::allocator<_Ty>>::_Ucopy<_Iter>(_Iter,_Iter,long *)' being compiled
1>        with
1>        [
1>            _Ty=long,
1>            _Iter=Numeric_Iterator<long>
1>        ]
1>c:\program files (x86)\microsoft visual studio\2017\enterprise\vc\tools\msvc\14.10.25017\include\vector(779): note: see reference to function template instantiation 'long *std::vector<long,std::allocator<_Ty>>::_Ucopy<_Iter>(_Iter,_Iter,long *)' being compiled
1>        with
1>        [
1>            _Ty=long,
1>            _Iter=Numeric_Iterator<long>
1>        ]
1>c:\program files (x86)\microsoft visual studio\2017\enterprise\vc\tools\msvc\14.10.25017\include\vector(794): note: see reference to function template instantiation 'void std::vector<long,std::allocator<_Ty>>::_Range_construct_or_tidy<_Iter>(_Iter,_Iter,std::forward_iterator_tag)' being compiled
1>        with
1>        [
1>            _Ty=long,
1>            _Iter=Numeric_Iterator<long>
1>        ]
1>c:\program files (x86)\microsoft visual studio\2017\enterprise\vc\tools\msvc\14.10.25017\include\vector(794): note: see reference to function template instantiation 'void std::vector<long,std::allocator<_Ty>>::_Range_construct_or_tidy<_Iter>(_Iter,_Iter,std::forward_iterator_tag)' being compiled
1>        with
1>        [
1>            _Ty=long,
1>            _Iter=Numeric_Iterator<long>
1>        ]
1>c:\users\utilforever\documents\visual studio 2017\projects\test\test\ex2_07.cpp(19): note: see reference to function template instantiation 'std::vector<long,std::allocator<_Ty>>::vector<Numeric_Iterator<T>,void>(_Iter,_Iter,const std::allocator<_Ty> &)' being compiled
1>        with
1>        [
1>            _Ty=long,
1>            T=long,
1>            _Iter=Numeric_Iterator<long>
1>        ]
1>c:\users\utilforever\documents\visual studio 2017\projects\test\test\ex2_07.cpp(19): note: see reference to function template instantiation 'std::vector<long,std::allocator<_Ty>>::vector<Numeric_Iterator<T>,void>(_Iter,_Iter,const std::allocator<_Ty> &)' being compiled
1>        with
1>        [
1>            _Ty=long,
1>            T=long,
1>            _Iter=Numeric_Iterator<long>
1>        ]
1>c:\program files (x86)\microsoft visual studio\2017\enterprise\vc\tools\msvc\14.10.25017\include\xmemory(126): error C2100: illegal indirection
1>c:\program files (x86)\microsoft visual studio\2017\enterprise\vc\tools\msvc\14.10.25017\include\xmemory(126): error C2062: type 'unknown-type' unexpected
1>Done building project "Test.vcxproj" -- FAILED.
========== Build: 0 succeeded, 1 failed, 0 up-to-date, 0 skipped ==========
```

무슨 문제가 있는 것일까?

## 원인 분석

오류가 발생하는 원인을 분석하기 위해, 오류 메시지를 토대로 하나씩 추적했다. 중간까지는 별다른 문제가 없어보였다. 그러다가 다음 메시지를 보게되었다.

```C++
1>c:\program files (x86)\microsoft visual studio\2017\enterprise\vc\tools\msvc\14.10.25017\include\xmemory(126): note: while trying to match the argument list '(const Numeric_Iterator<T>)'
1>        with
1>        [
1>            T=long
1>        ]
1>c:\program files (x86)\microsoft visual studio\2017\enterprise\vc\tools\msvc\14.10.25017\include\vector(1859): note: see reference to function template instantiation '_FwdIt *std::_Uninitialized_copy<_Iter,long*,std::allocator<_Ty>>(_InIt,_InIt,_FwdIt,std::_Wrap_alloc<std::allocator<_Ty>> &)' being compiled
1>        with
1>        [
1>            _FwdIt=long *,
1>            _Iter=Numeric_Iterator<long>,
1>            _Ty=long,
1>            _InIt=Numeric_Iterator<long>
1>        ]
```

그래서 Visual Studio 2017의 ```_Uninitialized_copy``` 함수가 어떻게 구현되어 있는지 살펴봤다.

```C++
template<class _InIt,
	class _FwdIt,
	class _Alloc> inline
	_FwdIt _Uninitialized_copy(_InIt _First, _InIt _Last, _FwdIt _Dest,
		_Wrap_alloc<_Alloc>& _Al)
	{	// copy [_First, _Last) to raw _Dest, using _Al
		// note: only called internally from elsewhere in the STL, debug checks
		// and deprecation warnings omitted
	const auto _UFirst = _Unchecked(_First);
	const auto _ULast = _Unchecked(_Last);
	const auto _UDest = _Unchecked(_Dest);
	return (_Rechecked(_Dest,
		_Uninitialized_copy_al_unchecked(_UFirst, _ULast, _UDest, _Al,
			_Ptr_copy_cat(_UFirst, _UDest),
			_Uses_default_construct_t<_Alloc, decltype(_Unfancy(_UDest)), decltype(*_UFirst)>())));
	}
```

그렇다면 Visual Studio 2015에서는 어떻게 구현되어 있을까?

```C++
template<class _InIt,
	class _FwdIt,
	class _Alloc> inline
	_FwdIt _Uninitialized_copy(_InIt _First, _InIt _Last, _FwdIt _Dest,
		_Wrap_alloc<_Alloc>& _Al)
	{	// copy [_First, _Last) to raw _Dest, using _Al
		// note: only called internally from elsewhere in the STL, debug checks
		// and deprecation warnings omitted
	return (_Rechecked(_Dest,
		_Uninitialized_copy_al_unchecked(_Unchecked(_First), _Unchecked(_Last),
			_Unchecked(_Dest), _Al)));
	}
```

내부 구현이 바뀌었다는 사실을 알 수 있었다.
기존에는 인자 ```_First```, ```_Last```, ```_Dest```를 그대로 사용했지만,
Visual Studio 2017에서 이 인자들을 ```const auto``` 타입으로 바꿔서 사용하도록 변경되었다.
이로 인해 컴파일 오류가 발생하게 된 것이다.

### 해결 방법

그렇다면 어떻게 이 오류를 해결할 수 있을까?
해결 방법은 간단하다.
반복자를 역참조하는 연산자 ```operator*()```를 아래처럼 수정하면 된다.

```C++
// 반복자를 역참조한다
const T& operator*() const
{
	// 값이 마지막에서 하나 더 뒤라면 이 값은 끝 반복자다
	if (value == static_cast<T>(range.start + range.count*range.step))
	{
		throw std::logic_error("Cannot dereference an end iterator.");
	}
	return value;
}
```

수정한 후, 컴파일하면 정상적으로 컴파일되고 출력 결과가 나온다.

```
1.5  2  2.5  3  3.5
Sum = 12.5

Values in vector are:
15  19  23  27  31  35  39  43  47  51

The values in the numbers range are:
15 19 23 27 31 35 39 43 47 51
Press any key to continue . . .
```

Visual Studio 2015, 2017 및 g++-6에서 정상 실행을 확인했다.

### 결론

Visual Studio의 버전을 업그레이드하면서 STL의 내부 구현에 변화가 있을 수 있다.
따라서 기존 Visual Studio에서 잘 실행되던 코드가 새로운 Visual Studio에서 실행되지 않는다면,
어떤 부분에서 오류가 발생하는지 확인하고 오류 메시지를 토대로 추적한 후,
C++ 표준의 변화가 원인이 아니라면  STL 내부 구현에 변화가 없는지 살펴봐야 할 것이다.