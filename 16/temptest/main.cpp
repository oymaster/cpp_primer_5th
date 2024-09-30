#include<iostream>
// #include"template_test.h"


using std::cout;
using std::cin;
using std::endl;



template<typename ...Args>
void g(Args ...args){
    cout<<sizeof...(Args)<<endl;
    cout<<sizeof...(args)<<endl;
}

int main(){
    g("1",2,3.0);
    g("1",2);
}