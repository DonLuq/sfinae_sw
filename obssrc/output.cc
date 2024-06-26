#include <type_traits>
#include <iostream>

template <typename T>
    requires std::is_integral_v<T>
class IntegralOnly
{
};

template <typename T>
T square(T x)
    requires std::is_floating_point_v<T>
{
    return x * x;
}

template <typename T>
T max(T a, T b)
    requires std::is_arithmetic_v<T> && std::is_unsigned_v<T> && std::is_same_v<T, decltype(a + b)>
{
    return (a > b) ? a : b;
}

int main()
{
    IntegralOnly<int> i; // compiles

    std::cout << square(5.0) << std::endl; // prints 25.0
    std::cout << max((unsigned)2, (unsigned)9) << std::endl;

    return 0;
}
