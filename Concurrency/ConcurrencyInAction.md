### **`std::thread`**

std::thread可用于任何可调用类型，包括函数对象，lambda函数  

可调用对象被**复制**到属于新创建的执行线程的存储中，并从那里调用  

线程函数不要持有局部对象的指针或引用,如下就很危险

```c++
struct func
{
    int &i;
    func(int &i_) : i(i_) {}
    void operator()()
    {
        for (unsigned j = 0; j < 1000000; ++j)
        {
            do_something(i);
        }
    }
};
void oops()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach();
}
```
#### 参数传递
传入std::thread 的 参数按值传递
要提前做好类型转化  

引用传递要加std::ref()  

可以传递成员函数指针

#### 转移所有权

std::thread is movable but not copyable. 

  


### **C++'s most vexing parse.**
```c++
std::thread my_thread(background_task());
```

这种写法会被看成函数的声明，而不是对象的定义。可以通过这种写法加以避免。
```c++
std::thread my_thread{background_task()};
```

### **`join()`**
等待线程完成  
在调用`join()`之后，不可再调用`join()`  
在出现异常时也要调用`join()`，以避免意外的生存期问题



### **RAII**


### **`detach()`**

### **`std::thread::hardware_concurrency()`**
返回真正并发运行的线程数

### **`get_id()`**

### **Race conditions**

### **`std::lock_guard`**

### **invariants** ###
不变量的概念
statements that are always true about a particular data structure

### **`互斥体`**
我的理解， 互斥体保护的是花括号里面的所有数据。
在程序执行到后面那个花括号的时候， std::lock_guard 自动释放


我的理解， 在同一线程下对同一互斥体进行加锁，不会有影响

最好将互斥体放到类里面去

### **`使用互斥体容易出现的问题`**

### **stray pointer**

### **接口设计问题**

increase the granularity --> may only need one mutex
decrease the granularity --> need more mutex

two more mutex may lead to deadlock
总是以同样的顺序加锁

https://stackoverflow.com/questions/4127333/should-mutexes-be-mutable

std::scoped_lock<> 可以同时锁住多个锁

3.2.5 锁住一个节点在代码层面是怎么表示的，没搞懂
实现listnode 死锁。

Using a lock hierarchy to prevent deadlock
自定义 hierarchical_mutex 类

# thread_local 关键字

### **std::unique_lock**

第二个参数可以传递
std::adopt_lock 提示 互斥体已经被锁住
std::defer_lock 提示 互斥体还没被锁住，不过将要被锁住。

可提前释放锁
my_lock.unlock();

释放锁后可再次加锁
my_lock.lock();


### **互斥体的所有权可以被传递**
使用场景，

一个网关类来确保 被保护的数据被正确加锁

### **控制加锁的粒度**

Lazy initialization

### **除了锁之外其它保护共享数据的办法### **
### **std::once_flag std::call_once**

当进行lazy init 时有用， 因为赋值只需要进行一次

### **reader-writer mutex### **

c++14之后 实现了读写锁，c++14之前需要借助boost

其它线程可访问函数
提供共享的，只读的访问
std::shared_lock<std::shared_mutex> lk(entry_mutex);

其它线程不可访问函数
std::lock_guard<std::shared_mutex> lk(entry_mutex);

### **Recursive locking### **

std::recursive_mutex
不推荐使用
可多次加锁， 加多少次锁也需解多少次锁

# Synchronizing concurrent operations
### **std::condition_variable std::condition_variable_any**

std::condition_variable 只能与 std::mutex 同时使用（preferred）
std::condition_variable_any 可以与 任何 mutex-like  mutex 使用，所以他有额外开销

### **`notify_one()` 与 `wait()` 搭配使用**

当条件不满足的时候， `wait()` 解锁 并让程序阻塞（因为如果不解锁， 其它线程就无法加锁）
当条件满足的时候 加锁
`notify_one()`必须与`std::unique_lock()`配合使用，因为`wait()` 会重复加锁解锁。

### **`notify_one()` 与 `notify_all()` 的区别**


### **future() 与 condition wait() notify() 比较**

future() promise() 只等一次

event 发生之后， future 不可重置。


### **future()**

std::future 不提供线程同步机制， 需要 加锁或其它来保护
适用于后台程序


### **std::async**
参数传入方式，引用，非引用
#### ***std::lunch***

#### ***std::packaged_task***
### ***std::promise***

### ***std::future exception***


exception 可以存储到 `std::future` 中，
同时`std::promise()` 调用 `set_value()`来存储异常

### ***std::shared_future***



