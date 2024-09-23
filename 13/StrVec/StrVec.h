#include<vector>
#include<string>
#include<iostream>

class StrVec{
public:
    StrVec():element(nullptr),first_free(nullptr),cap(nullptr){}
    StrVec(const StrVec&);
    StrVec(StrVec &&s) noexcept:element(s.element),first_free(s.first_free),cap(s.cap){
        s.element=s.cap=s.first_free=nullptr;
    }
    StrVec& operator=(const StrVec&);
    StrVec& operator=(StrVec &&) noexcept;

    std::string& operator[](size_t index) {
        return element[index];  // 返回元素的引用
    }
    const std::string& operator[](size_t index) const {
        return element[index];  // 返回元素的常量引用（用于 const 对象）
    }
    friend std::ostream& operator<<(std::ostream&os,const StrVec &s);
    friend std::istream& operator>>(std::istream&is,StrVec &s);
    StrVec& operator+=(const StrVec&);
    friend StrVec& operator+(const StrVec&,const StrVec&);
    friend bool operator==(const StrVec& lhs,const StrVec& rhs);
    friend bool operator!=(const StrVec& lhs,const StrVec& rhs);

    StrVec(std::initializer_list<std::string> ilist);
    ~StrVec();
    void push_back(const std::string&);
    void push_back(std::string &&);
    void pop_back();
    void reserve(size_t new_cap);
    void resize(size_t new_size){resize(new_size,"");}
    void resize(size_t new_size,const std::string &value);
    size_t size() const { return first_free-element;}
    size_t capacity() const { return cap-element; }
    std::string *begin() const { return element; }
    std::string *back() const {return first_free-1;}
    std::string *end() const { return first_free; }

private:
    void chk_n_alloc(){
        if(size()==capacity()) reallocate();
    }
    std::pair<std::string*,std::string*> alloc_n_copy
        (const std::string*,const std::string*);//创造一片新内存并将原StrVec复制过去，并返回新首尾指针
    void free();
    void reallocate();//获得更多内存并拷贝已有的元素
private:
    std::allocator<std::string> alloc;
    std::string *element;//头指针
    std::string *first_free;//元素的尾指针
    std::string *cap;//数组尾指针
};