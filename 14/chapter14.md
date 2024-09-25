# 十四章 重载运算与类型转换

## 一、运算符重载

1. **基本概念**

   执行`a+b`其实是隐形执行了`operator+(a,b)`,隐形调用了一个函数

   a作为成员函数的时候执行运算符时，函数自带一个`this`指针，因此函数只需要一个参数

   ```cpp
   StrVec& StrVec::operator=(const StrVec&s){
       if(&s!=this){
           auto newdata=alloc_n_copy(s.begin(),s.end());
           free();
           element=newdata.first;
           first_free=newdata.second;
       }
       return *this;
   }
   ```

   需要多个参数并且需要本身参数时。需要用到友元函数。例如：

   ```cpp
   friend std::ostream& operator<<(std::ostream&os,const StrVec &s){
       for(size_t i=0;i<s.size();i++){
           os<<s[i]<<" ";
       }
       return os;
   }
   ```

2. **不能重构的运算符**

   `::` `.*` `.` `?:`

3. **输入输出运算符**

   ```cpp
   //重载<<
   std::ostream &operator<<(std::ostream &os,const StrVec &s){
       for(size_t i=0;i<s.size();i++){
           os<<s[i]<<" ";
       }
       return os;
   }
   
   //重载>>
   std::istream &operator>>(std::istream &is, StrVec &s){
       std::string t;
       is>>t;
       if(is) s.push_back(t);
       else s=StrVec();
       return is;
   }
   ```

4. **相等运算符**

   ```cpp
   bool operator==(const StrVec& lhs,const StrVec& rhs){
       if(lhs.size()!=rhs.size()) return false;
       for(size_t i=0;i<lhs.size();i++){
           if(lhs[i]!=rhs[i]) return false;
       }
       return true;
   }
   ```

5. **赋值运算符**

   ```cpp
   StrVec& StrVec::operator=(const StrVec&s){
       if(&s!=this){
           auto newdata=alloc_n_copy(s.begin(),s.end());
           free();
           element=newdata.first;
           first_free=newdata.second;
       }
       return *this;
   }
   ```

6. **下标运算符**

   ```cpp
   std::string& operator[](size_t index) {
       return element[index];  // 返回元素的引用
   }
   const std::string& operator[](size_t index) const {
       return element[index];  // 返回元素的常量引用（用于 const 对象）
   }
   ```

## 二、function库

**function**可以用来绑定函数：

```cpp
#include <functional>
#include <iostream>

void print(int x) {
    std::cout << x << std::endl;
}

int main() {
    std::function<void(int)> func = print;
    func(5); // 输出 5
    return 0;
}
```

## 三、类型转换

1. **类型转换符**

   一般形式：

   ```cpp
   operator type() const
   ```

   例子：

   ```cpp
   class SmallInt{
   pubilc:
       SmallInt(int i=0): val(i){
   		if(i<0||i>255) throw std::out_or_range("bad");
       }
       operator int() cosnt {return val;}
   private:
       std::size_t val;
   };
   
   int main(){
        Smallint si;
        si=4;//4被隐式转换成Smallint ,然后给构造函数
        si+3;//si隐式转换成int
   }
   ```

2. **explicit关键字**

   隐式类型转换有可能带来问题，因此c11引入了explicit关键字，可以避免隐式转换。

   ```cpp
   Smallint si=3;
   si+3;//错误，声明了explicit后无法隐式转换
   static_cast<int>(si) +3;//正确
   ```

   

3. **static_cast**

   在c中类型转换一般直接

   `（type）变量`来达到类型转换

   c++需要通过`static_cast<type> 变量`来执行类型转换。







 