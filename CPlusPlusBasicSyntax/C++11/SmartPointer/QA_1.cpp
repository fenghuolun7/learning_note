#include <algorithm>
#include <vector>
#include <memory>
#include <iostream>

struct Foo
{
    Foo(int n = 0) noexcept : bar(n)
    {
        std::cout << "Foo::Foo(), bar = " << bar << " @ " << this << '\n';
    }
    ~Foo()
    {
        std::cout << "Foo::~Foo(), bar = " << bar << " @ " << this << "\n";
    }
    int getBar() const noexcept { return bar; }

private:
    int bar;
};

int main()
{
    std::cout << "1) unique ownership\n";
    {
        std::shared_ptr<Foo> sptr = std::make_shared<Foo>(100);
        std::shared_ptr<Foo> ssptr = sptr;

        std::cout << "Foo::bar = " << ssptr->getBar() << ", use_count() = "
                  << ssptr.use_count() << '\n';

        // Reset the shared_ptr without handing it a fresh instance of Foo.
        // The old instance will be destroyed after this call.
        std::cout << "call sptr.reset()...\n";
        sptr.reset(); // calls Foo's destructor here
        std::cout << "After reset(): use_count() = " << ssptr.use_count()
                  << ", sptr = " << ssptr << '\n';
    } // No call to Foo's destructor, it was done earlier in reset().
}