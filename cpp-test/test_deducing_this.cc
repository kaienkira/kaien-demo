class A {
public:
    void doFunc(this auto &self);
};

void A::doFunc(this auto &self)
{
}

int main(void)
{
    A a;
    const A &a1 = a;

    a.doFunc();
    a1.doFunc();

    return 0;
}
