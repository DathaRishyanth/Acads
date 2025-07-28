#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<int> coeff = {2,3,0,5};
    int degree = coeff.size();
    int x = 2;
    int res = 0;
    auto evaluate = [&coeff,&x](){
        int res = 0;
        int n = coeff.size();
        int i = n-2;
        res = coeff[n-2] + x*coeff[n-1];
        i--;
        while(i>=0){
            res = coeff[i] + x*res;
            i--;
        }
        return res;
    };
    cout<<evaluate();
}