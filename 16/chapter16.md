# 第十六章 模板与泛型编程

## 一、模板

### 1.定义

### 2.作用

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

    

## 二、

## 三、

## 四、

## 五、其他