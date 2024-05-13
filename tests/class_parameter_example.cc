#include <type_traits>
#include <new>
#include <iostream>
#include <string>

template <class T, class Enable = void>
class A
{
}; // primary template

template <class T>
class A<T, typename std::enable_if<std::is_floating_point_v<T>>::type>
{
}; // specialization for floating point types

int main()
{
    A<int>{};    // OK: matches the primary template
    A<double>{}; // OK: matches the partial specialization
}
