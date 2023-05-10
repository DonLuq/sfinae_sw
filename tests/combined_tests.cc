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
void print_if_integral(T val, std::enable_if_t<std::is_integral_v<T>> * = nullptr)
{
    std::cout << "Integral value: " << val << std::endl;
}

template <typename T, typename = std::enable_if_t<std::is_class_v<T>>>
class MyClass
{
};

int main()
{
    IntegralOnly<int> i; // compiles
    // IntegralOnly<float> f; // does not compile

    std::cout << square(5.0) << std::endl; // prints 25.0
    // std::cout << square("hello") << std::endl; // does not compile

    print_if_integral(5); // prints "Integral value: 5"
    // print_if_integral(3.14); // does not print anything

    // MyClass<std::string> s; // does not compile
    MyClass<int> i; // compiles

    return 0;
}
