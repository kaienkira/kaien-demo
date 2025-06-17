#include <iostream>

class A {
public:
    int operator[](int a, int b, int c, int d) {
        return a + b + c + d;
    }
};

int main(void)
{
    A a;

    std::cout << a[1, 1, 1, 1] << std::endl;

    return 0;
}
