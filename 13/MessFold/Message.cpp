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
