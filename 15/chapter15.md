# 面向对象程序设计

## 一、概述

### 1.什么是类和对象

**类** 是对一组对象的抽象描述，而 **对象** 是类的实例。

以**animal**为例：

```cpp
class Animal {
private:
    double weight;
    double height;
public:
    virtual void speak(){ //虚函数，支持重写
        std::cout << "Animal sound" << std::endl; 
    }
};
```

上述是个简单的**animal**类例子，在**animal**动物中，都会有身高体重属性，还有普遍的行为，也就是会叫`speak`

在动物类中，比如说狗，和猫，它们均是动物，是动物类下的分支，但猫和狗两大类又有不同

猫和狗都会继承动物类的属性和行为，均有身高体重属性，和都会叫

```cpp
class Dog : public Animal {
public:
    void speak() override { 
        std::cout << "Woof!" << std::endl; 
    }
};

class Cat : public Animal {
public:
    void speak() override { 
        std::cout << "Meow!" << std::endl; 
    }
};
```

但他们叫的方式不同，也就是同一个行为下的重写override

以上都是类，还是抽象的。

```cpp
Dog hask；//一个对象（实例），属于狗类，还属于动物大类，会狗叫
Cat qq；//一个对象（实例），属于猫类，还属于动物大类，会猫叫
```

## 二、基类和派生类（继承）

在章节一中的例子中，基类就是Animal类，派生类就是Cat，Dog。

通过类派生列表来指定继承了哪些类，通常继承一个类，也可以继承多个类，比如**体育老师**可以继承**体育类**和**老师类**。

```cpp
class 体育老师 : public 体育,public 老师 {}；
```

### 1.继承类型

**访问权限**

* **public**：公共成员可以被任何其他代码访问，包括类的外部代码和派生类。
* **protected**：受保护成员只能被类的成员函数、友元函数和派生类的成员函数访问，但不能被类的外部代码访问。
* **private**：私有成员只能被类的成员函数和友元函数访问，无法被外部代码或派生类的成员函数访问。

**继承权限**

* **public** 继承：基类的 `public` 成员和 `protected` 成员在派生类中保持其访问权限，`private` 成员不可访问。
* **protected** 继承：基类的 `public` 和 `protected` 成员在派生类中变为 `protected`，而 `private` 成员仍不可访问。
* **private** 继承：基类的 `public` 和 `protected` 成员在派生类中变为 `private`，而 `private` 成员仍不可访问。

### 2.继承内容

* 非私有的成员变量（`protected`和`public`成员）。
* 非私有的成员函数（包括虚函数）。
* 静态成员变量和静态成员函数（非私有的）。
* 派生类不会继承构造函数、析构函数、私有成员、友元关系。

### 3.切片问题

切片主要发生在处理对象的复制时，尤其是当涉及到基类和派生类的对象时。切片指的是当一个派生类对象被赋值给基类对象时，派生类特有的数据和行为被丢弃，只保留基类部分。

```cpp
class Base {
public:
    virtual void show() const { std::cout << "Base class" << std::endl; }
};

class Derived : public Base {
public:
    void show() const override { std::cout << "Derived class" << std::endl; }
    void derivedMethod() const { std::cout << "Derived method" << std::endl; }
};

int main() {
    Derived d; // 创建派生类对象
    Base b = d; // 发生切片
    b.show(); // 输出 "Base class"
    // b.derivedMethod(); // 编译错误：b没有derivedMethod
    return 0;
}
```

在上面的例子中，当我们将 `Derived` 类型的对象 `d` 赋值给基类对象 `b` 时，`d` 的信息（如 `derivedMethod`）被切片掉，`b` 只保留 `Base` 部分。

## 三、虚函数

### 1.什么是虚函数

以Animal类为例，当派生类需要重写基类的某个函数时，可以将函数定义为虚函数，以此实现多态性。

关键字为`virtual`

```cpp
virtual void speak();
```

而派生类可以定义同名函数实现不同内容通过`override`（可以不写，但最好写上）

```cpp
void speak() override;
```

### 2.注意点

* 基类通常都应该定义应该虚析构函数，即使不执行任何操作

