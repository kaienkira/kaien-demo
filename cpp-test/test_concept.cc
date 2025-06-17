#include <type_traits>

class A
{
};

template<class T, class U>
concept Derived = std::is_base_of<U, T>::value;

template<class T>
void f(T t) requires Derived<T, A>
{
}

class B : public A
{
};

class C
{
};

int main(void)
{
    B c;
    f(c);

    return 0;
}
