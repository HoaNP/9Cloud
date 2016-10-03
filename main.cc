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

string terminal_names[MaxN]; /*store name of Terminal*/
string non_terminal_names[MaxN]; /*store name of NonTerminal*/

int numberOfNonTerminal, /* number of NonTerminal*/
    numberOfTerminal, /* number of Terminal*/
    numberOfProduction; /* number of Production*/
    
int right_hand_sides[MaxN][MaxN] = {0}; /*rhs[i][0] is number of symbols in rhs of i-th production
                                          rhs[i][j] is j-th symbol in rhs of i-th production*/
int lhs[MaxN]; //store non-terminal of i-th production

map<int, set<int>> first_set; 
map<int, set<int>> follow_set;
map<int, set<int>> predict_set;
map<int,int>EPS; 
int LL[MaxN][MaxN] = {0};

/**
 * Make initialization
 */
void init(){
    memset(terminal_names,sizeof(terminal_names), 0);
    memset(non_terminal_names,sizeof(non_terminal_names), 0);
}

/**
 * Check if s is a terminal
 */
int isTerminal(string s){
    for(int i = 1; i <= numberOfTerminal; i++) {
        if (s == terminal_names[i]) return i;
    }
    return 0;
}

/**
 * Check if s is a nonterminal
 */
int isNonTerminal(string s){
    for(int i = 1; i <= numberOfNonTerminal; i++){
        if (s == non_terminal_names[i]) return i;
    }
    return 0;
}

/**
 * Read terminals, nonterminals from file
 */
void read_file(){
    string s, st, sr;
    int n = 0, cnt = 0;
    numberOfProduction = 0;
    numberOfNonTerminal = 0;
    while(getline(cin,s)){
        n++;
        if(s == "") break;
        stringstream ss(s);
        ss >> st >> n; //read token names and token numbers
        terminal_names[n] = st;
    }
    numberOfTerminal = n;
    while(getline(cin, s)){
        // read a production
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

/**
 * make EPS
 */
void make_EPS(){
    for (int i = 1; i <= numberOfTerminal; i++) {
        EPS[-i] = 0;
        first_set[-i].insert(i);
    }
    for(int i = 1; i <= numberOfProduction; i++){
        if (right_hand_sides[i][0] == 0) EPS[lhs[i]] = 1;
    }
    
}

/**
 * Calculate FIRST(s)
 */
void cal_first(int i){
    int tmp = 0;
    for(int j = 1; j <= numberOfProduction; j++){
        if (lhs[j] == i){
            for(int k = 1; k <= right_hand_sides[j][0]; k++){
                tmp = right_hand_sides[j][k];
                if(tmp != i) cal_first(tmp);
                first_set[i].insert(first_set[tmp].begin(),first_set[tmp].end());
                if (!EPS[tmp]) {
                    break;
                }
                else {
                    EPS[i] = 1;
                }
            }
        }
    }
    
}

/**
 * Make FIRST set
 */
void make_first(){
    for (int i = 1; i <= numberOfNonTerminal ; i++) {
        cal_first(i);
    }
}

/**
 * Calculate FOLLOW(s)
 */
void cal_follow(int i){
    int tmp;
    for(int j = 1; j <= numberOfProduction; j++){
        for (int k = 1; k <= right_hand_sides[j][0] ; k++) {
            tmp = right_hand_sides[j][k];
            if(tmp == i){
                if (k < right_hand_sides[j][0]){
                    follow_set[i].insert(first_set[right_hand_sides[j][k+1]].begin(),
                                         first_set[right_hand_sides[j][k+1]].end());    
                }
                
                if (k == right_hand_sides[j][0] || (k < right_hand_sides[j][0] && EPS[right_hand_sides[j][k+1]])){
                    if (lhs[j] != i) cal_follow(lhs[j]);
                    follow_set[i].insert(follow_set[lhs[j]].begin(),follow_set[lhs[j]].end());
                }
            }
        }
    }
}

/**
 * Make FOLLOW set
 */
void make_follow(){
    for (int i = 1; i <= numberOfNonTerminal ; i++) {
        /* code */
        cal_follow(i);
    }
}

/**
 * Make PREDICT set
 */
void make_predict(){
    int tmp;
    for(int i = 1; i <= numberOfProduction; i++){
        for(int j = 1; j <= right_hand_sides[i][0]; j++){
            tmp = right_hand_sides[i][j];
            predict_set[i].insert(first_set[tmp].begin(), first_set[tmp].end());    
            if (!EPS[tmp]) break;
        }
        if (EPS[right_hand_sides[i][1]] || right_hand_sides[i][0] == 0) {
            predict_set[i].insert(follow_set[lhs[i]].begin(), follow_set[lhs[i]].end());
        }
        
    }
}

/**
 * Make LL Table
 */
void make_LL(){
    for(int i = 1; i <= numberOfProduction; i++){
        for(auto j: predict_set[i]){
            LL[lhs[i]][j] = i;
        }
    }
}

void display(int n, map<int, set<int>> m){
    for(int i = 1; i <= n; i++){
        cout << non_terminal_names[i] << ": ";
        for (auto j: m[i]) {
            cout << terminal_names[j] << " ";
        }
        cout << endl;
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    init();
    read_file();
    make_EPS();
    make_first();
    make_follow();
    make_predict();
   
    cout << "First Set: \n";
    display(numberOfNonTerminal, first_set);
    cout << "\n\nFollow Set: \n";
    display(numberOfNonTerminal,follow_set);
    cout << "\n\nPredict Set: \n";
    for(int i = 1; i <= numberOfProduction; i++){
        cout << i << ": ";
        for (auto j: predict_set[i]) {
            cout << terminal_names[j] << " ";
        }
        cout << endl;
    }
    make_LL();
    cout << "\n\nLL Table: \n";
    cout << setw(11) << "|";
    for (int j = 1; j <= numberOfTerminal; j++) {
        if (terminal_names[j] != "") cout << setw(10) << terminal_names[j] << "|";
    }
    cout << endl;
    for(int i = 1; i<= numberOfNonTerminal; i++){
        cout << setw(10) << non_terminal_names[i] << "|";
        for (int j = 1; j <= numberOfTerminal; j++) {
            if (terminal_names[j] != "")
                cout << setw(10) <<LL[i][j] << "|";
        }
        cout << endl;
    }
    return 0;
}