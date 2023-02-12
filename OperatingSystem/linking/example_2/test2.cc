#include <iostream>
#include <string>
#include "test1.h"
void test2_so_func(){
    std::cout << "in shared object 2; calling shared object 1" <<std::endl;
    test1_so_func();
}
