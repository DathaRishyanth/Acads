#include <bits/stdc++.h>
using namespace std;

class Number
{
private:
    int num;

public:
    Number() {}
    Number(int a) : num(a) {}
    int getNum()
    {
        return num;
    }
    Number &operator++()
    {
        num++;
        return *this;
    }

    Number &operator+(Number &n)
    {
        num += n.num;
        return *this;
    }
    Number &operator-(Number &n)
    {
        num -= n.num;
        return *this;
    }
    // Number& operator+(int n){
    //     num += n;
    //     return *this;
    // }
    // friend int operator+(int n,Number &num);

    void *operator new(size_t size)
    {
        cout << "New operator overloaded" << endl;
        void *p = malloc(size);
        return p;
    }

    void operator delete(void *p)
    {
        cout << "Delete operator overloaded" << endl;
        free(p);
    }

    friend ostream &operator<<(ostream &out, Number &n);
    friend istream &operator>>(istream &stream, Number &n);
};

int operator+(int n, Number &num)
{
    return n + num.getNum();
}

int operator+(Number &num, int n)
{
    return n + num.getNum();
}

class Word
{
private:
    string s;

public:
    Word() {}
    Word(string a) : s(a) {}
    Word &operator*(int n)
    {
        string temp = s;
        for (int i = 0; i < n - 1; i++)
        {
            s += temp;
        }
        return *this;
    }
    friend istream &operator>>(istream &stream, Word &w);
    friend ostream &operator<<(ostream &out, Word &w);
};

class Datha
{
private:
    vector<int> v;

public:
    Datha() {}
    Datha(vector<int> a) : v(a) {}
    int operator[](int i)
    {
        return v[i];
    }
    Datha &operator+(int n)
    {
        v.push_back(n);
        return *this;
    }
    vector<int> *operator->()
    {
        return &v;
    }
};



istream &operator>>(istream &stream, Word &w)
{
    stream >> w.s;
    return stream;
}

ostream &operator<<(ostream &out, Word &w)
{
    out << w.s;
    return out;
}

ostream &operator<<(ostream &out, Number &n)
{
    out << n.num;
    return out;
}

istream &operator>>(istream &stream, Number &n)
{
    stream >> n.num;
    return stream;
}

int main()
{
    // Number n1,n2;
    // cin>>n1>>n2;
    // cout<<n1+2<<endl;
    // cout<<2+n1<<endl;

    // cout << n1 << endl;
    // cout << n2 << endl;
    // cout << n1 + n2 << endl;
    // cout << n1 - n2 << endl;
    // cout << ++n1 << endl;

    // Number *n = new Number(5);
    // cout<<*n<<endl;
    // delete n;

    // Word w1;
    // cin>>w1;
    // cout << w1 << endl;
    // cout << w1*3 << endl;

    // Datha d({1, 2, 3, 4, 5});
    // d + 6;
    // d + 7;
    // d + 8 + 9;
    // cout << d[8] << endl;

    // cout << d->back() << endl;


    return 0;
}