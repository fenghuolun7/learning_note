#!/bin/bash

cat > test0.cc <<EOF
#include <iostream>
#include <string>
void foo(){
    std::cout << "this is the target function." << std::endl;
}
EOF

cat > test1.cc <<EOF
#include <iostream>
#include <string>
extern void foo();
void test1_so_func(){
    std::cout << "in shared object 1; calling target function" << std::endl;
    foo();
}
EOF

cat > test1.h <<EOF
#pragma once
void test1_so_func();
EOF

cat > test2.cc <<EOF
#include <iostream>
#include <string>
#include "test1.h"
void test2_so_func(){
    std::cout << "in shared object 2; calling shared object 1" <<std::endl;
    test1_so_func();
}
EOF

cat > test2.h <<EOF
#pragma once
void test2_so_func();
EOF

cat > main.cc <<EOF
#include <iostream>
#include <string>
#include "test2.h"
int main() {
  test2_so_func();
  return 0;
}
EOF

# tested version:
# g++ (Ubuntu 5.4.0-6ubuntu1~16.04.12) 5.4.0 20160609
# g++ (Ubuntu 9.3.0-10ubuntu2) 9.3.0
# clang version 11.0.0-++20200513020828+63c0e72b2f8-1~exp1~20200513001456.2968

set -x
g++ -g -fPIC -shared test0.cc -o libtest0.so
g++ -g -fPIC -shared test1.cc -o libtest1.so

g++ -g -fPIC -shared test2.cc -o libtest2.so -L. -ltest1

# 1. uncomment the follow line for g++ so the main.cc compile/link work.
#g++ -g -fPIC -shared test2.cc -o libtest2.so -L. -ltest1 -ltest0

# 2. if you replace all g++ with clang++, the compiling/linking for main.cc works.

g++ -g -std=c++11 main.cc -L. -ltest2 -ltest0