#include <iostream>
#include <bits/stdc++.h>

using namespace std;
map<pair<string, string>, int> MyMap;

int main() {
    std::cout << "Hello World!" << std::endl;
    pair<string, string> demo;
    demo = make_pair("hoa", "la");
    MyMap[demo] = 1;
    if (MyMap[demo] == 1){
        for (auto& i : MyMap) {
        cout << i.second;
        }
    }
    
}