* 虚函数可以与默认实参一起使用，但注意，如果在派生类中重写了函数，默认实参将以派生类的参数为准。

  例如：

  ```cpp
  class Base {
  public:
      virtual void display(int x = 10) {  // 虚函数，带有默认实参
          cout << "Base class: x = " << x << endl;
      }
  };
  
  class Derived : public Base {
  public:
      void display(int x = 20) override {  // 派生类重写虚函数，并设置不同的默认实参
          cout << "Derived class: x = " << x << endl;
      }
  };
  
  int main() {
      Base* basePtr = new Derived();  // 基类指针指向派生类对象
      basePtr->display();  // 调用的是Derived::display，但默认实参是Base类的
      delete basePtr;
      return 0;
  }
  ```

* 虚函数应在基类中定义，普通虚函数有默认实现，纯虚函数要求派生类实现。

  纯虚函数一般形式：

  ```cpp
  virtual 返回类型 函数名()=0；
  ```

## 四、动态绑定

### 1.定义

**动态绑定**（Dynamic Binding）是面向对象编程中实现多态性的重要机制。它允许程序在**运行时**根据对象的实际类型选择合适的函数实现，而不是在编译时决定。这种机制使得继承和虚函数的使用更加灵活。

例如：

```cpp
Animal* myDog = new Dog();
Animal* myCat = new Cat();

myDog->speak(); // 输出 "Woof!"
myCat->speak(); // 输出 "Meow!"

delete myDog; // 记得释放内存
delete myCat;
```

上面的例子中，`myDog` 和 `myCat` 的 `speak` 方法调用是动态绑定的。

如果我们在 `Animal` 类中没有将 `speak` 声明为虚函数，那么即使使用基类指针，调用的也会是 `Animal` 类的 `speak` 方法，而不是派生类的实现。这就是动态绑定的好处。

### 2.静态绑定和动态绑定

* **静态绑定**（Static Binding）：也叫**早绑定**，是在编译时根据变量的声明类型决定调用哪个函数。例如，普通的非虚函数就是静态绑定。
* **动态绑定**（Dynamic Binding）：也叫**晚绑定**，是在运行时根据对象的实际类型决定调用哪个函数。虚函数的调用通过动态绑定实现。

### 3.实现条件

* **虚函数**：函数必须在基类中被声明为`virtual`。
* **指针或引用**：调用函数时，必须通过指向基类的**指针**或**引用**来实现。
* **派生类重写**：派生类中必须重写基类的虚函数。

### 4.工作原理

C++通过虚函数表（**vtable**）实现动态绑定。当一个类包含虚函数时，编译器会为每个类维护一个虚函数表，表中记录了该类及其派生类所实现的所有虚函数的地址。每个对象还会有一个指向其所属类的虚函数表的指针，称为**虚指针**（vptr）。当通过基类指针调用虚函数时，程序会通过虚指针查找对象的实际类型，并从虚函数表中找到正确的函数实现。

## 五、其他

代码：

```cpp
static bool compare(const std::shared_ptr<Quote>& lhs, 
                    const std::shared_ptr<Quote>& rhs) {
    return lhs->isbn() < rhs->isbn();
}
std::multiset<std::shared_ptr<Quote>, decltype(&compare)> items{&compare};
```

自定义比较函数

`set`，`map`这种需要自定义比较规则的时候，传入的应该是可调用的对象

例如新建类，或者类里面重构，并传入这个类。

如果是普通的函数，需要传入这个函数指针，并指名函数指针的类型，避免类型混淆（特别是在运用模板中），同时还需要在后面添加一个实例

而通过类的对象传参，则不需要在后面添加这个实例。

如果普通函数不添加这个实例，则容器在初始化构造的时候，调用的还是默认的比较函数，容器需要一个实例去初始化。

```cpp
struct compare {
    bool operator()(const std::shared_ptr<Quote>& lhs, 
                    const std::shared_ptr<Quote>& rhs) const {
        return lhs->isbn() < rhs->isbn(); // 按 ISBN 排序
    }
};
std::multiset<std::shared_ptr<Quote>,compare> items；
```

上述例子就不需要指定函数指针，也不需要添加实例参数。
