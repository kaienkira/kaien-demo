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

    int &getA() { return a_; }
    float &getB() { return b_; }
    int &getC() { return c_; }

private:
    int a_;
    float b_;
    int c_;
};

template<>
struct std::tuple_size<B> : std::integral_constant<size_t, 3> {
};

template<>
struct std::tuple_element<0, B> {
    using type = int;
};

template<>
struct std::tuple_element<1, B> {
    using type = float;
};

template<>
struct std::tuple_element<2, B> {
    using type = int;
};

template<size_t I>
auto &get(B& o);

template<>
auto &get<0>(B &o) { return o.getA(); }

template<>
auto &get<1>(B &o) { return o.getB(); }

template<>
auto &get<2>(B &o) { return o.getC(); }

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
