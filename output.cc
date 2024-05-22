#include <concepts>

template <typename T>
    requires std::integral<T> && std::signed_integral<T>
T A(T a, T b, T c)
{
    return a + b + c;
}

int main()
{
    A<int>(1, 2, 3);
}