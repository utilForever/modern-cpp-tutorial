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

