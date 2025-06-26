#include <algorithm>
#include <iostream>
#include <vector>

int main(void)
{
    std::vector<int> v = {1, 2, 3};
    std::cout << std::all_of(v.begin(), v.end(), [](int i) { return i != 0; }) << std::endl;

    return 0;
}
