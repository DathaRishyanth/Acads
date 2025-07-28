#include <bits/stdc++.h>
using namespace std;

class A
{
    private:
        int a;
    public:
        A(int x) { a = x; } 
        virtual ~A()
        {
            cout << "Destructor of A" << endl;
        }
        virtual void fun()
        {
            cout << "A" << endl;
        }
};

class B : public A
{
    private:
        int b;
    public:
        ~B()
        {
            cout << "Destructor of B" << endl;
        }
        B(int x, int y) : A(x) 
        {
            b = y;
        }

        void fun()
        {
            cout << "B" << endl;
        }
};

class C : public A{
    private:
        int c;
    public:
        ~C(){
            cout<<"Destructor of C\n";
        }
        C(int x,int y) : A(x){
            c = y;
        }

        void fun(){
            cout<<"C"<<endl;
        }


};

int main()
{
    // A *obj1 = new A(1);
    // A *obj2 = new B(2, 3);
    // // B *obj3 = new A(4);  
    // B *obj4 = new B(5, 6);

    // obj1->fun(); // Calls A::fun()
    // obj2->fun(); // Calls B::fun() due to virtual function
    // obj4->fun(); // Calls B::fun()

    // delete obj1;
    // delete obj2;
    // delete obj4;

    A* obj1 = new A(3);
    A* obj2 = new B(4,5);
    A* obj3 = new C(2,3);

    vector<A*> v{obj1,obj2,obj3};
    for(auto it = v.begin();it!= v.end();it++)
        (*it)->fun();

        

    return 0;
}




