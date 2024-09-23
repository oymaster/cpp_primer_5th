#include<bits/stdc++.h>
using namespace  std;
using line_id = vector<string>::size_type;
vector<string> line;
map<string,set<line_id>> mp;

void runQuery(ifstream &infile){
    string s;
    int cnt=0;
    while(getline(infile,s)){
        istringstream sLine(s);
        line.push_back(s);
        string word;
        while(sLine>>word){
            mp[word].insert(cnt);
        }
        cnt++;
    }
    while(true){
        string word;
        cout<<"enter word you want to query or 'q' to quit: ";
        if(!(cin>>word)||word[0]=='q') break;
        auto st=mp[word];
        if(!st.size()) cout<<"occur 0 time"<<endl;
        else {
            for(auto i:st){
                cout<<i<<" "<<line[i]<<endl;
            }
        }
    }
}
int main(){
    string load="test.txt";
    ifstream in(load);
    if(in.is_open()) runQuery(in);
    else cout<<"error in open file\n";
    return 0;
}


