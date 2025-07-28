#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

long long modularExpo(long long a, long long b)
{
    long long res = 1;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            res = (res * a) % MOD;
        }
        a = (a * a) % MOD;
        b /= 2;
    }
    return res;
}