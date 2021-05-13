# C++编程简介
# 头文件与类的声明

## 基于对象与面向对象
* Object Based:面向的是单一class的设计
* Object Oriented:面向的是多重classes的设计,classes与classes之间的关系

## class的两个经典分类
* class without pointer member(s)
> complex

* class with pointer member(s)
> string

## Header(头文件)中的防卫式声明
```cpp
//complex.h
# ifndef __COMPLEX__
# define __COMPLEX__

//...

# endif
```

### include gurad 和 pragma once
* #pragma once不是c++标准的一部分,但是现代编译器普遍支持.比include gurad快一点点,而且声明简单,不容易出错.

参考:
> [#pragma once vs include guards? [duplicate]](https://stackoverflow.com/questions/1143936/pragma-once-vs-include-guards)

> [在 C++ 中防止头文件被重复包含时为什么同时使用 #ifndef 和 #pragma once？](https://www.zhihu.com/question/40990594)

# 构造函数
## inline
* 见C++复习 inline

## 访问级别(acess level)
* public,private,protected.

## 构造函数
### 初始化列表
* 见C++复习 成员初始化列表

### 重载
* 重载函数需要函数签名不一样（函数名，参数）

```cpp
//调用时存在二义性，不可以同时存在
complex(double r = 0,double i = 0) : re(r),im(i){}
complex():re(0),im(0);
```

# 参数传递与返回值