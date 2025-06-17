#include <cmath>
#include <format>
#include <numbers>
#include <iostream>

int main(void)
{
    std::cout << std::format("hypot(1, 1, 1) = {}", std::hypot(1, 1, 1)) << std::endl;
    std::cout << std::format("e = {}", std::numbers::e_v<float>) << std::endl;
    std::cout << std::format("e = {}", std::numbers::e_v<double>) << std::endl;
    std::cout << std::format("e = {}", std::numbers::e_v<long double>) << std::endl;
    std::cout << std::format("pi = {}", std::numbers::pi_v<float>) << std::endl;
    std::cout << std::format("pi = {}", std::numbers::pi_v<double>) << std::endl;
    std::cout << std::format("pi = {}", std::numbers::pi_v<long double>) << std::endl;

    return 0;
}
