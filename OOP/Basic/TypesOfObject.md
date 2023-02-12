# composition
对象 x 的生命周期由其owner控制。owner 析构的时候也随着析构。
```C++
class owner {
    X x = new x(); 
}
```

# association
A 类 用到了另一个对象 B, 调用了后者的成员函数。
A 持有对象 B 的指针（或引用）

两个有关联（ｈａｓ　ａ）
```C++
class A {
    B* b; 
}
```

# aggregation
是一类特殊的association
A 类 用到了另一个对象 B, 调用了后者的成员函数。
A 持有对象 B 的指针（或引用）
A 与Ｂ有逻辑上整体与部分的关系
例如　Computer　与　Monitor 