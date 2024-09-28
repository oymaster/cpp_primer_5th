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