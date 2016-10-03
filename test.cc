// program 1
// stmt_list 2
// stmt 3
// expr 4
// term 5
// term_tail 6
// add_op 7
// factor 8
// fact_tail 9
// mult_op 10
#include <bits/stdc++.h>

using namespace std;
const int MaxN = 101;

string terminal_names[MaxN];
string non_terminal_names[MaxN];
int numberOfNonTerminal, numberOfTerminal, numberOfProduction;
int right_hand_sides[MaxN][MaxN] = {0}; // production ith, set of RHS
int lhs[MaxN];
//int first_set[MaxN][MaxN] = {0};
map<int, set<int>> first_set;
map<int,int>EPS;

void init(){
    memset(terminal_names,sizeof(terminal_names), 0);
    memset(non_terminal_names,sizeof(non_terminal_names), 0);
    
}

int isTerminal(string s){
    for(int i = 1; i <= numberOfTerminal; i++) {
        if (s == terminal_names[i]) return i;
    }
    return 0;
}

int isNonTerminal(string s){
    for(int i = 1; i <= numberOfNonTerminal; i++){
        if (s == non_terminal_names[i]) return i;
    }
    return 0;
}


void read_file(){
    string s, st, sr;
    int n = 0, cnt = 0;
    while(getline(cin,s)){
        n++;
        if(s == "") break;
        stringstream ss(s);
        ss >> st >> n;
        terminal_names[n] = st;
    }
    numberOfTerminal = n;
    numberOfProduction = 0;
    numberOfNonTerminal = 0;
    while(getline(cin, s)){
        numberOfProduction++;
        stringstream ss(s);
        ss >> st >> sr;
        
        if (isNonTerminal(st) == 0) {
            numberOfNonTerminal++;
            non_terminal_names[numberOfNonTerminal] = st;
        }
        lhs[numberOfProduction] = isNonTerminal(st);
        int k = 0;
        while(ss >> st){
            k++;
            //cout << "st = " << st << endl;
            int tmp = isTerminal(st);
            if(tmp > 0) {
                right_hand_sides[numberOfProduction][k] = -tmp;
            }
            else {
                tmp = isNonTerminal(st);
                if (tmp == 0){
                    numberOfNonTerminal++;
                    non_terminal_names[numberOfNonTerminal] = st;
                    tmp = numberOfNonTerminal;
                }    
                right_hand_sides[numberOfProduction][k] = tmp;
            }
            
        }
        right_hand_sides[numberOfProduction][0] = k;
    }
    
}

void make_EPS(){
    for (int i = 1; i <= numberOfTerminal; i++) {
        /* code */
        EPS[-i] = 0;
        first_set[-i].insert(-i);
    }
    for(int i = 1; i <= numberOfProduction; i++){
        if (right_hand_sides[i][0] == 0) EPS[lhs[i]] = 1;
    }
    
}


void cal_first(int i){
    int tmp, flag = 0;
    for(int j = 1; j <= numberOfProduction; j++){
        if (lhs[j] == i){
            flag = 0;
            //if(right_hand_sides[j][0] == 0) 
            //cout << "i = " << i << endl;
            for(int k = 1; k <= right_hand_sides[j][0]; k++){
                //cout << "rhs = " << right_hand_sides[j][k] << endl;
                // if(right_hand_sides[j][k] < 0){
                //     first_set[i].insert(-right_hand_sides[j][k]);
                //     //first_set[i][first_set[i][0]] = -right_hand_sides[j][k];
                //     break;
                // }   
                // else {
                //     if (right_hand_sides[j][k] != i) cal_first(right_hand_sides[j][k]);
                //     if(EPS[right_hand_sides[j][k]] != 0) break; 
                //     EPS[right_hand_sides[j][k]] = 1;
                // }
                tmp = right_hand_sides[j][k];
                if(tmp != i) cal_first(tmp);
                first_set[i].insert(first_set[tmp].begin(),first_set[tmp].end());
                if (!EPS[tmp]) {
                    flag = 1;
                    break;
                }
                
            }
            if (!flag) EPS[i] = 1;
            
        }
    }
    
}

void make_first(){
    for (int i = 1; i <= numberOfNonTerminal ; i++) {
        /* code */
        cal_first(i);
    }
    // for(int i = numberOfNonTerminal; i >=  1 ;i--){
    //     cal_first(i);        
    // }
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    init();
    read_file();
    // for (int i = 1; i <= numberOfProduction; i++) {
    //     cout << lhs[i] << endl;
    // }
    make_EPS();
    make_first();
    // for (int i = 1; i <= numberOfNonTerminal; i++) {
    //     cout << EPS[i] << endl;
    // }
    //cal_first(1);
    //cal_first(4);
   
    // for(int i = 1; i <= numberOfProduction; i++){
    //     for (int j = 1; j <= right_hand_sides[i][0] ; j++) {
    //         cout << right_hand_sides[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    //cout << numberOfNonTerminal << endl;
    for(int i = 1; i <= numberOfNonTerminal; i++){
        cout << i << ": ";
        for (auto j: first_set[i]) {
            cout << j << " ";
        }
        cout << endl;
    }
    return 0;
}