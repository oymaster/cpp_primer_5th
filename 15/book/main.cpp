#include<iostream>
#include"Quote.h"
#include"Bulk_quote.h"
#include"Basket.h"

using std::cin;
using std::cout;
using std::endl;
using std::ostream;

double print_total(ostream &os,const Quote &item, size_t n){
    double ret = item.net_price(n);
    os<<"ISBN: "<<item.isbn()<<" #sold: "<<n<<" total prices: "<<ret<<endl;
    return ret;
}

int main(){
    // Quote q1("1",20.0);
    // Quote q2("2",30.0);
    // Bulk_quote bq1("3",40,2,0.7);
    // print_total(cout,q1,3);
    // print_total(cout,q2,4);
    // print_total(cout,bq1,5);
    Basket basket;

    // 创建一些 Quote 和 Bulk_quote 对象
    Quote q1("12345", 20.0);
    Bulk_quote bq1("67890", 30.0, 3, 0.1); // 3本以上打9折
    Bulk_quote bq2("12345", 20.0, 2, 0.2); // 2本以上打8折

    // 将它们添加到购物车
    basket.add_item(q1);
    basket.add_item(bq1);
    basket.add_item(bq2);
    
    // 计算并打印总销售额
    basket.total_receipt(std::cout);

}