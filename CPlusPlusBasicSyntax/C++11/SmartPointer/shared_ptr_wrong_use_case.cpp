#include <algorithm>
#include <vector>
#include <memory>

class X
{
};

int main()
{
    X *x = new X();
    std::shared_ptr<X> p1(x);
    std::shared_ptr<X> p2(x);
    std::shared_ptr<X> p3(p1.get());
}
