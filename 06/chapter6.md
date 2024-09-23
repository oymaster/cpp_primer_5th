# 函数

## 一、const和函数

### 类型

1. **常量函数参数**（const参数）

   ```cpp
   void printMessage(const std::string& message) {
       // message 是 const 的，不能被修改
       std::cout << message << std::endl;
   }
   ```

2. **常量成员函数**（const成员参数）

   ```cpp
   class MyClass {
   public:
       int getValue() const {
           return value; // 该函数不能修改成员变量
       }
   private:
       int value = 42;
   };
   ```

3. **返回常量对象**（const返回类型）

   ```cpp
   const std::string& getName() const {
       return name;
   }
   ```

4. **常量指针与常量数据**（const指针）

   指向常量的指针：指针指向的对象不可修改。

   ```
   cpp复制代码void doSomething(const int* ptr) {
       // *ptr 是 const 的，不能修改
       // ptr 本身可以改变
   }
   ```

   常量指针：指针本身不可修改。

   ```
   cpp复制代码void doSomething(int* const ptr) {
       // *ptr 可以修改
       // ptr 本身不能修改
   }
   ```

   常量指向常量的指针：指针和数据都不可修改。

   ```
   cpp复制代码void doSomething(const int* const ptr) {
       // *ptr 和 ptr 都是 const 的
   }
   ```

### 总结

* `const` 用在函数参数：参数不可修改。

* `const` 用在成员函数后：函数不能修改类的成员变量。

* `const` 用在返回类型：返回的值不可修改。

* `const` 用在指针上：可以限定指针或指针指向的数据是否可修改。



## 二、