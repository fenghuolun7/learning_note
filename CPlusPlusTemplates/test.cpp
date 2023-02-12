#include <iostream>

template <typename CallBack>
class Signal
{
};

template <typename Ret, typename... Args>
class Signal<Ret(Args...)>
{
public:
    void aaa()
    {
        std::cout << "hello" << std::endl;
    }
};

int main()
{
    Signal<void(void)> s;
    s.aaa();
}