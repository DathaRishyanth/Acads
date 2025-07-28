#include <bits/stdc++.h>
using namespace std;
#define nl "\n"

class A{
    public:
        A(){
            x = 2;
        }
        static int x;
        int d;
        void fun(){
            this->x = 10;
        }
        void fub(){
            this->x = 4;
        }
        static int getX(){
            return x;
        }

        bool operator >(A& n){
            return this->x > n.x;
        }
        A operator -(){
            return A();
        }
        friend ostream& operator<<(ostream &stream,A&a){
            stream<<a.getX();
            return stream;
        }
        int *operator ->(){
            return &x;
        }


};


int A::x;

int main(){ 
    A a;
    A b;
    cout<<a.x<<nl;
    b.fun();
    cout<<b.x<<nl;
    cout<<a.x<<nl;

    a.fub();
    cout<<a.getX()<<" "<<b.getX()<<nl;

    bool flag = a > b;
    cout<<flag<<nl;
    flag = b > a;
    cout<<flag<<nl;

    A c = -a;
    cout<<b.getX()<<nl;

    cout<<a<<nl;

    


}