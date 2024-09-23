# 十三章 拷贝复制

## 1. 拷贝、赋值、销毁、移动构造、移动赋值（以StrVec为例）

**析构函数**：

```cpp
~StrVec();
```

**拷初构造函数**：

```cpp
StrVec(const StrVec &);
```

**拷贝赋值函数**：

```cpp
StrVec &operator=(const StrVec&);
```

**移动构造函数**:

```cpp
StrVec(StrVec &&s)noexcept;
```

**移动赋值函数：**

```cpp
StrVec &operator=(StrVec &&) noexcept;
```

* **三法则**

  如果一个类定义了拷贝、赋值、销毁之一，通常也应该定义其余两个

* **五法则**

  五法则扩展了三法则，引入了移动语义。在 C++11 中，移动语义使得对象可以通过移动而不是拷贝来转移资源，从而提高效率。

  如果一个类定义了以上五个之一，通常也应该定义其余的四个。

## 2. 左右值、引用

#### a. 引用内存占用

在编译器中如GCC,Clang，MSVC，引用本质其实就是个指针常量，所占空间和指针大小相同。但是现代编译器有优化操作。

例如：

```cpp
int a=10;
int &r=a;
r=20;
```

r作为a的引用，在某些编译器中可以优化为：

```cpp
int a=10;
a=20;
```

编译器可以直接将 `ref` 替换为 `a`，而无需在内部生成任何指向 `a` 的指针。结果是，没有对 `ref` 进行额外的空间分配。

大多数情况下，例如在类里面有成员是引用对象，则必须得占用空间。

#### **b. 左右值**

  * **左值（lvalue）**：
    
    * 左值是指可以在内存中持久存在的对象，具有可寻址性，通常是变量、数组元素等。
    * 左值可以在赋值语句的左侧使用。例如：
      ```cpp
      int x = 5; // x 是一个左值
      ```
    
  * **右值（rvalue）**：
    * 右值通常是临时对象、字面量或计算结果，不能直接取地址。
    * 右值的生命周期通常是短暂的，往往只在表达式的上下文中存在。例如：
      ```cpp
      int y = x + 5; // x + 5 是一个右值
      ```

#### c. **引用**

左值引用和右值引用在 C++ 中的大小通常是零，因为它们不占用任何额外的内存。它们的存在只是为了提供一种更方便的语法来访问对象。

  * **左值引用（lvalue reference）**：
    
    左值引用（lvalue reference）通常在底层实现为一个指针。在使用左值引用时，编译器会将引用的对象的地址存储在内存中。
    
    当你声明一个左值引用时，编译器实际上会在需要使用这个引用的地方生成代码，以获取原始对象的地址。
    
    * 使用 `&` 定义，能够绑定到左值。
    * 左值引用允许对引用对象进行修改。例如：
      ```cpp
      int a = 10;
      int& ref = a; // ref 是 a 的左值引用
      ref = 20;     // a 的值现在是 20
      ```
    
  * **右值引用（rvalue reference）**：
    
    右值引用（rvalue reference）也在底层实现为指针，但它们的使用语义与左值引用不同。右值引用允许对临时对象进行操作，并且通常与移动语义相关。
    
    当你声明一个右值引用时，编译器会生成代码以允许对临时对象的移动（而不是拷贝）。
    
    * 使用 `&&` 定义，能够绑定到右值。
    * 右值引用主要用于实现移动语义，允许对临时对象进行高效处理，避免拷贝。例如：
      ```cpp
      void process(int&& value) { /* 处理 value */ }
      process(10); // 10 作为右值被传递
      ```

## 3. Message类

#### Message.h

