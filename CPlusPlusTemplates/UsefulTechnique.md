# 类模板中可以初始化一个数据类型，然后通过类模板的构造函数以以下方式加以赋值：
```C++
explicit Result(E const& e) : mData(e) {}
```

# 在写 类模板中的时候， 以下返回值需要特别注意
is_nothrow_destructible
is_nothrow_move_constructible
is_nothrow_copy_constructible

这些值可以放入 noexcept 中，也可运用在 enable_if 中
