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
