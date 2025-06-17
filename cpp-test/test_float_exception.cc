#include <cfenv>
#include <cstdint>
#include <format>
#include <iostream>
#include <stdfloat>

//#pragma STDC FENV_ACCESS ON

int main(void)
{
    //::feenableexcept(FE_ALL_EXCEPT);

    std::cout << "0 / 0" << std::endl;
    std::feclearexcept(FE_ALL_EXCEPT);
    std::float32_t qnan = 0.0f32 / 0.0f32;
    std::cout << std::format("FE_INVALID = {:s}",
        std::fetestexcept(FE_INVALID) > 0)
        << std::endl;

    std::cout << "qNaN += 1" << std::endl;
    std::feclearexcept(FE_ALL_EXCEPT);
    qnan += 1;
    std::cout << std::format("FE_INVALID = {:s}",
        std::fetestexcept(FE_INVALID) > 0)
        << std::endl;

    std::cout << "sNaN += 1" << std::endl;
    std::feclearexcept(FE_ALL_EXCEPT);
    std::float32_t snan =
        std::numeric_limits<std::float32_t>::signaling_NaN();
    snan += 1;
    std::cout << std::format("FE_INVALID = {:s}",
        std::fetestexcept(FE_INVALID) > 0)
        << std::endl;

    return 0;
}
