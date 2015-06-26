# C++의 4가지 다형성 (The Four Polymorphisms in C++)

- 원본 링크 : http://www.catonmat.net/blog/cpp-polymorphism/
- 원본 작성자 : Peteris Krumins (peter@catonmat.net)
- 번역 작성자 : Chan-Ho Chris Ohk (utilForever@gmail.com, utilForever@kaist.ac.kr)

사람들이 주로 이야기하는 C++의 다형성이란 Base 클래스의 포인터 또는 참조형을 통해 Derived 클래스를 사용하는 것을 의미하는 경우가 많은데, 이를 서브 타입 다형성(Subtype Polymorphism)이라고 부른다. 그러나 매개 변수 다형성(Parametric Polymorphism), 임시 다형성(Ad-hoc Polymorphism), 강제 다형성(Coercion Polymorphism)과 같이 C++에 존재하는 다른 모든 종류의 다형성들을 잊어버리는 경우가 많다.
이러한 다형성들은 C++에서 다른 이름으로 알려져 있다.

- 서브타입 다형성은 **런타임 다형성(Runtime Polymorphism)**으로 알려져 있다.
- 매개 변수 다형성은 **컴파일 타임 다형성(Compile-Time Polymorphism)**으로 알려져 있다.
- 임시 다형성은 **오버로딩(Overloading)**으로 알려져 있다.
- 강제 다형성은 (암시적 또는 명시적) **캐스팅(Casting)**으로 알려져 있다.

이 문서에서는 C++ 언어를 사용한 예제들을 통해 모든 다형성을 설명하고 각자 다른 이름을 가지게 된 이유에 대한 통찰력을 제공한다.

## 서브타입 다형성 (런타임 다형성)

서브타입 다형성은 C++에서 "다형성"을 이야기할 때 모든 사람들이 이해하고 있는 의미의 다형성이다. Base 클래스의 포인터 또는 참조형을 통해 Derived 클래스를 사용하는 기능을 말한다.
여기에 예제가 있다. 고양이과에 속하는 다양한 종류의 고양이들을 가지고 있다고 가정해 보자.

