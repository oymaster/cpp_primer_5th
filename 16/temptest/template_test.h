#ifndef TEMPLATE_TEST_H
#define TEMPLATE_TEST_H

#include<iostream>

template<typename T>
int compare(const T& lhs,const T& rhs){
    if(lhs<rhs) return -1;
    if(rhs<lhs) return 1;
    return 0;
}

template<typename it,typename Value>
it find(it first,it last,const Value&v){
    while(1){
        if(first==last&&*first==Value) return first;
        ++first;
    }
}

template<typename Array>
void print(const Array& arr){
    for(const auto& elem :arr ){
        std::cout<<elem<<"\n";
    }
}

template<typename T,unsigned N>
T *begin(const T(&arr)[N]){
    return arr;
}

template<typename T,unsigned N>
T *begin(const T(&arr)[N]){
    return arr+N;
}

template<typename T,size_t N>
constexpr size_t size(const T(&arr)[N]){
    return N;
}

//16.19
template<typename Container>
void print2(const Container&c){
    for(typename Container::size_t i=0;i!=c.size();i++) std::cout<<c[i]<<" ";
    std::cout<<"\n";
}

//16.20
template<typename Container>
void print3(const Container&c){
    for(auto it=c.begin();it!=c.end();it++) std::cout<<*it<<" ";
    std::cout<<"\n";
}


#endif