constexpr

# virtual
基类指针指向子类对象
子类析构函数最好用virtual

# [[noreturn]]
直接抛异常，不返回，方便编译器优化

# 子类调用父类构造函数
A() : B()

# std::is_trivially 为啥要使用？
https://learn.microsoft.com/en-us/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170
## Trivial types:
1. no virtual functions or virtual base classes,

2. no base classes with a corresponding non-trivial constructor/operator/destructor

3. no data members of class type with a corresponding non-trivial constructor/operator/destructor

you can memcopy such objects but you cannot reliably consume them from a C program

## Standard layout types:

no virtual functions or virtual base classes

all non-static data members have the same access control

all non-static members of class type are standard-layout

any base classes are standard-layout

has no base classes of the same type as the first non-static data member.

meets one of these conditions:

no non-static data member in the most-derived class and no more than one base class with non-static data members, or

has no base classes with non-static data members

It is memcopy-able and the layout is sufficiently defined that it can be consumed by C programs.

## POD types
When a class or struct is both trivial and standard-layout, it is a POD


# std::decay
https://en.cppreference.com/w/cpp/types/decay
Applies lvalue-to-rvalue, array-to-pointer, and function-to-pointer implicit conversions to the type T, removes cv-qualifiers, and defines the resulting type as the member typedef type.

# 为啥模板里面class 中都要求不抛出异常

# union
## discriminated union ： 
It encloses the union in a struct
## union 类型不安全的体现
详见 type_safe.cpp
类型不安全我理解主要是可能会发生隐式类型转换。
## unrestricted union
union with a non-trivial constructor

if any non-static data member of a union has a non-trivial default constructor (12.1), copy constructor (12.8), move constructor (12.8), copy assignment operator (12.8), move assignment operator (12.8), or destructor (12.4), the corresponding member function of the union must be user-provided or it will be implicitly deleted (8.4.3) for the union

 If the union is an anonymous union inside a class or struct, then any special member functions of the class or struct that aren't user provided are marked as deleted

# enum
1. 限定作用域
enum class
2. 不限定作用域
enum

# explicit in_place_t() = default 这句话怎么解释？

# in_place_t
https://en.cppreference.com/w/cpp/utility/variant/variant
https://www.zhihu.com/question/66032208

# decltype

# declval


# placement new
https://blog.csdn.net/xiaorenwuzyh/article/details/44514815
new (&left_) L(e.left_);

# std::result_of
Deduces the return type of an INVOKE expression at compile time.    
https://en.cppreference.com/w/cpp/types/result_of

# std::is_constructible
Trait class that identifies whether T is a constructible type with the set of argument types specified by Arg

# default

目前的理解：
1. A() = default 与 A(){} 的区别：
会影响类类型trivial 或者 POD 的判断

2. 加了default 编译器会为程序生成默认构造函数。

# 什么时候 用栈存储，什么时候用堆存储？

# std::result_of  decltype declval 对比

# std::addressof

# 复制构造函数 移动构造函数 =default 干了啥？

# std::forward() std::move()
```c++
A(T&& t){
    std::cout << "A(T&& t)" << std::endl;
    this->t = std::forward<T>(t);
}
```
在移动构造函数中，使用 `std::forward<T>()` 代替 `std::move()` 没有问题，
但是为了语义清晰，最好还是在移动构造函数中使用`std::move()`

# 返回值
在 if else 中，
每个分支都要返回，并且每个返回值的类型都要与定义的相同。

# 类中 构造函数和析构函数的顺序


# 奇怪的用法
```c++
class State {
public:
    typedef std::shared_ptr<State> Ptr;
```

# std::shared_ptr
主要是为了内存管理
# std::function

# cast

# inline

