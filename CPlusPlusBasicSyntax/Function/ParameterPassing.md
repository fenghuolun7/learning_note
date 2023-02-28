# Overview


|  | value | const value | non-const reference | const reference |
| :----:| :----: | :----: | :----: | :----: |
| 是否是copy | 是 | 是 | 不是 | 不是 |
| 能否修改值 | 可以 | 不可以 | 可以 | 不可以 |
| 会不会反映到calling function中 | 不会 | 不会 | 会 | 不会（因为不能被修改） |


# Pass by value
```c++
Creature(std::string name) : m_name{std::move(name)} { }
```

A passed lvalue is copied into name, then is moved into m_name.

A passed rvalue is moved into name, then is moved into m_name.

The pass-by-value approach has the advantage that you only need to maintain one function but you pay for this with performance. It depends on your application whether this maintenance advantage outweighs the loss in performance.

https://stackoverflow.com/questions/21035417/is-the-pass-by-value-and-then-move-construct-a-bad-idiom


在c++11 之后的任何版本，应该遵循如下准则：
```c++
bar(foo f); // want to obtain a copy of f
bar(const foo& f); // want to read f
bar(foo& f); // want to modify f
```

# 传入引用与传入指针的优劣
```c++
void modifies(T &param);
// vs
void modifies(T *param);
```

## 传入指针
### 调用：
```c++
call(&obj)
```

### 优点：
语义清晰

### 缺点：


## 传入引用
### 调用：
```c++
call(&obj)
```

### 优点：

### 缺点：


# copy elision
https://www.zhihu.com/question/57048704/answer/151446405