![고양이과에 속하는 다양한 종류의 고양이들 (James Halliday 제공)](http://www.catonmat.net/images/polymorphic-cats.gif)

모두 생물학적으로 고양이과에 속하고 "야옹"이라고 할 수 있기 때문에, *Felid*라는 Base 클래스로부터 상속을 받고 *meow*라는 순수 가상 함수를 오버라이딩하는 클래스들로 나타낼 수 있다.
    
	// file cats.h

    class Felid {
        public:
            virtual void meow() = 0;
    };

    class Cat : public Felid {
    public:
        void meow() { std::cout << "Meowing like a regular cat! meow!\n"; }
    };

    class Tiger : public Felid {
    public:
        void meow() { std::cout << "Meowing like a tiger! MREOWWW!\n"; }
    };

    class Ocelot : public Felid {
    public:
        void meow() { std::cout << "Meowing like an ocelot! mews!\n"; }
    };
	
이제 메인 프로그램에서 *Felid* (Base 클래스) 포인터를 통해 *Cat*, *Tiger*, *Ocelot*를 번갈아 가며 사용할 수 있다.

    #include <iostream>
    #include "cats.h"

    void do_meowing(Felid *cat) {
        cat->meow();
    }

    int main() {
        Cat cat;
        Tiger tiger;
        Ocelot ocelot;

        do_meowing(&cat);
        do_meowing(&tiger);
        do_meowing(&ocelot);
    }

메인 프로그램은 Cat, Tiger, Ocelet을 가리키는 포인터를 do_meowing 함수로 전달한다. 전달되는 포인터들은 모두 Felid이기 때문에, 프로그램은 객체마다 올바른 meow 함수를 호출하며 출력 결과는 다음과 같다.

    Meowing like a regular cat! meow!
    Meowing like a tiger! MREOWWW!
    Meowing like an ocelot! mews!

서브타입 다형성은 런타임 다형성이라고 부르기도 한다. 다형성 함수의 호출 결정은 런타임에 가상 테이블을 통한 간접 참조를 통해 일어난다. 좀 더 쉽게 설명하자면, 컴파일러가 컴파일 타임 때 호출될 함수의 주소를 찾는 것이 아니라 프로그램을 실행할 때 가상 테이블에 있는 오른쪽 포인터를 역참조해 함수를 호출하는 것이다.

타입 이론에서는 서브타입 다형성을 포함 다형성(Inclusion Polymorphism)이라고도 부른다.

## 매개 변수 다형성 (컴파일 타임 다형성)

매개 변수 다형성은 어떤 타입에 대해 동일한 코드를 실행하기 위한 수단을 제공한다. C++에서 매개 변수 다형성은 템플릿을 통해 구현할 수 있다.

가장 간단한 예제 중 하나는 두 개의 인수 중에서 큰 값을 찾는 일반화된 *max* 함수다.

    #include <iostream>
    #include <string>

    template <class T>
    T max(T a, T b) {
        return a > b ? a : b;
    }

    int main() {
        std::cout << ::max(9, 5) << std::endl;     // 9

        std::string foo("foo"), bar("bar");
        std::cout << ::max(foo, bar) << std::endl; // "foo"
    }

*max* 함수는 타입 *T*에 대해 다양한 형태가 될 수 있다. 하지만, 포인터를 통한 비교는 내용이 아닌 메모리 위치를 비교하기 때문에 포인터 타입에 대해서는 동작하지 않는다. 포인터 타입에 대해서 동작하게 만들고 싶다면 포인터 타입에 대해 템플릿 특수화해야 되는데, 그렇게 되면 더 이상 매개 변수 다형성이 아닌 임시 다형성이 될 것이다.

매개 변수 다형성은 컴파일 타임에 일어나기 때문에, 컴파일 타임 다형성이라고도 부른다.

## 임시 다형성 (오버로딩)

임시 다형성은 같은 이름을 가진 함수가 각 타입에 따라 다르게 행동할 수 있도록 해준다. 예를 들어, *int* 타입의 변수 2개와 *+* 연산자가 주어졌다면, 두 변수를 더한다. 반면, *std::string* 타입의 변수 2개와 *+* 연산자가 주어졌다면, 두 변수를 연결하게 된다. 이를 오버로딩이라고도 부른다.

*int*와 *std::string*에 대해 *add* 함수를 구현한 구체적인 예제가 있다.

    #include <iostream>
    #include <string>

    int add(int a, int b) {
        return a + b;
    }

    std::string add(const char *a, const char *b) {
        std::string result(a);
        result += b;
        return result;
    }

    int main() {
        std::cout << add(5, 9) << std::endl;
        std::cout << add("hello ", "world") << std::endl;
    }

C++에서 임시 다형성은 템플릿 특수화를 할 때도 나타난다. *max* 함수를 다룬 예제로 돌아가, *char* 포인터 타입의 변수 2개에 대한 *max* 함수를 작성하는 방법을 살펴보자.

    template <>
    const char *max(const char *a, const char *b) {
        return strcmp(a, b) > 0 ? a : b;
    }

이제 두 문자열 "foo"와 "bar" 중 큰 값을 찾기 위해 *::max("foo", "bar")*를 호출할 수 있다.

## 강제 다형성 (캐스팅)

강제 다형성은 객체 또는 기본 타입이 다른 객체 또는 기본 타입으로 변환할 때 일어난다. 예를 들어,

    float b = 6; // int는 (암시적으로) float으로 승격된다.
    int a = 9.99 // float은 (암시적으로) int로 강등된다.
	
명시적 캐스팅은 *(unsigned int**)*나 *(int)*와 같이 C 스타일의 타입 캐스팅 표현식을 사용하거나 C++의 *static_cast*, *const_cast*, *reinterpret_cast*, *dynamic_cast*를 사용할 때 일어난다.

또한 강제 다형성은 클래스의 생성자가 *explicit*로 선언되어 있지 않을 때에도 일어나는데, 예를 들어,

    #include <iostream>

    class A {
        int foo;
    public:
        A(int ffoo) : foo(ffoo) {}
        void giggidy() { std::cout << foo << std::endl; }
    };

    void moo(A a) {
        a.giggidy();
    }

    int main() {
        moo(55);     // 55를 출력 
    }
	
만약 A의 생성자를 *explicit*로 선언했다면, 위 예제는 더 이상 실행이 되지 않는다. 변환과 관련된 실수를 피하기 위해서는 생성자를 *explicit*로 선언하는 것이 좋다.

또한 클래스에 타입 T에 대한 변환 연산자를 정의하는 경우, T 타입을 알 수 있는 곳이라면 어디든 사용할 수 있다.

예를 들어,

    class CrazyInt {
        int v;
    public:
        CrazyInt(int i) : v(i) {}
        operator int() const { return v; } // CrazyInt에서 int로 변환
    };
	
*CrazyInt*는 *int* 타입에 대한 변환 연산자를 정의했다. 이제 *int*를 인수로 받는 *print_int* 함수가 있다면, *CrazyInt* 타입의 객체도 전달할 수 있게 된다.

    #include <iostream>

    void print_int(int a) {
        std::cout << a << std::endl;
    }

    int main() {
        CrazyInt b = 55;
        print_int(999);    // 999를 출력
        print_int(b);      // 55를 출력
    }
	
실제로 앞에서 설명한 서브타입 다형성은 Derived 클래스를 Base 클래스 타입으로 변환하기 때문에 강제 다형성이기도 하다.

## 즐거운 시간 보내시길!

다형성에 대한 새로운 지식들과 함께 즐거운 시간 보내시길!