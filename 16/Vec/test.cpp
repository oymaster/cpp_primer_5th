#include <iostream>
#include <string>
#include "Vec.h"  // 假设 Vec 类的定义在 Vec.h 文件中

using std::cout;
using std::endl;
using std::string;

int main() {
    // 使用列表初始化构造函数创建 Vec
    Vec<int>v1;
    string s;
    Vec<string>vec = {"apple", "banana", "cherry"};
    Vec<string> v2=vec;
    // v2[2]="asd";
    Vec<string> moveVec=std::move(vec);
    //测<<>>
    // std::cin>> v2;
    cout << "<< contents of v2:" << endl;
    cout<<v2<<endl;
    cout<<(moveVec==v2)<<endl;
    cout << "move contents of vec:" << endl;
    for (size_t i = 0; i < moveVec.size(); ++i) {
        cout << moveVec[i] << endl;  // 输出 apple, banana, cherry, date
    }
    cout << "\nInitial contents of vec:" << endl;
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i] << endl;  // 输出 apple, banana, cherry
    }

    // 使用 push_back 添加元素
    vec.push_back("date");
    cout << "\nAfter adding 'date':" << endl;
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i] << endl;  // 输出 apple, banana, cherry, date
    }

    // 使用 reserve 函数
    vec.reserve(10);
    cout << "\nCapacity after reserving space for 10:" << endl;
    cout << "Capacity: " << vec.capacity() << endl;  // 输出当前容量

    // 使用 resize 函数
    vec.resize(6, "default");
    cout << "\nAfter resizing to 6:" << endl;
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i] << endl;  // 输出 apple, banana, cherry, date, default, default
    }

    // 使用 resize 函数减小大小
    vec.resize(3);
    cout << "\nAfter resizing to 3:" << endl;
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i] << endl;  // 输出 apple, banana, cherry
    }
    //使用pop_bakc()
    cout<<vec.size()<<endl;
    vec.pop_back();
    cout<<vec.size()<<endl;
    
    return 0;
}
