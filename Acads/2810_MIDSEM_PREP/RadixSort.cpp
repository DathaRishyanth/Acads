#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define nl "\n"
#define MOD 1000000007
typedef long long ll;
typedef pair<ll, ll> pii;
typedef vector<ll> vi;

class Thor{
    public:
    void countSort(vector<int>&v, int exp){
        int n = v.size();
        vector<int> output(n);
        int count[10] = {0};

        for(int i=0; i<n; i++){
            count[(v[i]/exp)%10]++;
        }
        for(int i=1; i<10; i++){
            count[i] += count[i-1];
        }
        for(int i=n-1; i>=0; i--){
            output[count[(v[i]/exp)%10]-1] = v[i];
            count[(v[i]/exp)%10]--;
        }
        for(int i=0; i<n; i++){
            v[i] = output[i];
        }
    }
    void radixSort(vector<int>&v){
        int n = v.size();
        int exp = 1;
        for(int i=0; i<10; i++){
            exp *= 10;
            countSort(v,exp);
        }
    }
    void BringMeThanos(){
        vector<int> v = {802,45,70,90,24,2,66,99,1000};
        int n = v.size();
        radixSort(v);
        for(int i=0; i<n; i++){
            cout<<v[i]<<" ";
        }

        
    
    }
};


int main() {
 ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t = 1;
    cin>>t;
    while(t--){
        Thor OdinSon;
        OdinSon.BringMeThanos();
    }
}