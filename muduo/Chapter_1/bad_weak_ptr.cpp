#include <algorithm>
#include <vector>
#include <memory>
#include <mutex>
#include <thread>
#include <iostream>
#include <chrono>

// 1:
// pass shared_ptr of this in destructor, it is pretty dangerous.

class Foo;

void do123(const std::shared_ptr<Foo> &x)
{
    std::cout << "123" << std::endl;
}

class Foo : public std::enable_shared_from_this<Foo>
{
public:
    ~Foo()
    {
        do123(shared_from_this());
    }
    Foo() = default;
};

// 2:
// pass shared_ptr of this in destructor, it is pretty dangerous.

class Example_2;

class Example_1 : public std::enable_shared_from_this<Example_1>
{
public:
    void do123()
    {
        auto example_2 = std::make_shared<Example_2>(this->shared_from_this());
    }

    Example_1() = default;
};

class Example_2
{
public:
    Example_2(const std::shared_ptr<Example_1> &ptr) : ptr_(ptr) {}

    std::shared_ptr<Example_1> ptr_;
};

///////////////////////////////////////////////////////////////////////////////////////////

class Example_4;

class Example_3 : public std::enable_shared_from_this<Example_3>
{
public:
    std::shared_ptr<void>  do123()
    {
        auto example_4 = std::make_shared<Example_4>(this->shared_from_this());

        return example_4;
    }

    Example_3() = default;
};

class Example_4
{
public:
    Example_4(const std::shared_ptr<Example_3> &ptr) : ptr_(ptr) {}

    std::shared_ptr<Example_3> ptr_;
};


// notice here:
std::shared_ptr<void> global_shared_ptr;

int main()
{

    // // idkw, even use try catch, it will coredump anyway.
    // try
    // {
    //     std::shared_ptr<Foo> p1(new Foo());
    // }
    // catch (const std::bad_weak_ptr &e)
    // {
    //     std::cout << e.what() << '\n';
    // }

    printf("========\n");

    try
    {
        // wrong:
        Example_1 e1;
        e1.do123();
    }
    catch (const std::bad_weak_ptr &e)
    {
        std::cout << e.what() << '\n';
    }

    printf("========\n");

    // correct :
    std::shared_ptr<Example_1> e2(new Example_1());
    e2->do123();

    printf("========\n");

    // wrong :
    Example_3 e3;
    global_shared_ptr = e3.do123();
}