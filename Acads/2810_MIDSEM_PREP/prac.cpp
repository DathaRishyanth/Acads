#include <bits/stdc++.h>
using namespace std;

template<typename T>
void printVector(const vector<T>& vec) {
    for (const auto& elem : vec) {
        cout << elem << " ";
    }
    cout << endl;
}

template<>
void printVector(const vector<string>& vec) {
    for (const auto& elem : vec) {
        cout << "\"" << elem << "\" ";
    }
    cout << endl;
}



int main(){
    vector<int> intVec = {1, 2, 3, 4, 5};
    vector<string> strVec = {"Hello", "World", "!"};

    cout << "Integer Vector: ";
    printVector(intVec);

    cout << "String Vector: ";
    printVector(strVec);

    return 0;
}