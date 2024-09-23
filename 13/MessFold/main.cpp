#include <iostream>
#include "Message.h"
#include "Folder.h"

using namespace std;

int main() {
    Folder f1;
    Message m1("Hello, World!");
    
    // 将 Message 保存到 Folder
    m1.save(f1);
    cout << "Message saved in folder." << endl;
    
    // 继续测试其他功能...

    return 0;
}
