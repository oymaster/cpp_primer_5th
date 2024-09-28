#include <iostream>
#ifndef DEBUG_DELETE
#define DEBUG_DELETE

class debugDelete{
private:
    std::ostream& os;
public:
    debugDelete(std::ostream& s=std::cerr):os(s){}
    template<typename T>
    void operator() (T *p) const {
        os<<"debug delete\n";
        delete p;
    }
};

#endif