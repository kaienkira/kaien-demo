#include <iostream>
#include <utility>

namespace test_declval {

class A {
public:
    A() = delete;

    int foo()
    {
        return 0;
    }
};

void test()
{
    std::cout << "test_declval" << std::endl;
    decltype(std::declval<A>().foo()) a = 0;
    std::cout << "  " << typeid(a).name() << std::endl;
}

} // namespace test_declval

int main()
{
    test_declval::test();

    return 0;
}
