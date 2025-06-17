#include <cmath>
#include <cstdint>
#include <format>
#include <iostream>
#include <limits>
#include <string>
#include <type_traits>

template <std::floating_point T>
void printFloatInfo(const std::string &type_name)
{
    std::cout << "+++++ " << type_name << " +++++"
        << std::endl;
    std::cout << std::format("is_float_point: {:s}",
        std::is_floating_point_v<T>)
        << std::endl;
    std::cout << std::format("is_iec559: {:s}",
        std::numeric_limits<T>::is_iec559)
        << std::endl;
    std::cout << std::format("has_infinity: {:s}",
        std::numeric_limits<T>::has_infinity)
        << std::endl;
    std::cout << std::format("has_quiet_NaN: {:s}",
        std::numeric_limits<T>::has_quiet_NaN)
        << std::endl;
    std::cout << std::format("has_signaling_NaN: {:s}",
        std::numeric_limits<T>::has_signaling_NaN)
        << std::endl;
    std::cout << std::format("digits: {} digits10: {} max_digits10: {}",
        std::numeric_limits<T>::digits,
        std::numeric_limits<T>::digits10,
        std::numeric_limits<T>::max_digits10)
        << std::endl;
}

void printFloatBit()
{
    float inf =
        std::numeric_limits<float>::infinity();
    float negative_inf = -inf;
    float zero = +0.0;
    float negative_zero = -0.0;
    float nan_zero_divide_zero = zero / zero;
    float nan_macro = NAN;
    float qnan =
        std::numeric_limits<float>::quiet_NaN();
    float snan =
        std::numeric_limits<float>::signaling_NaN();
    float qnan0 = std::nanf("0");
    float qnan1 = std::nanf("1");
    float qnan2 = std::nanf("2");

    std::cout << std::format("{:10} {:032b}",
        inf,
        *reinterpret_cast<uint32_t *>(&inf))
        << std::endl;
    std::cout << std::format("{:10} {:032b}",
        negative_inf,
        *reinterpret_cast<uint32_t *>(&negative_inf))
        << std::endl;
    std::cout << std::format("{:10} {:032b}",
        zero,
        *reinterpret_cast<uint32_t *>(&zero))
        << std::endl;
    std::cout << std::format("{:10} {:032b}",
        negative_zero,
        *reinterpret_cast<uint32_t *>(&negative_zero))
        << std::endl;
    std::cout << std::format("{:10} {:032b} nan_zero_divide_zero",
        nan_zero_divide_zero,
        *reinterpret_cast<uint32_t *>(&nan_zero_divide_zero))
        << std::endl;
    std::cout << std::format("{:10} {:032b} NAN",
        nan_macro,
        *reinterpret_cast<uint32_t *>(&nan_macro))
        << std::endl;
    std::cout << std::format("{:10} {:032b} qnan",
        qnan,
        *reinterpret_cast<uint32_t *>(&qnan))
        << std::endl;
    std::cout << std::format("{:10} {:032b} snan",
        snan,
        *reinterpret_cast<uint32_t *>(&snan))
        << std::endl;
    std::cout << std::format("{:10} {:032b} qnan0",
        qnan0,
        *reinterpret_cast<uint32_t *>(&qnan0))
        << std::endl;
    std::cout << std::format("{:10} {:032b} qnan1",
        qnan1,
        *reinterpret_cast<uint32_t *>(&qnan1))
        << std::endl;
    std::cout << std::format("{:10} {:032b} qnan2",
        qnan2,
        *reinterpret_cast<uint32_t *>(&qnan2))
        << std::endl;

}

int main(void)
{
    printFloatBit();
    printFloatInfo<float>("float");
    printFloatInfo<double>("double");
    printFloatInfo<long double>("long double");

    return 0;
}
