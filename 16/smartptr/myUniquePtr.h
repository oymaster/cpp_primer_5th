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