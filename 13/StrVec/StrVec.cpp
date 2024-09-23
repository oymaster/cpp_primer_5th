#include "StrVec.h"

void StrVec::push_back(const std::string &s){
    chk_n_alloc();
    alloc.construct(first_free++,s);
}
void StrVec::push_back(std::string &&s){
    chk_n_alloc();
    alloc.construct(first_free++,std::move(s));
}

void StrVec::pop_back(){
    if (first_free != element) {  // 确保不为空
        alloc.destroy(--first_free);  // 销毁最后一个有效元素
    }
}

void StrVec::reserve(size_t new_cap){
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

void StrVec::resize(size_t new_size,const std::string &value){
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

void StrVec::free(){
    if(element){
        for(auto p=first_free;p!=element;) 
            alloc.destroy(--p);
        alloc.deallocate(element,cap-element);
    }
}

StrVec::StrVec(const StrVec&s){
    auto newdata=alloc_n_copy(s.begin(),s.end());
    element=newdata.first;
    first_free=newdata.second;
}

StrVec::StrVec(std::initializer_list<std::string> ilist){
    auto newdata=alloc_n_copy(ilist.begin(),ilist.end());
    element=newdata.first;
    first_free=cap=newdata.second;
}

StrVec& StrVec::operator=(const StrVec&s){
    if(&s!=this){
        auto newdata=alloc_n_copy(s.begin(),s.end());
        free();
        element=newdata.first;
        first_free=newdata.second;
    }
    return *this;
}

StrVec& StrVec::operator=(StrVec &&rhs) noexcept{
    if(&rhs!=this){
        free();
        element=rhs.element;
        first_free=rhs.first_free;
        cap=rhs.cap;
    }
    return *this;
}

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
// StrVec &operator+=(const StrVec&);
// friend StrVec operator+(const StrVec&,const StrVec&);
bool operator==(const StrVec& lhs,const StrVec& rhs){
    if(lhs.size()!=rhs.size()) return false;
    for(size_t i=0;i<lhs.size();i++){
        if(lhs[i]!=rhs[i]) return false;
    }
    return true;
}
bool operator!=(const StrVec& lhs,const StrVec& rhs){
    return !(lhs==rhs);
}


StrVec::~StrVec(){  
    free();
}

std::pair<std::string*,std::string *>
StrVec::alloc_n_copy(const std::string *b,const std::string *e){
    auto data=alloc.allocate(e-b);//创建一个大小为（e-b）空间，首指针为data
    return {data,uninitialized_copy(b,e,data)};//类似copy，将be中的内容复制构造到data之后，返回尾指针
}

void StrVec::reallocate(){
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