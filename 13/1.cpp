#include<bits/stdc++.h>
using namespace std;

bool check(const string&&s){
    if(s.size()>0) return true;
    return false;
}

// bool check(const &s){
//     if(s.size()>0) return true;
//     return false;
// }
        
int main(){
    string s="213";
    // cout<<check(s)<<endl;
    cout<<check("213")<<endl;
}
