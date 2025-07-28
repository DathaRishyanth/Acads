#include <bits/stdc++.h>
using namespace std;

class Number
{
private:
    int num;

public:
    Number(int n) : num{n} {}
    Number() : num{0} {}

    int getNum() const
    {
        return num;
    }

    int operator+(const Number &b) const
    {
        return num + b.num;
    }

    int &operator[](Number &b)
    { // Returning reference
        return num;
    }

    Number &operator=(const Number &b)
    { // Fixing assignment operator
        if (this != &b)
        {
            num = b.num;
        }
        return *this;
    }

    int *operator->()
    { 
        return &num;
    }

    void *operator new(size_t size)
    {
        cout << "Creating\n";
        return malloc(size);
    }

    void operator delete(void *ptr)
    {
        cout << "Deleting\n";
        free(ptr);
    }

    friend ostream &operator<<(ostream &stream, const Number &a)
    {
        stream << a.num;
        return stream;
    }
};

class Student
{
private:
    Number roll;

public:
    Student(int n) : roll(n) {}

    Number *operator->()
    {
        return &roll;
    }
};

// Subscript operator( [] ) requires returning by reference so that you can modify them later

int main()
{
    // Number n1(5);
    // Number n2(5);
    // int c = n1+n2;
    // int d = n1[n2];
    // bool flag = n1 = n2;
    // Number* n3 = new Number(10);
    // cout<<*n3<<"\n";
    // cout<<*n3->operator->()<<"\n";
    // delete(n3);
    // cout<<c<<" " <<d<<" "<<flag<<"\n";
    // cout<<*n2.operator->()
    Student s1(5);
    cout << s1->getNum();
}