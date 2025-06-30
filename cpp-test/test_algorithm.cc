#include <algorithm>
#include <iostream>
#include <vector>

int main(void)
{
    std::vector<int> v = {1, 2, 3, 4};

    auto p_not_zero = [](int i) { return i != 0; };
    auto p_is_one = [](int i) { return i == 1; };

    std::cout << std::all_of(v.begin(), v.end(), p_not_zero) << std::endl;
    std::cout << std::ranges::all_of(v, p_not_zero) << std::endl;

    std::cout << std::any_of(v.begin(), v.end(), p_is_one) << std::endl;
    std::cout << std::ranges::any_of(v, p_is_one) << std::endl;

    std::cout << std::none_of(v.begin(), v.end(), p_is_one) << std::endl;
    std::cout << std::ranges::none_of(v, p_is_one) << std::endl;

    return 0;
}
