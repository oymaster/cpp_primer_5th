#include <bits/stdc++.h>
using namespace std;
struct man{
    string x;
    vector<string>number;
};

int main() {
    string line;
    vector<man>people;
    while(getline(cin,line)){
        man t1;
        istringstream s(line);
        s>>t1.x;
        string num;
        while(s>>num) t1.number.push_back(num);
        people.push_back(t1);
    }
    for(auto i:people){
        cout<<i.x<<" ";
        for(auto j:i.number) cout<<j<<" ";
        cout<<endl;
    }
    return 0;
}
