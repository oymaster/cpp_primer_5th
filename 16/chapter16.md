# 第十六章 模板与泛型编程

## 一、模板

### 1.定义

* **函数模板** 

  函数模板允许定义一个通用的函数，它可以接受任意类型的参数。具体类型在函数调用时由编译器推导或指定。

* **类模板**

  类模板允许定义一个通用的类，它的成员函数和数据成员可以根据类型参数的不同而表现不同。

### 2.作用

* **泛型编程**： 模板允许编写能够适应多种数据类型的代码，这减少了重复代码的编写。比如，你可以使用同一个 `add` 函数处理 `int`、`double` 或 `float` 类型的数据，而不需要为每种类型单独编写一个 `add` 函数。
* **代码复用**： 模板能够极大地提高代码的复用性。通过模板，可以创建通用的容器（如 `vector`、`list`），算法（如 `sort`、`swap`）等，使用时只需要提供类型参数。
* **类型安全**： 虽然模板提供泛型编程的能力，但在编译时会进行类型检查，因此模板代码仍然是类型安全的。编译器根据模板参数实例化具体的类型，并检查操作是否符合该类型的要求。
* **性能优化**： 模板在编译时进行实例化，相比于运行时的多态机制（如虚函数），它能够带来更好的性能，因为函数和类模板是根据具体类型在编译时生成的。

### 3.注意点

* 当在模板类中定义友元模板函数时，因为在类中已经知道了模板实参，所以有的成员函数可以不需要指定模板参数

  例如：

  ```cpp
  template<typename T> 
  class Vec{
  public:
      Vec():element(nullptr),first_free(nullptr),cap(nullptr){}
      Vec(const Vec&);
      Vec(Vec &&s) noexcept:element(s.element),first_free(s.first_free),cap(s.cap){
          s.element=s.cap=s.first_free=nullptr;
      }
      Vec& operator=(const Vec&);
      Vec& operator=(Vec &&) noexcept;
      
      friend bool operator== (const Vec& lhs,const Vec& rhs)；
  };
  ```

  上面的构造函数声明中，可以不需要指定出`Vec<T>`,但是友元函数不指定的话，无法分辨是正常函数还是模板函数。

  ```cpp
  friend bool operator== (const Vec& lhs,const Vec& rhs)；//无法判断
  ```

  一般可以用两种方法

  * **直接定义**（**更推荐**）

    在类里面直接定义出该友元函数的内容：

    ```cpp
    friend bool operator== (const Vec& lhs,const Vec& rhs){
        if(lhs.size()!=rhs.size()) return false;
        for(size_t i=0;i<lhs.size();i++){
            if(lhs[i]!=rhs[i]) return false;
        }
        return true;
    }
    ```

  * **前向声明**

    ```cpp
    template<typename T> class Vec;
    
    // 前向声明友元函数
    template<typename T>
    bool operator== (const Vec<T>& lhs, const Vec<T>& rhs);
    
    template<typename T>
    class Vec {
        // 省略其他代码...
    public:
        // 声明友元模板函数
        friend bool operator== <>(const Vec<T>& lhs, const Vec<T>& rhs);
    };
    ```

    

## 二、引用折叠

* X& &、X& &&、X&& &折叠成类型X&
* 类型X&& && 折叠成X&&

## 三、转发

假设我们需要写一个反转的模板函数，将两个变量转换位置输出

```cpp
template <typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2) {
    f(t2, t1); // 这里没有 std::forward
}
```

假如：

```cpp
int x = 42;
flip([](int&& a, int&& b) { /*...*/ }, std::move(x), 100);
```

`T1` 被推导为 `int&&`，因为我们使用了 `std::move(x)`（这是一个右值）。

`T2` 被推导为 `int`，因为 `100` 是一个右值。

但在 `f(t2, t1)` 这行代码中：

* `t2` 和 `t1` 是函数内部的变量，在调用 `f` 时，它们都是**左值**，即使它们的实际类型是右值引用或右值。
* 所以，在没有使用 `std::forward` 的情况下，传递给 `f` 的 `t2` 和 `t1` 都会被当作**左值**。

因此，即使 `t1` 本来是右值，它也会被当作左值传递给 `f`。如果 `f` 的参数期望右值引用（比如 `int&&`），这可能导致编译错误或不符合预期的行为。



为了保持传递的值类别（左值或右值），我们需要使用 `std::forward`：

```cpp
template <typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2) {
    f(std::forward<T2>(t2), std::forward<T1>(t1));  // 保留传递的值类别
}
```



## 四、可变参数模板

```cpp
template<typename T,typename... Args>
void foo(const T &t,const Args ...rest);
```

Args为模板参数包，rest为函数参数包

```cpp
template<typename ... Args> void g(Args ... args) {
	cout << sizeof...(Args) << endl; // 模板参数包的数量
	cout << sizeof...(args) << endl; // 函数参数包的数量
}
```



