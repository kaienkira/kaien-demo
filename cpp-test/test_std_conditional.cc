#include <iostream>
#include <type_traits>
#include <typeinfo>
 
int main() 
{
    using Type1 = std::conditional<true, int, double>::type;
    using Type2 = std::conditional<false, int, double>::type;
    using Type3 = std::conditional<sizeof(int) >= sizeof(double), int, double>::type;
 
    std::cout << typeid(Type1).name() << '\n';
    std::cout << typeid(Type2).name() << '\n';
    std::cout << typeid(Type3).name() << '\n';
}
