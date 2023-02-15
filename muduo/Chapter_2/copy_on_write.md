```c++
g_foos.reset(new FooList(*g_foos))
```

# what does this mean ?

for example, if there are four threads, one is trying to use the function `post()`
the other three are trying to use the function `traverse()`

so the *use_count* of shared_ptr instances pointing to the current FooList object is 4.
after the execution of `g_foos.reset(new FooList(*g_foos))`, the *use_count* reduces to 3. And, here is the critical part: A new shared pointer pointing to a new copyed FooList has also created which has a *use_count* of 1 and named g_foos.
Remember that the object g_foos pointing to is now has the same content but different address.

the other three threads will continuously traverse the 'old' FooList, and when they all finished. the *use_count* of shared_ptr instances pointing to the 'old' FooList object reduces to 0 which cause the destruction of the old FooList. And the new FooList become the old FooList.