#include <iostream>
#include <type_traits>

class A {
};

class B : public A {
};

int main(void)
{
    std::cout << std::is_base_of<A, B>::value << std::endl;
    std::cout << std::is_base_of_v<A, B> << std::endl;

    std::cout << std::is_base_of<B, A>::value << std::endl;
    std::cout << std::is_base_of_v<B, A> << std::endl;

    return 0;
}
