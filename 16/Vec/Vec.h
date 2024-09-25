#ifndef VEC_H
#define VEC_H

#include<memory>

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

    T& operator[](size_t index) {
        return element[index];  // 返回元素的引用
    }
    const T& operator[](size_t index) const {
        return element[index];  // 返回元素的常量引用（用于 const 对象）
    }
    friend std::ostream& operator<< (std::ostream& os, const Vec& s);
    Vec& operator+= (const Vec&);
    friend Vec& operator+ (const Vec&,const Vec&);
    friend bool operator== (const Vec& lhs,const Vec& rhs);
    friend bool operator!= (const Vec& lhs,const Vec& rhs);

    Vec(std::initializer_list<T> ilist);
    ~Vec();
    void push_back(const T&);
    void push_back(T &&);
    void pop_back();
    void reserve(size_t new_cap);
    void resize(size_t new_size){resize(new_size,"");}
    void resize(size_t new_size,const T &value);
    size_t size() const { return first_free-element;}
    size_t capacity() const { return cap-element; }
    T *begin() const { return element; }
    T *back() const {return first_free-1;}
    T *end() const { return first_free; }

private:
    void chk_n_alloc(){
        if(size()==capacity()) reallocate();
    }
    std::pair<T*,T*> alloc_n_copy
        (const T*,const T*);//创造一片新内存并将原Vec复制过去，并返回新首尾指针
    void free();
    void reallocate();//获得更多内存并拷贝已有的元素

private:
    std::allocator<T> alloc;
    T *element;//头指针
    T *first_free;//元素的尾指针
    T *cap;//数组尾指针
};

template<typename T>
void Vec<T>::push_back(const T &s){
    chk_n_alloc();
    alloc.construct(first_free++,s);
}

template<typename T>
void Vec<T>::push_back(T &&s){
    chk_n_alloc();
    alloc.construct(first_free++,std::move(s));
}

template<typename T>
void Vec<T>::pop_back(){
    if (first_free != element) {  // 确保不为空
        alloc.destroy(--first_free);  // 销毁最后一个有效元素
    }
}

template<typename T>
void Vec<T>::reserve(size_t new_cap){
    if(new_cap<=capacity()) return;
    auto newdata=alloc.allocate(new_cap);
    auto dest=newdata;
    auto elem=element;
    for(auto i=0;i!=size();i++) alloc.construct(dest++,std::move(*elem++));
    free();
    element=newdata;
    first_free=dest;
    cap=element+new_cap;
}

template<typename T>
void Vec<T>::resize(size_t new_size,const T &value){
    if(new_size<size()){
        for(auto p=element+new_size;p!=first_free;){
            alloc.destroy(--first_free);
        }
    }else if(new_size>size()){
        while (new_size>capacity()){
            reallocate();
        }
        for(auto i=size();i<new_size;i++) push_back(value);
    }
}

template<typename T>
void Vec<T>::free(){
    if(element){
        for(auto p=first_free;p!=element;) 
            alloc.destroy(--p);
        alloc.deallocate(element,cap-element);
    }
}

template<typename T>
Vec<T>::Vec(const Vec&s){
    auto newdata=alloc_n_copy(s.begin(),s.end());
    element=newdata.first;
    first_free=newdata.second;
}

template<typename T>
Vec<T>::Vec(std::initializer_list<T> ilist){
    auto newdata=alloc_n_copy(ilist.begin(),ilist.end());
    element=newdata.first;
    first_free=cap=newdata.second;
}

template<typename T>
Vec<T>& Vec<T>::operator=(const Vec&s){
    if(&s!=this){
        auto newdata=alloc_n_copy(s.begin(),s.end());
        free();
        element=newdata.first;
        first_free=newdata.second;
    }
    return *this;
}

template<typename T>
Vec<T>& Vec<T>::operator=(Vec &&rhs) noexcept{
    if(&rhs!=this){
        free();
        element=rhs.element;
        first_free=rhs.first_free;
        cap=rhs.cap;
    }
    return *this;
}

//重载<<
template<typename T>
std::ostream &operator<<(std::ostream &os,const Vec<T> &s){
    for(size_t i=0;i<s.size();i++){
        os<<s[i]<<" ";
    }
    return os;
}


template<typename T>
bool operator==(const Vec<T>& lhs,const Vec<T>& rhs){
    if(lhs.size()!=rhs.size()) return false;
    for(size_t i=0;i<lhs.size();i++){
        if(lhs[i]!=rhs[i]) return false;
    }
    return true;
}

template<typename T>
bool operator!=(const Vec<T>& lhs,const Vec<T>& rhs){
    return !(lhs==rhs);
}

template<typename T>
Vec<T>::~Vec(){  
    free();
}

template<typename T>
std::pair<T*,T *>
Vec<T>::alloc_n_copy(const T *b,const T *e){
    auto data=alloc.allocate(e-b);//创建一个大小为（e-b）空间，首指针为data
    return {data,std::uninitialized_copy(b,e,data)};//类似copy，将be中的内容复制构造到data之后，返回尾指针
}

template<typename T>
void Vec<T>::reallocate(){
    auto newcapacity=size()?2*size():1;//如果为0则1，不为则*2
    auto newdata = alloc.allocate(newcapacity);
    auto dest=newdata;
    auto elem=element;//旧头指针
    for(auto i=0;i<size();i++){
        alloc.construct(dest++,std::move(*elem++));
    }
    //移动元素版
    // auto dest=uninitialized_copy(make_move_iterator(begin()),make_move_iterator(end()),newdata);
    free();
    element=newdata;
    first_free=dest;
    cap=element+newcapacity;
}

#endif