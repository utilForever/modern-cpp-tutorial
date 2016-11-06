<img src="https://github.com/utilForever/ModernCpp/blob/master/Logo.png" align="right" width="144" height="144" />

# Modern C++

A curated list of Modern C++ articles, examples, tutorials, frameworks, libraries, and shiny things.

## Notice

Thanks for your stars! I'll do my best.

## Articles

### English → Korean

[The Four Polymorphisms in C++](https://github.com/utilForever/ModernCpp/blob/master/Articles/The%20Four%20Polymorphisms%20in%20C%2B%2B.md)

## Examples

### Classes

[polymorphism.cpp]() -  

### Declaration

[scoped_enum.cpp]() - 

### Exceptions

[stack_unwinding1.cpp]() - 

[stack_unwinding2.cpp]() - 

[try_catch_throw1.cpp]() -

[try_catch_throw2.cpp]() - 

### Expressions

[operator_overloading.cpp]() - 

### Keywords

[alignas.cpp]() - 

[const_cast.cpp]() - 

[default.cpp]() -

[delete.cpp]() - 

[dynamic_cast.cpp]() - 

[nullptr.cpp]() - 

[reinterpret_cast.cpp]() - 

[static_cast.cpp]() - 

[typeid.cpp]() - 

### Libraries

#### Thread support

[async.cpp]() - 

[future.cpp]() -

[promise.cpp]() - 

### Miscellaneous

[RAII-rule_of_five.cpp]() - 

[RAII-rule_of_zero.cpp]() - 

### Templates

[class_template.cpp]() - 

[function_template.cpp]() - 

## Tutorials

### C++ Programming Basic Course Slides (presented by Korean)

[1st Study: From C to C++ (1/4)](http://www.slideshare.net/utilforever/c-programming-1s-study)
  - printf, scanf → cin, cout
  - bool type
  - auto keyword

[2nd Study: From C to C++ (2/4)](http://www.slideshare.net/utilforever/c-programming-2nd-study)
  - Range-based for
  - malloc, free → new, delete
  - NULL → nullptr
  - static_cast

[3rd Study: From C to C++ (3/4)](http://www.slideshare.net/utilforever/c-programming-3rd-study)
  - Scoped enum
  - Binary literal, separator
  - std::string

[4th Study: From C to C++ (4/4)](http://www.slideshare.net/utilforever/c-programming-4th-study)
  - Reference
  - Function overloading
  - Namespace

[5th Study: Object-Oriented Programming (1/8)](http://www.slideshare.net/utilforever/c-programming-5th-study)
  - Class and object
  - Access modifier: public, protected, private
  - Information hiding, Encapsulation

[6th Study: Object-Oriented Programming (2/8)](http://www.slideshare.net/utilforever/c-programming-6th-study)
  - Constructor
  - Destructor
  - this pointer

[7th Study: Object-Oriented Programming (3/8)](http://www.slideshare.net/utilforever/c-programming-7th-study)
  - Copy constructor
  - Copy assignment operator
  - Shallow copy / deep copy
  - Rule of zero / rule of three

[8th Study: Object-Oriented Programming (4/8)](http://www.slideshare.net/utilforever/c-programming-8th-study)
  - Member variable
    - static
    - const
    - reference
    - const reference
  - Member function
    - static
    - const
    - default parameter

[9th Study: Object-Oriented Programming (5/8)](http://www.slideshare.net/utilforever/c-programming-9th-study)
  - Inheritance
  - Method overriding
  - Something about superclasses
  - Up / down casting

[10th Study: Object-Oriented Programming (6/8)](http://www.slideshare.net/utilforever/c-programming-10th-study)
  - Polymorphism
  - Pure virtual method

[11th Study: Object-Oriented Programming (7/8)](http://www.slideshare.net/utilforever/c-programming-11th-study)
  - Operator Overloading

[12th Study: Object-Oriented Programming (8/8)](http://www.slideshare.net/utilforever/c-programming-12th-study)
  - Multiple inheritance
  - vtable (virtual function table)
  - RTTI(Run-Time Type Information)

[13th Study: Exception Handling](http://www.slideshare.net/utilforever/c-programming-13th-study)
  - Exception handling in C++
  - try ~ catch ~ throw
  - Standard exception classes
  - Stack unwinding

[14th Study: Generic Programming](http://www.slideshare.net/utilforever/c-programming-14th-study)
  - Generic programming in C++
  - Function template
  - Class template

[15th Study: TBA](...)

### Basic Curriculum

1. From C To C++
  - (1st) printf, scanf -> std::cin, std::cout
  - (1st) bool type
  - (1st) auto
  - (2nd) Range-based for
  - (2nd) malloc, free -> new, delete
  - (2nd) NULL -> nullptr
  - (2nd) Casting 1: static_cast 
  - (3rd) Scoped enum
  - (3rd) Binary literal, Separator
  - (3rd) std::string 
  - (4th) Reference
  - (4th) Function overloading
  - (4th) Namespace
  - (TBD) decltype
  - (TBD) Casting 2: dynamic_cast, const_cast, reinterpret_cast
  - (TBD) typedef -> type alias
  - (TBD) Uniform initialization
  - (TBD) Initializer list
  - (TBD) Lambda expression
  - (TBD) Lvalue / Rvalue reference
  - (TBD) Move semantics
  - (TBD) Perfect forwarding
  - (TBD) Smart pointer: unique_ptr, shared_ptr, weak_ptr
2. OOP: Object-Oriented Programming
  - (5th) Class and Object
  - (5th) Access modifier: public, protected, private
  - (5th) Information hiding, Encapsulation
  - (6th) Constructor
  - (6th) Destructor
  - (6th) this pointer
  - (7th) Copy constructor
  - (7th) Copy assignment operator
  - (7th) Shallow copy, Deep copy
  - (7th) Rule of zero, Rule of three
  - (8th) Member variable: static / const / reference / const reference
  - (8th) Method: static / const / method overloading / default parameter / inline
  - (9th) Inheritance
  - (9th) Method Overriding
  - (9th) Something about superclasses
  - (9th) Up / Down casting
  - (10th) Polymorphism
  - (10th) Pure virtual method
  - (11th) Operator overloading
  - (12th) Multiple inheritance
  - (12th) vtable, RTTI
  - (TBD) Special functions 3: Move constructor, Move assignment operator
  - (TBD) Special functions 4: std::initializer_list constructor, Inheriting constructor
  - (TBD) Rule of five
  - (TBD) =default, =delete 
  - (TBD) explicit keyword
  - (TBD) friend keyword
  - (TBD) mutable
  - (TBD) overriding keyword
  - (TBD) final keyword
  - (TBD) PIMPL
3. Exception Handling
  - (13th) Exception handling in C++
  - (13th) try ~ catch ~ throw / throw list (noexcept)
  - (13th) Standard exception classes
  - (13th) Stack unwinding
  - (TBD) Nested exception
  - (TBD) Function-try-block
4. Generic Programming: Template
  - (14th) Generic programming in C++
  - (14th) Function template
  - (14th) Class template
  - (TBD) Template specialization
  - (TBD) Partial specialization
  - (TBD) Template inheritance vs template specialization
  - (TBD) Template aliases
  - (TBD) decltype + auto
  - (TBD) Function template
  - (TBD) Template recursion
  - (TBD) Variadic template
  - (TBD) Variable template
  - (TBD) Type inference
  - (TBD) SFINAE
  - (TBD) Template metaprogramming
  - (TBD) Type traits
  - (TBD) constexpr
5. Concurrency: Multithreading Programming
  - (TBD) Race condition, Deadlock
  - (TBD) Atomic task
  - (TBD) thread
  - (TBD) mutex, lock, call_once
  - (TBD) condition_variable
  - (TBD) async
  - (TBD) future, promise
  - (TBD) Thread pool
6. STL: Standard Library
  - (TBD) vector, deque, list, array
  - (TBD) queue, priority_queue, stack
  - (TBD) pair, tuple, map, multimap, set, multiset
  - (TBD) algorithm
  - (TBD) function
  - (TBD) forward_list
  - (TBD) unordered_map, unordered_multimap, unordered_set, unordered_multiset
  - (TBD) bitset
  - (TBD) ratio
  - (TBD) chrono
  - (TBD) random
  - (TBD) regular expression