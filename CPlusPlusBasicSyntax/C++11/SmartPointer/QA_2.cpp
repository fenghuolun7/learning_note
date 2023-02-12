// 代码出自链接：http://www.jellythink.com/archives/771
#include <functional>
#include <iostream>
#include <memory>

class A
{
public:
    A() = default;
    std::string s = "init";
    int a = 1;
};
std::function<void(std::shared_ptr<A>&, std::string)> Functional;

void doit(const std::shared_ptr<A> &ptr, std::string s)
{
    ptr->s = s;
    ptr->a = 2;
}

int main()
{
    std::shared_ptr<A> a(new A());
    std::string s = "Hello";
    auto NewFunctional = std::bind(doit, std::ref(a), s);
    NewFunctional();
    std::cout << a->a << std::endl;
    std::cout << a->s << std::endl;
    return 0;
}