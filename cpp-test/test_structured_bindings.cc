#include <cstddef>
#include <iostream> 
#include <utility>

struct A {
    A() : a_(1), b_(2.0), c_(3)
    {
    }

    ~A()
    {
    }

    int a_;
    float b_;
    int c_;
};

class B {
public:
    B() : a_(1), b_(2.0), c_(3)
    {
    }

    ~B()
    {
    }

    
    template <size_t I>
    auto &get()
    {
        if constexpr (I == 0) {
            return a_;
        } else if constexpr (I == 1) {
            return b_;
        } else if constexpr (I == 2) {
            return c_;
        }
    }

private:
    int a_;
    float b_;
    int c_;
};

template <>
struct std::tuple_size<B> : std::integral_constant<size_t, 3> {
};

template <>
struct std::tuple_element<0, B> {
    using type = int;
};

template <>
struct std::tuple_element<1, B> {
    using type = float;
};

template <>
struct std::tuple_element<2, B> {
    using type = int;
};

int main(void)
{
    {
        A sa;
        const auto &[a, b, c] = sa;
        std::cout << a << b << c << std::endl;
    }
    {
        B sb;
        auto &[a, b, c] = sb;
        std::cout << a << b << c << std::endl;
    }

    return 0;
}
