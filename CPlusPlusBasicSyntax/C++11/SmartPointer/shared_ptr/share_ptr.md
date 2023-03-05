# 中使用`std::share_ptr`时容易出现的问题

## 意外延长对象的生命期
只要有一个指向对象的`std::shared_ptr`存在，***该对象就不会析构**
如果遗漏了一个拷贝的析构，就会有内存泄漏的问题, The cause of memory leak is usually circular reference
## Circular reference
two class hold each other's shared_ptr, when the program ends, each shared pointer still hold one object which leads to
memory leak.
## example :
```c++
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
```

### 解决方法：
使用`std::weak_ptr`,其不会产生引用计数（use_count），
必要的时候可以通过`lock()` 函数提升至`std::share_ptr`

## 将同一份动态内存托管给多个智能指针
p7、p8和p9指向了相同的动态内存，但由于它们是相互独立创建的，因此各自的引用计数都是1，即相互不知道对方的存在，认为自己是这块内存的唯一管理者。
### wrong use case :
```c++
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
```

# Q & A
## Will reset() affect other shared objects pointing to the same object ?

NO, it only affect the managed object.
See reset.cpp as an example.

## Can shared_ptr work with std::ref() ?
YES, it can, see QA_2 for a example.
