# Overview


|  | value | const value | non-const reference | const reference |
| :----:| :----: | :----: | :----: | :----: |
| 是否是copy | 是 | 是 | 不是 | 不是 |
| 能否修改值 | 可以 | 不可以 | 可以 | 不可以 |
| 会不会反映到calling function中 | 不会 | 不会 | 会 | 不会（因为不能被修改） |




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