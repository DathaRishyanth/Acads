#include <bits/stdc++.h>
using namespace std;    

class Increase{
    public:
        int k;
        Increase(){
            k = 0;
        }
        Increase(int x){
            k = x;
        }
        // int operator()(int x){
        //     return x+1;
        // }
        int operator()(int arr){
            return arr+k;
        }

};

class Compare{
    public:
        bool operator()(int a, int b){
            if(a%2==0 && b%2==0){
                return a<b;
            }
            if(a%2!=0 && b%2!=0){
                return a<b;
            }
            return a%2==0;
            return false;
        }

};

class Duplicate{
    public:
        string operator()(string s){
            return s+s;
        }
};

int main(){
    // Increase inc;
    // int k = 10;
    // cout<<inc(5)<<endl;
    // vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    // sort(v.begin(), v.end(), Compare());
    // for(auto x: v){
    //     cout<<x<<" ";
    // }
    // cout<<endl;
    // Increase inc2(k);
    // for(auto it = v.begin(); it!=v.end(); it++){
    //     *it = inc2(*it);
    // }
    // for(auto x: v){
    //     cout<<x<<" ";
    // }

    // set<string> s;
    // s.insert("abc");
    // s.insert("def");
    // s.insert("ghi");

    // Duplicate dup;
    // set<string> newSet;
    // transform(s.begin(), s.end(), inserter(newSet, newSet.begin()), dup);
    
    // for(auto x: newSet){
    //     cout << x << " ";
    // }



int g = 10;


    std::vector<int> v = {0, 1, 2, 3};
    int k1 = 3, k2 = 5;
    
    // first for_each
    std::for_each(v.begin(), v.end(), [&](int &x) { 
        std::cout << ++k1 << ++k2 << ++g << std::endl;
    });

    // second for_each
    std::for_each(v.begin(), v.end(), [](int x) {
        std::cout << x << std::endl;
    });






    return 0;
}