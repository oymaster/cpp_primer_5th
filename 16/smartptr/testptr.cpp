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
