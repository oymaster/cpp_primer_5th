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

#endif