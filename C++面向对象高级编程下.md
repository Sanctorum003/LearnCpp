# conversion function(转换函数)
```cpp
operator TypeName() const
{}
```

## non-explicit one argument constructor(转换构造函数)
* 能通过一个实参调用的构造函数定义了一条从构造函数的参数类型向类类型隐式转换的规则

```cpp
Sales_data(std::string s) : Sales_data(s,0,0){} // 可以隐式(stirng -> Sales_data)
Sales_data(std::istream &is) : Sales_data(){read(is,*this)} // 可以隐式（cin(istream) -> Sales_data）
```

## explicit one argument constructor(抑制构造函数定义的隐式转换)
* 详细见C++复习 explicit

* 关键字 <font color = red>explicit</font>

* 只能在类内的单个形参的构造函数前使用

* 并且explicit声明的构造函数只能用于直接初始化而不能用于拷贝初始化

```cpp
Sales_data item1(null_book); //true
Sales_data item2 = null_book; //error
```

* explicit 使得构造函数不能用于隐式变换，但仍可以显式变换

```cpp
item.combine(Sales_data(null_book));
item.combine(Static_cast<Sales_data>(cin));
```

# 仿指针(pointer-like classes)
* 伪指针(pointer-like classes)是指作用类似于指针的对象,实现方式是重载*和->运算符.
## 智能指针

* 标准库中的shared_ptr类是一个典型的伪指针类,代码如下:

```cpp
mplate<class T>
class shared_ptr {
public:
    T& operator*() const {		// 重载 * 运算符
        return *px;
    }

    T *operator->() const {		// 重载 -> 运算符
        return px;
    }
    //...
    
private:
    T *px;
    // ...
};
```

```cpp
int *px = new Foo;
shared_ptr<int> sp(px);

func(*sp);			// 语句1: 被解释为 func(*px)
sp -> method();		// 语句2: 被解释为 px -> method()
```
* 对于语句1,形式上解释得通,重载运算符*使得func(*sp)被编译器解释为func(*px)

* 对于语句2,形式上有瑕疵,重载运算符->使得sp ->被编译器解释为px,这样运算符->就被消耗掉了.
    - 而对于C++来说,箭头符号作用下去会一直作用下去，不会被消耗掉

***
## 迭代器
* 标准库中的迭代器_List_iterator也是一个伪指针类,代码如下:

```cpp
template<class _Tp, class Ref, class Ptr>
struct _List_iterator {
    _List_iterator& operator++() { ...	}
    _List_iterator operator++(int) { ...	}
    _List_iterator& operator--(){ ...	}
    _List_iterator operator--(int)  { ...	}
    bool operator==(const _Self &__x) { ... }
    bool operator!=(const _Self &__x) { ... }
    Ref operator*() { ...	}
    Ptr operator->() { ...	}
};
```
* _List_iterator除了重载*和->运算符之外,还重载了原生指针的其他运算符.

# 仿函数(function-like classes)
* 伪函数(function-like classes)是指作用类似于函数的对象,实现方式是重载()运算符,标准库中的几个伪函数如下:

```cpp
template<class T>
struct identity {
    const T &
    operator()(const T &x) const { return x; }
};

template<class Pair>
struct select1st {
    const typename Pair::first_type &
    operator()(const Pair &x) const { return x.first; }
};

template<class Pair>
struct select2nd {
    const typename Pair::second_type &
    operator()(const Pair &x) const { return x.second; }
};
```
* class里面没有数据也要占用1字节

# 成员模板
* 成员模板用于指定成员函数的参数类型:

```cpp
//例子:pair 拷贝构造函数.
template<class T1, class T2>
struct pair {
    typedef T1 first_type;
    typedef T1 second_type;

    T1 first;
    T2 second;

    pair() : first(T1()), second(T2()) {}
    pair(const T1 &a, const T2 &b) : first(a), second(b) {}

    template<class U1, class U2>
    pair(const pair<U1, U2> &p) :first(p.first), second(p.second) {}
}

pair<Derived1, Derived2> p1;	// 使用子类构建对象
pair<Base1, Base2> p2(p1);		// 将子类对象应用到需要父类的参数上
```

