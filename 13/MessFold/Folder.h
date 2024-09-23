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
