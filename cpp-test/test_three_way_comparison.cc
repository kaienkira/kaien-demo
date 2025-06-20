#include <compare>
#include <iostream>

template <class T>
void printOrder(const T &v1, const T &v2)
{
    auto o = v1 <=> v2;

    std::cout << std::format("{} == {} : {:s}",
        v1, v2, std::is_eq(o))
        << std::endl;
    std::cout << std::format("{} < {} : {:s}",
        v1, v2, std::is_lt(o))
        << std::endl;
    std::cout << std::format("{} > {} : {:s}",
        v1, v2, std::is_gt(o))
        << std::endl;
    std::cout << std::format("{} != {} : {:s}",
        v1, v2, std::is_neq(o))
        << std::endl;
    std::cout << std::format("{} <= {} : {:s}",
        v1, v2, std::is_lteq(o))
        << std::endl;
    std::cout << std::format("{} >= {} : {:s}",
        v1, v2, std::is_gteq(o))
        << std::endl;
}

int main(void)
{
    // std::strong_ordering o1 = (1 <=> 2);
    // std::partial_ordering o2 = (+0.0 <=> -0.0);

    printOrder(1, 2);
    printOrder(+0.0, -0.0);
    printOrder(std::numeric_limits<float>::quiet_NaN(),
               std::numeric_limits<float>::quiet_NaN());

    return 0;
}
