#include <type_traits>
#include <new>
#include <iostream>
#include <string>

template <class T>
typename std::enable_if_t<std::is_floating_point_v<T>, T> // TO DO version with typename std::enable_if_t<std::is..::type oraz std::enable_if_t<std::is_floating_point_v<T>, T>
construct(T arg)
{
    std::cout << "default constructing trivially default constructible T\n";
    return arg;
}

int main()
{
    float val = 4.20f;
    construct(val);
}