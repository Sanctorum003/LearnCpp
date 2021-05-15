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
## 单列模式

```cpp
class A
{
public:
    static A& getInstance();
    setup(){...}
private:
    A();
    A(const A& rhs);
    ...
};

A& A::getInstance()
{
    static A a;
    return a;
}
```
## 常量成员函数
* 函数后面加const为量成员函数,该函数不改变成员变量.

* 常量对象只能调用常量成员函数.

## 参数传递(pass by value / pass by reference(to const))
* 引用在底层是用常量指针实现的.
> [c++中，引用和指针的区别是什么？](https://www.zhihu.com/question/37608201)

## 返回值传递(return by value / return by refernece(to const))
* 返回值在可以的情况下尽量返回引用
* 传递者无需知道接受者是以reference形式接受. 
* 可以连续赋值

```cpp
//连续赋值
c3 += c2 += c1;
```

## friend(友元)
* 见C++复习 friend友元

* 相同class的各个objects互为友元

```cpp
class complex
{
public:
    complex (double r = 0,double i = 0):re(r),ri(i){}

    //相同class的各个objects互为友元
    int func(const complex& param){return param.re + param.ri;}

private:
    double re,im;
}
```

# 操作符重载和临时对象
* 重载运算符函数的参数数量与该运算符作用的运算对象数量一样多
    - 所以每个可重载的运算符其函数形式确定不变.（比如+=为2元运算符，只能有两个变量，且第一个对应左边，第二个对应右边）
    - 对于有些运算符可以是一元可以是二元(+,-)，可以是前置也可以是后置(++,--)
## 成员操作符重载
* 所有的成员函数都隐藏一个this指针

```cpp
inline complex& complex::operator += (/*this ,*/const complex& r)
{
  return __doapl (this, r);
}
```

## 非成员操作符重载
```cpp
//注意这里返回的是局部变量，不能返回引用
inline complex operator + (const complex& x, const complex& y)
{
  return complex (real (x) + real (y), imag (x) + imag (y));
}
```
* typename()
> 创建匿名临时对象，声明周期在下一行就销毁

* << 输出运算符只能声明为非成员函数

```cpp
ostream& operator << (ostream& os,const complex x);

cout<<complex(1);
```

* <<操作符作用于左边的对象,如果写成成员函数,写法将会变成如下,与c++通用写法不一致.

```cpp
ostream& complex::operator << (ostream& os);

complex(1)<<os;
```

# 三大函数（拷贝构造，拷贝赋值，析构）

```cpp
String(const char* cstr=0);         //直接构造        
String(const String& str);          //拷贝构造
String& operator=(const String& str);         //拷贝赋值
~String();                          //析构
```

* strlen()不计算`\0`

* class with pointer members必须有拷贝构造和拷贝赋值

* alias（别名）

## 拷贝赋值函数
* 要检测自我赋值

```cpp
inline String& String::operator=(cons String& str)
{
    if(this = &str)
        return *this;//检测自我赋值

    delete[] m_data;
    m_data = new char[strlen(str.m_data)+1];
    strcpy(m_data,str.m_data);
    return *this;
}
```
# 堆栈和内存管理
* new出来的变量在离开作用域时，需要自己delete掉,不然会造成内存泄露

## new:先分配memory,再调用构造函数

```cpp
Complex* pc = new Complex(1,2);

//<=>

Complex* pc;
void* mem = operator new(sizeof(Complex));//分配内存，operator new其内部调用malloc(n)
pc = static_cast<Complex*>(mem);//类型转型
pc->Complex::Complex(1,2);//构造函数
```

## delete:先调用析构函数，再释放内存

```cpp
String* ps = new String("Hello");
delete ps;

//<=>

String::~String(ps); // 析构函数
operator delete(ps); // 释放内存，其内部调用free(ps)
```

* new 搭配 delete
* new[] 搭配 delete[]
> delete[]会调用多次析构函数，对于数组来说释放内存要delete每个对象.

* 对于动态内存分配的底层原理看CSAPPd第九章