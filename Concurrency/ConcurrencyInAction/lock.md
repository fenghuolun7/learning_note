# std::lock_guard<>
  RAII 构造时给互斥加锁，析构时解锁
  ## std::adopt_lock 参数
    获取互斥体m的所有权，而不尝试锁定它
```C++
    std::lock l{mut_a, mut_b};
    std::lock_guard<std::mutex> lock_a(mut_a, std::adopt_lock);
    std::lock_guard<std::mutex> lock_b(mut_b, std::adopt_lock);
```
以上写法也没有死锁风险

# std::lock_guard<>(C++17)
给多个互斥体加锁时，没有死锁风险
```C++
    std::scoped_lock l{mut_a, mut_b};
```

# std::unique_lock<>
特点：加锁灵活

  ## std::adopt_lock 参数（与std::lock_guard<>中的相同）
    获取互斥体m的所有权，而不尝试锁定它。
  ## std::defer_lock 参数
    互斥在完成构造时处于无锁状态，等有需要时才在`std::unique_lock` 对象上调用`lock()`
    或者把`std::unique_lock`对象交给`std::lock()`
```C++
        std::unique_lock<std::mutex> lock_a(lhs.m,std::defer_lock);
        std::unique_lock<std::mutex> lock_b(rhs.m,std::defer_lock);
        std::lock(lock_a,lock_b);
```

