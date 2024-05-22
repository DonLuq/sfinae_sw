#include <type_traits>
#include <iostream>

template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
class IntegralOnly
{
};

template <typename T>
std::enable_if_t<std::is_floating_point_v<T>, T> square(T x)
{
    return x * x;
}

template <typename T>
std::enable_if_t<std::is_arithmetic_v<T> && std::is_unsigned_v<T>, T> max(T a, T b)
{
    return (a > b) ? a : b;
}

int main()
{
    IntegralOnly<int> i; // compiles

    std::cout << square(5.0) << std::endl; // prints 25.0

    return 0;
}
