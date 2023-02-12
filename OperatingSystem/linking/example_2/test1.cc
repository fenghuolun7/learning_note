#include <iostream>
#include <string>
extern void foo();
void test1_so_func(){
    std::cout << "in shared object 1; calling target function" << std::endl;
    foo();
}
