# erase
在使用循环遍历 std::vector 时，如使用erase()，erase()的返回值自动获取下一个iterator，谨慎使用iterator++
## wrong use case
```c++
#include <vector>
#include <iostream>
 
 
void print_container(const std::vector<int>& c) 
{
    for (int i : c)
        std::cout << i << " ";
    std::cout << '\n';
}
 
int main( )
{
    std::vector<int> c{0, 1, 2, 3, 4, 5, 6, 7, 8};

    // risk of heap overflow
    for (std::vector<int>::iterator it = c.begin(); it != c.end();++it)
    {
        if (*it % 2 == 0)

            c.erase(it);

            // // wrong either !!
            // it = c.erase(it);
    }

    print_container(c);
}
```

## correct use case
```c++
#include <vector>
#include <iostream>

void print_container(const std::vector<int> &c)
{
    for (int i : c)
        std::cout << i << " ";
    std::cout << '\n';
}

int main()
{
    std::vector<int> c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (std::vector<int>::iterator it = c.begin(); it != c.end();)
    {
        if (*it % 2 == 0)
            it = c.erase(it);
        else
            ++it;

        print_container(c);
    }
}
```