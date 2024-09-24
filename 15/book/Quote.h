#ifndef QUOTE_H
#define QUOTE_H

#include <string>
using std::move;
using std::cout;
class Quote{
private:
    std::string bookNo;
protected:
    double price =0.0;
public:

    //clone
    virtual Quote* clone() const &{return new Quote (*this);}
    virtual Quote* clone() const &&{return new Quote (move(*this));}
    //constructor
    Quote()=default;
    Quote(const std::string &book,double sales_price):bookNo(book),price(sales_price){}
    Quote(const Quote&q):bookNo(q.bookNo),price(q.price){ cout<<" copy quote\n";}
    Quote(Quote&&q) noexcept:bookNo(move(q.bookNo)),price(move(q.price)){cout<<"move quote\n";}
    Quote& operator=(const Quote&q){
        if(this!=&q){
            bookNo=q.bookNo;
            price=q.price;
        }
        cout<<"= quote\n";
        return *this;
    }
    Quote& operator=(Quote&&q)noexcept{
        if(this!=&q){
            bookNo=move(q.bookNo);
            price=move(q.price);
        }
        cout<<"move = quote\n";
        return *this;

    }
    virtual ~Quote()=default;
    //
    std::string isbn() const {return bookNo;}
    virtual double net_price(std::size_t n) const{ return n*price; }
    
};

#endif