```cpp
#ifndef MESSAGE_H
#define MESSAGE_H
#include <set>
#include <string>
class Folder;
class Message {
    friend class Folder;
public:
    explicit Message(const std::string &str = "") : contents(str) {}
    Message(const Message&);
    Message& operator=(const Message&);
    ~Message();
    void save(Folder&);
    void remove(Folder&);
private:
    std::string contents;
    std::set<Folder*> folders;
    void add_to_Folders(const Message&);
    void remove_from_Folders();
    void addFol( Folder *f) { folders.insert(f); }
    void remFol( Folder *f) { folders.erase(f); }
};
#endif // MESSAGE_H
```

#### Message.cpp

```cpp
#include "Message.h"
#include "Folder.h"

// 构造函数
Message::Message(const Message &m) : contents(m.contents), folders(m.folders) {
    add_to_Folders(m);
}

// 析构函数
Message::~Message() {
    remove_from_Folders();
}

// 赋值运算符
Message& Message::operator=(const Message &rhs) {
    if (this != &rhs) {
        remove_from_Folders();
        contents = rhs.contents;
        folders = rhs.folders;
        add_to_Folders(rhs);
    }
    return *this;
}

// 保存 Message 到 Folder
void Message::save(Folder &f) {
    folders.insert(&f);
    f.addMsg(this);
}

// 从 Folder 中移除 Message
void Message::remove(Folder &f) {
    folders.erase(&f);
    f.remMsg(this);
}

// 辅助函数：将当前 Message 添加到所有关联的 Folder 中
void Message::add_to_Folders(const Message &m) {
    for (auto f : m.folders) {
        f->addMsg(this);
    }
}

// 辅助函数：将当前 Message 从所有关联的 Folder 中移除
void Message::remove_from_Folders() {
    for (auto f : folders) {
        f->remMsg(this);
    }
}
```

#### Folder.cpp

```cpp
#include "Folder.h"
#include "Message.h"

// 构造函数
Folder::Folder(const Folder &f) : msgs(f.msgs) {
    add_to_Message(f);
}

// 赋值运算符
Folder& Folder::operator=(const Folder &rhs) {
    if (this != &rhs) {
        remove_to_Message();
        msgs = rhs.msgs;
        add_to_Message(rhs);
    }
    return *this;
}

// 析构函数
Folder::~Folder() {
    remove_to_Message();
}

// 辅助函数：将当前 Folder 添加到 Message 中
void Folder::add_to_Message(const Folder &f) {
    for (auto s : f.msgs) {
        s->addFol(this);
    }
}

// 辅助函数：将当前 Folder 从 Message 中移除
void Folder::remove_to_Message() {
    for (auto m : msgs) {
        m->remFol(this);
    }
    msgs.clear();
}

// 添加消息到 Folder
void Folder::addMsg(Message *m) {
    msgs.insert(m);
}

// 从 Folder 中移除消息
void Folder::remMsg(Message *m) {
    msgs.erase(m);
}
```

#### Folder.h

```cpp
#ifndef FOLDER_H
#define FOLDER_H

#include <set>
class Message;

class Folder {
    friend class Message;

public:
    Folder() = default;
    Folder(const Folder&);
    Folder& operator=(const Folder&);
    ~Folder();

private:
    std::set<Message*> msgs;
    void add_to_Message(const Folder&);
    void remove_to_Message();

    void addMsg(Message *m);
    void remMsg(Message *m);
};

#endif // FOLDER_H
```



## 4. StrVec类

#### StrVec.h

```cpp
#include<vector>
#include<string>

class StrVec{
public:
    StrVec():element(nullptr),first_free(nullptr),cap(nullptr){}
    StrVec(const StrVec&);
    StrVec(StrVec &&s) noexcept:element(s.element),first_free(s.first_free),cap(s.cap){
        s.element=s.cap=s.first_free=nullptr;
    }
    StrVec &operator=(const StrVec&);
    StrVec &operator=(StrVec &&) noexcept;

    std::string& operator[](size_t index) {
        return element[index];  // 返回元素的引用
    }
    const std::string& operator[](size_t index) const {
        return element[index];  // 返回元素的常量引用（用于 const 对象）
    }
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
```

#### StrVec.cpp

```cpp
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
```

