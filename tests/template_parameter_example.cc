#include <type_traits>
#include <iostream>

template <typename T, typename std::enable_if_t<std::is_integral_v<T>, int> = 0>
void foo(T x)
{
    std::cout << x << std::endl;
}

template <typename T, typename std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
void foo(T x)
{
    std::cout << x << std::endl;
}

int main()
{
    foo(42);   // Calls the first overload
    foo(3.14); // Calls the second overload
}