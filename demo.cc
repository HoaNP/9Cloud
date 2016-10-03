#include <bits/stdc++.h>

using namespace std;
const int MaxN = 1001;

map<string, int> lTerminal; // Terminal, int
map<string, int> lNonTerminal;
map<int, string[MaxN]> lProduction; // id of Production, 0th is lhs, else rhs

//char First[MaxN][MaxN];
map<string, set<string>> First;
int rhs[MaxN][MaxN] = {0};
int numberOfrhs, numberOfTerminal, numberOfNonTerminal;

int getValues(string s){
    auto x = lTerminal.find(s);
    if (x != lTerminal.end()) {
        return -x->second;
    }
    x = lNonTerminal.find(s);
    if (x != lNonTerminal.end()){
        return x->second;
    }
    return 0;
}

bool isNonTerminal(string s){
    auto x = lNonTerminal.find(s);
    if (x != lNonTerminal.end()){
        return true;
    }
    return false;
}


void read_file(){
    string s, st, sr;
    int n = 0, cnt = 0;
    while(getline(cin,s)){
        n++;
        if(s == "") break;
        stringstream ss(s);
        ss >> st >> n;
        lTerminal[st] = n;
    }
    numberOfTerminal = n;
    n = 0;
    while(getline(cin, s)){
        n++;
        
        stringstream ss(s);
        ss >> st >> sr;
        if(lNonTerminal.find(st) == lNonTerminal.end()) {
            cnt++;
            lNonTerminal[st] = cnt;
            cout << st << ": " << cnt << endl;
        }
        int k = 0;
        lProduction[n][k] = st;
       
        while(ss >> st){
            k++;
            lProduction[n][k] = st;
            
        }
        rhs[n][0] = k;
    }
    numberOfrhs = n;
    numberOfNonTerminal = cnt;
}

void make_RHS(){
    for(auto x: lProduction){
        //cout << x.first << endl;
        for(int i = 1; i <= rhs[x.first][0];i++){
            string tmp = lProduction[x.first][i];
            cout << tmp << " " << getValues(tmp) << endl;
            rhs[x.first][i] = getValues(tmp);
        }
    }
}
void cal_First(string s){
    //cout << "Day la string s: " << s << endl;
    if(!isNonTerminal(s)) First[s].insert(s);
    for(auto x: lProduction){
        //cout << x.second[0] << " - " << x.second[1] << endl;
        if(x.second[0] == s){
            if(!isNonTerminal(x.second[1])) First[s].insert(x.second[1]);
            else cal_First(x.second[1]);
        }
    }
}


void make_First(){
    
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    read_file();
    make_RHS();
    // for(int i = 1; i <= numberOfrhs; i++){
    //     for(int j = 1; j <= rhs[i][0]; j++){
    //         cout << rhs[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    cout << "FIRST: \n";
    for(auto x: NonTerminal) cal_First(x.first);
    for (auto i : First) {
        cout << i.first << endl;
        for(auto j: i.second){
            cout << j << " ";
        }
        cout << endl;
    }
   
    return 0;
}