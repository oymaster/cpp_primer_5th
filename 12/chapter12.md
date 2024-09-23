# 十二章 动态内存和智能指针

## 动态内存

| 内容               | 存放位置                                                     | 作用域                                       |
| ------------------ | ------------------------------------------------------------ | -------------------------------------------- |
| 全局变量和静态变量 | 数据段中，包含了已初始化的数据段和未初始化的数据段           | 全局变量整个程序，静态变量在文件或者函数有效 |
| 局部变量           | 存放在栈中，                                                 | 在作用域中，离开作用域销毁                   |
| 动态分配的内存     | 堆（heap）这个堆跟数据结构的堆不一样，相当于一片自由的空间，由程序员控制，new,delete,malloc,free | 可跨域，由程序员自己销毁                     |
| 函数               | 函数本身放在代码段,函数里面参数都放在栈中                    | 看函数本身是局部还是全局                     |

* 为什么需要动态内存

  * 不知道存放多大的对象
  * 不知道对象类型
  * 为了在多个对象中共享数据

* 动态内存的问题

  以往的动态内存中，由程序员建立和销毁动态内存，容易出现以下情况导致内存泄漏

  * 一个指针指向了一个内存，换了一个指向之后，之前的内存找不到，未定义
  * 一直未释放动态内存
  * 内存相互引用


## 智能指针

* share_ptr 

  可共享的指针，带有自动销毁对象的功能

* unique_ptr

  独享对象，有特殊功能realse释放对象

* weak_ptr

  不参与引用计数，经常用于打破循环引用

  

## allocator类

  allocate函数用于分配指定数量的**未构造**对象的内存，将构造和定义分离开。

1. c语言中的内存分布，malloc和free

     malloc只分布内存，示例：
     
   ```cpp
   int *p=(int *)malloc(sizeof(int));
   *p=10;
   free(p)//释放 
   ```


2. c++中的new，delete

   示例：
   
   ```cpp
   int*p=new int (10)；//分配一个int并初始化为10
   delete p;//释放p
   ```
   
3. allocate

   示例：
   
   ```cpp
   allocator<int>alloc;
   int *p=alloc.allocate(1);//分配不初始化
   alloc.construct(p,10);//手动调用构造函数，初始化为10
   alloc.destroy(p);//手动调用析构函数
   alloc.deallocate(p,1);//释放内存
   ```
   
   

## 文本查询程序

```cpp
#include<bits/stdc++.h>
using namespace  std;
using line_id = vector<string>::size_type;

class queryResult{
    friend ostream &print(ostream& os , const queryResult &qr){
        os<<qr.searchWord<<" occurs"<< qr.lines->size()<<" "
          <<(qr.lines->size()==1?"time":"times")<<endl;
        for(auto num: *qr.lines){
            os<<"\t(line "<<num+1<<" )"
            <<*(qr.file->begin()+num)<<endl;
        }
        return os;
    }
public:
    queryResult (string s,shared_ptr<set<line_id>> p,
            shared_ptr<vector<string>>f):searchWord(s),lines(p),file(f){}

private:
    string searchWord;
    shared_ptr<set<line_id>> lines;
    shared_ptr<vector<string>> file;
};

class textQuery {
public:
    textQuery(ifstream& is): file(new vector<string>){
        string text;
        while (getline(is,text)){
            file->push_back(text);
            int n=file->size()-1;//当前行号
            istringstream line(text);
            string word;
            while (line>>word){
                auto &ptr_set = mp[word];
                if(!ptr_set) ptr_set.reset(new set<line_id>);
                else ptr_set->insert(n);
            }
            

​    }
}
queryResult query(const string &searchWord) const{
​    static shared_ptr<set<line_id>> nodata(new set<line_id>);
​    auto loc = mp.find(searchWord);
​    if(loc== mp.end()) 
​        return queryResult(searchWord,nodata,file);
​    else 
​        return queryResult(searchWord,loc->second,file);
}

private:
    shared_ptr<vector<string>> file;
    map<string,shared_ptr<set<line_id>>> mp;

};

void runQuery(ifstream &infile){
    textQuery tq(infile);
    while(true){
        string word;
        cout<<"enter word you want to query or 'q' to quit: ";
        if(!(cin>>word)||word[0]=='q') break;
        print(cout,tq.query(word));
    }
}

int main(){
    string load="test.txt";
    ifstream in(load);
    if(in.is_open()) runQuery(in);
    else cout<<"error in open file\n";
    return 0;
}
```

