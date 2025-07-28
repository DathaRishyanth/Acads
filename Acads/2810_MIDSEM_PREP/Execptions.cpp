#include <bits/stdc++.h>
using namespace std;
string s;
void fun()
{
    try
    {
        try
        {
            s.insert(1, "Hello");
        }
        catch (std::out_of_range)
        {
            cout << "caught in fun: out of range\n";
            throw;
        }
    }
    catch (std::exception &e)
    {
        cout << "Caught in fun.\n";
    }
    cout << "continue with fun\n";
}

int main()
{
    try
    {
        fun();
    }
    catch (std::exception &e)
    {
        cout << "The exception is caught." << endl;
        exit(1);
    }
    cout << "The program ends now.\n";
}

