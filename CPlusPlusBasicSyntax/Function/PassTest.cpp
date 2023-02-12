// this file is aimed to test whether
// pass by value is able to use c++11
// copy and move constructors

#include <iostream>

class X
{
public:
    X(const X &&)
    {
        std::cout << "X(const X&&)" << std::endl;
    }

    X(const X &)
    {
        std::cout << "X(const X&)" << std::endl;
    }

    X() = default;
    int a = 0;
    constexpr static int b = 3;
};

void pass_by_value(X x)
{
    x.a = 2;
}

void pass_by_const_value(const X& x)
{
    // // cannot change
    // x.a = 2;
}

int main()
{   
    X x;

    const X cx;

    pass_by_value(X());
    pass_by_value(x);

    pass_by_value(X());
    pass_by_value(cx);
    std::cout << x.a << std::endl;
    // must has a value,then can we print
    std::cout << x.b << std::endl;

    // will not create copy
    pass_by_const_value(X());
    pass_by_const_value(x);
    pass_by_const_value(cx);
}