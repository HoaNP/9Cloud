#include <bits/stdc++.h>

using namespace std;
const int MaxN = 1001;


map<string, int> Terminal;
set<string> NonTerminal;
map<int, list<string> > Production;
map<pair<string, string>, int> parse_tab;
int prod_tab[MaxN];
stack<string> parse_stack;
map<string, set<string> > First, Follow;
map<int, set<string> > Predict;
map<string, bool> EPS;
void match(string s){
    
}

void parse_error(){
    
}

void MakeEPS(){
    for(auto& x: Terminal){
        EPS[x.first] = false;
        First[x.first].insert(x.first);
    }
    for(auto p: Production){
        if(p.second.size() == 1) {
            EPS[*p.second.begin()] = true;
        }
        else {
            EPS[*p.second.begin()] = false;
        }
    }
    //do{
        for(auto p: Production){
            if(p.second.size() != 1){
                string x = *p.second.begin();
                for(auto y: p.second){
                    if (y == x) continue;
                    First[x].insert(First[y].begin(), First[y].end());
                    if(!EPS[y]) break;
                }
                EPS[x] = true;
            }
        }
        
    //}while(1);
    
    
}

void MakeFollow(){
    
    
}
void CreateTable(){
    string expected_sym, input_token;
    parse_stack.push("iden");
    while(1){
        expected_sym = parse_stack.top();
        parse_stack.pop();
        auto it = Terminal.find(expected_sym);
        if (it != Terminal.end()){
            match(expected_sym);
            if (expected_sym == "$$") return;
        }
        else {
            pair<string, string> tmp;
            tmp = make_pair(expected_sym, input_token);
            if(parse_tab[tmp] == 0){
                //break;
                parse_error();
            } 
            else {
                int p = parse_tab[tmp], flag = 0;
                for (auto i : Production[p]) {
                    if (!flag){
                        flag = 1;
                        continue;
                    }
                    parse_stack.push(i);
                }
                //break;
                
            }
            
        }
    }
}


void ReadFile(){
    int n;
    string s, st, sr, tmp;
    //stringstream ss;
    while(getline(cin,s)){
        if(s == "") break;
        stringstream ss(s);
        ss >> st >> n;
        Terminal[st] = n;
        //cout << st << " " << Terminal[st] << endl;
    }
    n = 0;
    while(getline(cin,s)){
        n++;
        stringstream ss(s);
        ss >> st >> sr;
        Production[n].push_back(st);
        while(ss >> tmp){
            Production[n].push_back(tmp);
        }
        NonTerminal.insert(st);
        //cout <<sr<< endl;
    }
    
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    ReadFile();
    //CreateTable();
    // for (auto& x: Terminal) {
    //     cout << x.first << ": " << x.second << '\n';
    // }
    // for (auto& x: Terminal) {
    //     cout << x.first << ": " << x.second << '\n';
    // }
    // for(auto x: Production){
    //     cout << x.first << endl;
    //     //cout << *x.second.begin() << endl;
    //     for(auto y:x.second){
    //         cout << y << " "  <<  endl;
            
    //     }
    //     cout << endl;
    // }
    MakeEPS();
    cout << "First Set: \n";
    for (auto x : First) {
        cout << "NonTerminal: " << x.first << endl;
        for (auto y : x.second) {
            cout << y << " ";
        }
        cout << endl;
    }
    
    return 0;
    
}