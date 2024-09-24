#ifndef BASKET_H
#define BASKET_H

#include"Quote.h"
#include <memory>
#include<set>
#include<ostream>
using std::shared_ptr;
using std::ostream;
//前向声明
double print_total(ostream &os,const Quote &item, size_t n);

class Basket
{
private:
   static bool compare(const shared_ptr<Quote>&lhs,const shared_ptr<Quote>&rhs){ return lhs->isbn()<rhs->isbn();}
   std::multiset<shared_ptr<Quote>,decltype(&compare)>items{&compare};

public:
    // void add_item(const shared_ptr<Quote>&item){items.insert(item);}
    void add_item(const Quote&q){
        items.insert(shared_ptr<Quote>(q.clone()));
    }
    void add_item(Quote&&q){
        items.insert(shared_ptr<Quote>(move(q).clone()));
    }

    double total_receipt(std::ostream& os) const{
        double sum=0.0;
        for(auto it=items.begin();it!=items.end();it=items.upper_bound(*it)){
            sum+=print_total(os,**it,items.count(*it));
        }
        os<<"Total sales : "<<sum<<std::endl;
        return sum;
    }


};

#endif