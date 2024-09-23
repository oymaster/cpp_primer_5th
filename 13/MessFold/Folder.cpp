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
