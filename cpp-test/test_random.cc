#include <ctime>
#include <iostream>
#include <random>

int main(void)
{
    std::mt19937 rand_eng(std::time(nullptr));
    std::uniform_int_distribution<> rand_dist(0, 99);

    std::vector<int> rand_count(100, 0);
    for (int i = 0; i < 1000000; ++i) {
        size_t index = rand_dist(rand_eng);
        ++rand_count[index];
    }
    for (int count : rand_count) {
        int star_count = count / 1000;
        for (int i = 0; i < star_count; ++i) {
            std::cout << '*';
        }
        std::cout << std::endl;
    }

    return 0;
}
