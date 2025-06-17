#include <iostream>

class A {
public:
    static int operator()(int a, int b) {
        return a + b;
    }

    static int operator[](int a, int b) {
        return a * b;
    }
};

int main(void)
{
    int a = 1;
    int b = 2;
    int c = A::operator()(a, b);
    int d = A::operator[](a, b);

    auto is_even = [](int i) static {
        return i % 2 == 0;
    };
    is_even(c);

    std::cout << c << std::endl;
    std::cout << is_even(c) << std::endl;
    std::cout << is_even(d) << std::endl;
}
