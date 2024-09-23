#include<bits/stdc++.h>
using namespace  std;
using line_id = vector<string>::size_type;

class queryResult{
    friend ostream &print(ostream& os , const queryResult &qr){
        os<<qr.searchWord<<" occurs"<< qr.lines->size()<<" "
          <<(qr.lines->size()==1?"time":"times")<<endl;
        for(auto num: *qr.lines){
            os<<"\t(line "<<num+1<<" )"
            <<*(qr.file->begin()+num)<<endl;
        }
        return os;
    } 
public:
    queryResult (string s,shared_ptr<set<line_id>> p,shared_ptr<vector<string>>f) : searchWord(s),lines(p),file(f){}

private:
    string searchWord;
    shared_ptr<set<line_id>> lines;
    shared_ptr<vector<string>> file;
};

class textQuery {
public:
    textQuery(ifstream& is): file(new vector<string>){
        string text;
        while (getline(is,text)){
            file->push_back(text);
            int n=file->size()-1;//当前行号
            istringstream line(text);
            string word;
            while (line>>word){
                mp[word] = mp[word] ? mp[word] : make_shared<set<line_id>>();
                mp[word]->insert(n);
            }
            
        }
        
    }
    queryResult query(const string &searchWord) const{
        static shared_ptr<set<line_id>> nodata(new set<line_id>);
        auto loc = mp.find(searchWord);
        if(loc== mp.end()) 
            return queryResult(searchWord,nodata,file);
        else 
            return queryResult(searchWord,loc->second,file);
    }

private:
    shared_ptr<vector<string>> file;
    map<string,shared_ptr<set<line_id>>> mp;

};

void runQuery(ifstream &infile){
    textQuery tq(infile);
    while(true){
        string word;
        cout<<"enter word you want to query or 'q' to quit: ";
        if(!(cin>>word)||word[0]=='q') break;
        print(cout,tq.query(word));
    }
}

int main(){
    string load="test.txt";
    ifstream in(load);
    if(in.is_open()) runQuery(in);
    else cout<<"error in open file\n";
    return 0; 
}