#ifndef DISC_QUOTE_H
#define DISC_QUOTE_H
//抽象基类 用来写一类折扣
#include "Quote.h"
using std::string;
class Disc_quote : public Quote 
{
private:
    size_t min_qty =0;//最低购买量
    double discount=0.0;//折扣力度

public:
    Disc_quote()=default;
    Disc_quote(const string&book,double price,size_t n,double disc):Quote::Quote(book,price),min_qty(n),discount(disc){}
    double net_price(size_t n) const =0;
};

#endif