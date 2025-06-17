#include <format>
#include <iostream>
#include <type_traits>

class A {
};

void test_is_integral()
{
    std::cout << std::format("(int) is_integral = {}",
        std::is_integral_v<int>) << std::endl;
    std::cout << std::format("(long) is_integral = {}",
        std::is_integral_v<long>) << std::endl;
    std::cout << std::format("(bool) is_integral = {}",
        std::is_integral_v<bool>) << std::endl;
    std::cout << std::format("(float) is_integral = {}",
        std::is_integral_v<float>) << std::endl;
    std::cout << std::format("(int *) is_integral = {}",
        std::is_integral_v<int *>) << std::endl;
    std::cout << std::format("(int &) is_integral = {}",
        std::is_integral_v<int &>) << std::endl;
    std::cout << std::format("(int[]) is_integral = {}",
        std::is_integral_v<int[]>) << std::endl;
    std::cout << std::format("(A) is_integral = {}",
        std::is_integral_v<A>) << std::endl;
    std::cout << std::endl;
}

void test_is_reference()
{
    std::cout << std::format("(int) is_reference = {}",
        std::is_reference_v<int>) << std::endl;
    std::cout << std::format("(int *) is_reference = {}",
        std::is_reference_v<int *>) << std::endl;
    std::cout << std::format("(int &) is_reference = {}",
        std::is_reference_v<int &>) << std::endl;
    std::cout << std::format("(int &&) is_reference = {}",
        std::is_reference_v<int &&>) << std::endl;
    std::cout << std::format("(const int &) is_reference = {}",
        std::is_reference_v<const int &>) << std::endl;
    std::cout << std::format("(volatile int &) is_reference = {}",
        std::is_reference_v<volatile int &>) << std::endl;
    std::cout << std::endl;
}

void test_is_lvalue_reference()
{
    std::cout << std::format("(int) is_lvalue_reference = {}",
        std::is_lvalue_reference_v<int>) << std::endl;
    std::cout << std::format("(int *) is_lvalue_reference = {}",
        std::is_lvalue_reference_v<int *>) << std::endl;
    std::cout << std::format("(int &) is_lvalue_reference = {}",
        std::is_lvalue_reference_v<int &>) << std::endl;
    std::cout << std::format("(int &&) is_lvalue_reference = {}",
        std::is_lvalue_reference_v<int &&>) << std::endl;
    std::cout << std::endl;
}

void test_is_rvalue_reference()
{
    std::cout << std::format("(int) is_rvalue_reference = {}",
        std::is_rvalue_reference_v<int>) << std::endl;
    std::cout << std::format("(int *) is_rvalue_reference = {}",
        std::is_rvalue_reference_v<int *>) << std::endl;
    std::cout << std::format("(int &) is_rvalue_reference = {}",
        std::is_rvalue_reference_v<int &>) << std::endl;
    std::cout << std::format("(int &&) is_rvalue_reference = {}",
        std::is_rvalue_reference_v<int &&>) << std::endl;
    std::cout << std::endl;
}

int main(void)
{
    test_is_integral();
    test_is_reference();
    test_is_lvalue_reference();
    test_is_rvalue_reference();

    return 0;
}
