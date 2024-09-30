# 第十六章 实现智能指针

## 一、实现shared_ptr

```cpp
#ifndef MY_SHARED_PTR
#define MY_SHARED_PTR

#include<iostream>
#include<functional>

template <typename T>
class mySharedPtr{
private:
    T *ptr;
    std::function<void(T*)> deleter;
    int *ref_count;
    //释放资源
    void release(){
        if(--(*ref_count)==0){
            if(deleter) deleter(ptr);
            else{
                std::cerr<<"mySharedPtr default delete\n";
                delete ptr;
            }
            delete ref_count;
        }
    }
public:
    //默认构造
    explicit mySharedPtr(T *p,std::function<void(T*)>d = nullptr): ptr(p),ref_count(new int(1)),deleter(d){}
    //拷贝构造
    mySharedPtr(const mySharedPtr &other):ptr(other.ptr),ref_count(other.ref_count),deleter(other.deleter){
        ++(*ref_count);
    }
    //赋值
    mySharedPtr& operator=(const mySharedPtr&other){
        if(this!=&other){
            release();//先释放自己的资源，避免内存泄漏
            ptr=other.ptr;
            ref_count=other.ref_count;
            deleter=other.deleter;
            //sharedptr不需要清空other的内容，他们需要共享指针和引用计数

            ++(*ref_count);

        }            
        return *this;
    }
    //移动构造
    mySharedPtr (mySharedPtr && other) noexcept :ptr(other.ptr),ref_count(other.ref_count),deleter(other.deleter){
        other.ptr=nullptr;
        other.ref_count=nullptr;
    }
    //移动赋值
    mySharedPtr& operator=(mySharedPtr && other) noexcept{
        if(this!=&other){
            //防止内存泄漏
            release();
            ptr==other.ptr;
            ref_count=other.ref_count;
            deleter=other.deleter;
            //移动赋值需要清空other，因为此时是把所有资源转移了
            other.ptr=nullptr;
            other.ref_count=nullptr;
        }
        return *this;

    }
    ~mySharedPtr(){
        release();
    }
    //加个const防止修改本对象的指针
    T *get() const {return ptr;}
};


#endif
```



## 二、实现unique_ptr

```cpp
#ifndef MY_UNIQUE_PTR
#define MY_UNIQUE_PTR

#include<iostream>
#include<functional>

template<typename T>
class myUniquePtr
{
private:
    T *ptr;
    std::function<void(T *)> deleter;
public:
    //默认构造
    explicit myUniquePtr(T *p,std::function<void(T*)>d = nullptr): ptr(p),deleter(d){}
    //禁止拷贝构造
    myUniquePtr(const myUniquePtr &)=delete;
    //禁止赋值
    myUniquePtr& operator=(const myUniquePtr&) = delete;
    //移动构造
    myUniquePtr (myUniquePtr && other) noexcept :ptr(other.ptr),deleter(other.deleter){
        other.ptr=nullptr;
    }
    //移动赋值
    myUniquePtr& operator=(myUniquePtr && other) noexcept{
        if(this!=&other){
            //防止内存泄漏
            if(deleter) deleter(ptr);
            else delete ptr;
            
            ptr=other.ptr;
            deleter=other.deleter;
            other.ptr=nullptr;
        }
        return *this;

    }
    ~myUniquePtr(){
        if(deleter) deleter(ptr);
        else {
            std::cerr<<"myUniquePtr default delete\n";
            delete ptr;
        }
    }
    //加个防止修改本对象的指针
    T *get() const {return ptr;}
};


#endif
```



## 三、debugDelete删除器

```cpp
#include <iostream>
#ifndef DEBUG_DELETE
#define DEBUG_DELETE

class debugDelete{
private:
    std::ostream& os;
public:
    debugDelete(std::ostream& s=std::cerr):os(s){}
    template<typename T>
    void operator() (T *p) const {
        os<<"debug delete\n";
        delete p;
    }
};

#endif
```



## 四、测试

```cpp
#include<iostream>
#include"mySharedPtr.h"
#include"myUniquePtr.h"
#include"debugDelete.h"

using std::cout;
using std::cin;
using std::endl;

int main(){
    // 测试 myUniquePtr
    {
        myUniquePtr<int> up1(new int(42), debugDelete());
        myUniquePtr<int> up2(new int(100));

        cout << "Value in up1: " << *up1.get() << endl;

        up2 = std::move(up1);  // 移动赋值,此时up1被清空，但暂时不会销毁，作用域结束再销毁
        cout << "Value in up2 after move: " << *up2.get() << endl;
    } // up1,up2 会在这里被销毁，DebugDelete 会被调用

    // 测试 mySharedPtr
    {
        mySharedPtr<int> sp1(new int(42));
        mySharedPtr<int> sp2(sp1); // 拷贝构造
        mySharedPtr<int> sp3(new int(100), debugDelete());
        mySharedPtr<int> sp4=sp3;

        cout << "Value in sp1: " << *sp1.get() << endl;
        cout << "Value in sp2: " << *sp2.get() << endl;
        cout << "Value in sp3: " << *sp3.get() << endl;
        cout << "Value in sp4: " << *sp4.get() << endl;

        sp3 = sp1; // 赋值
        cout << "Value in sp3 after assignment: " << *sp3.get() << endl;
    } // 都在这里被销毁，sp1,sp2,sp3默认删除器会被调用,sp4使用debug，sp3因为后续被赋值成sp1了，所以删除器被更改
    //销毁顺序为栈，sp4->sp3->sp2->sp1
    return 0;
}
```

**输出：**

```cpp
Value in up1: 42
Value in up2 after move: 42
debug delete
debug delete
Value in sp1: 42
Value in sp2: 42
Value in sp3: 100
Value in sp4: 100
Value in sp3 after assignment: 42      
debug delete
mySharedPtr default delete
```