```cpp
//智能指针 向上转型
template<tyname _Tp>
class shared_ptr : public __shared_ptr<_Tp>
{
...
    template<typename _Tp1>
    explicit shared_ptr(_Tp1* __p):__shared_ptr<_Tp>(__p){}
...
};

Based1* ptr = new Derived1; //up-cast
shared_ptr<Base1> sptr(new Derived1);//模拟 up-cast
```
* 成员模板常用于类模板的拷贝构造函数(父类与子类之间)和向上转型

## 模板(全)特化
* 模板特化用来部分针对某些特定参数类型执行操作:

```cpp
//下面代码实现针对char、int和long这三个数据类型使用指定代码创建对象,其它数据类型使用默认的泛化操作创建对象.
template<class Key>
struct hash {
    // ...
};

template<>
struct hash<char> {
    size_t operator()(char x) const { return x; }
};

template<>
struct hash<int> {
    size_t operator()(char x) const { return x; }
};

template<>
struct hash<long> {
    size_t operator()(char x) const { return x; }
};
```

### 模板偏特化 -- 个数的偏
* 指定部份参数类型
    - 偏特化必须从左到右绑定,不能绑定

```cpp
template<typename T, typename Alloc>
class vector{
// ...  
};

template<typename Alloc>
class vector<bool, Alloc>{	// 指定了第一个参数类型
// ...  
};
```


### 模板偏特化 -- 范围的偏
* 缩小参数类型的范围
    - 例如:从任意类型特化到任意指针类型

```cpp
template<typename T>
class C{
// 声明1...  
};

template<typename T>
class C<T*>{	// 指定了参数类型为指针类型
// 声明2...  
};

C<string> obj1;		// 执行声明1
C<string*> obj2;	// 执行声明2
```

## 模板模板参数
* 模板模板参数是指模板的参数还是模板的情况

```cpp
template<typename T, template<typename U> class Container>
class XCls {
private:
    Container<T> c;
public:
    // ...
};
```
* 在上面例子里,`XCls`的第二个模板参数`template<typename U> class Container`仍然是个模板,因此可以在类声明内使用`Container<T> c`语句对模板`Container`进行特化,使用方式如下:

```cpp
XCls<string, list> mylst1;	// mylst1的成员变量c是一个list<string>
```
* 上面语句构造的mylst1变量的成员变量c是一个特化的类list<string>.仅从模板模板参数的语法来说,上面语句是正确的,但是实际上不能编译通过,因为list模板有2个模板参数,第二个模板参数通常会被省略,但在类声明体内不能省略其他模板参数,因此可以使用using语法达到目的:

```cpp
template<typename T>
using LST = list<T, allocator<T>>

XCls<string, list> mylst2;	// mylst2的成员变量c是一个list<string>
```
* 这样就能够编译通过了,mylst2的成员变量c是一个特化的list<string>
***
* 下面这种情况不属于模板模板参数:
```cpp
template<class T, class Sequence=deque<T>>
class stack {
    friend bool operator== <>(const stack &, const stack &);
    friend bool operator< <>(const stack &, const stack &);

protected:
    Sequence c; // 底层容器
	// ...
};
```
* 上面例子中`stack`类的第二模板参数`class Sequence=deque<T>`不再是一个模板,而是一个已经特化的类,在实现特化stack的时候需要同时特化`class Sequence=deque<T>`的模板参数.
  
```cpp
stack<int> s1;				
stack<int, list<int>> s2;	// 特化第二模板参数时应传入特化的类而非模板
```
* 在上面的例子中s2在特化时第二模板参数被设为`list<int>`,是一个特化了的类,而非模板参数,实际上如果愿意的话,甚至可以将第二模板参数设为`list<double>`,与第一模板参数T不同,也能编译通过;而模板模板参数就不能这样了,模板模板参数的特化是在类声明体中进行的,类声明体里制定了使用第一模板参数来特化第二模板参数.
    - 即`clas T`和`class Sequence=deque<T>`是两个泛化,在只传入一个参数类型的时候,连个T一样.但也可以传入两个不同类型的参数.

