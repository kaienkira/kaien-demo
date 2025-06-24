#include <initializer_list>
#include <iostream>
#include <vector>

class A {
public:
    A(const std::initializer_list<int> &l)
    {
        v_.insert(v_.end(), l.begin(), l.end());
    }

    void print()
    {
        for (const int &i : v_) {
            std::cout << i << std::endl;
        }
    }

private:
    std::vector<int> v_;
};

int main(void)
{
    A a = {1, 2, 3};
    a.print();

    return 0;
}
