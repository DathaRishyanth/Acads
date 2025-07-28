#include <bits/stdc++.h>
using namespace std;

int evaluate(vector<int> &coef,int a){
    int res = 0;
    int n = coef.size();
    int i = n-2;
    res = coef[n-2] + a*coef[n-1];
    i--;
    while(i>=0)
    {
        res = coef[i] + a*res;
        i--;
    }
    return res;
}



int main(){
    vector<int> coef = {2,3,0,5};
    cout<<evaluate(coef,2);

}