# 模板偏特化：

## 在模板偏特化过程中，只有在模板列表中定义了形参， 才可以使用。
错误示例：
```c++
template <>
struct is_reference<T> : public false_type {};
```
***error: identifier "T" is undefined***

正确示例：
```c++
template <typename T>
struct is_reference<T> : public false_type {};
```

    
## 在模板偏特化过程中，主模板与特化版本的模板参数类型与数量一致
错误示例：
```c++
// 1
template <typename T>
struct is_reference {};

// 2
template <typename T>
struct is_reference<T> : public false_type {};
```
***error: a template argument list is not allowed in a declaration of a primary template***

注意以下不会报错：
```c++
// 1
template <typename T>
struct is_reference {};

// 3
template <typename T>
struct is_reference<T&> : public true_type {};
```

因为 1 与 2 本质是一样的，2 中 模板的特化还是 T。

正确示例：
```c++
template <typename T>
struct is_reference : public false_type {};
```

1 与 2 可以 合并为一个主模板

## 在模板偏特化过程中，模板模板的参数列表与实际传入的不匹配
错误示例：
```c++
template <template <typename T> typename Tmpl, typename... Args>
// here
struct is_instantiation_of<Tmpl<Args...>, Args...> : public true_type{};
```
不会报错，但是不规范，容易引起歧义

正确示例：
```c++
template <template <typename... > typename Tmpl, typename... Args>
// here
struct is_instantiation_of<Tmpl<Args...>, Args...> : public true_type{};
```

## 被传入参数的模板模板是类型，而不再是模板模板
错误示例：
```c++
// here
template <template <typename T> typename Tmpl, typename... Args>
struct is_instantiation_of : public false_type{};

template <template <typename T> typename Tmpl, typename... Args>
struct is_instantiation_of<Tmpl<Args...>, Args...> : public true_type{};
```

***error: class "Tmpl<Args...>" is not a class template***

正确示例：
```c++
template <typename T, typename... Args>
struct is_instantiation_of : public false_type{};

template <template <typename T> typename Tmpl, typename... Args>
struct is_instantiation_of<Tmpl<Args...>, Args...> : public true_type{};
```

## 特化版本的模板形参数量和类型不一定要与主模板一致
正确示例：
```c++
template <typename T, typename... Args>
struct abc : public true_type{};

template <template <typename T> typename Tmpl, typename... Args>
struct abc<Tmpl<Args...>, Args...> : public true_type{};
```

即使形参数量和类型不一致，只要形参组合成的实际特化实参符合主模板的数量和类型，就能够实现功能

## 别名（aliases）模板需要和主模板完全一致， 包括默认模板参数。
错误示例：
```c++
template <bool, typename T = void>
struct enable_if : type_identity<T> {};

template <bool B, typename T>
using enable_if_t = enable_if<B, T>::type;
```
***error: too few arguments for alias template "enable_if_t"***
正确示例：
```c++
template <bool, typename T = void>
struct enable_if : type_identity<T> {};

template <bool B, typename T = void>
using enable_if_t = enable_if<B, T>::type;
```