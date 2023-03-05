#include <algorithm>
#include <vector>
#include <memory>

class B;
class A
{
public:
    std::shared_ptr<B> b_;
};

class B
{
public:
    std::shared_ptr<A> a_;
};

// memory leak because of copying shared_ptr
// Kind of like a deadlock
int main()
{
    std::shared_ptr<A> a(new A());
    std::shared_ptr<B> b(new B());
    a->b_ = b;
    b->a_ = a;
}
