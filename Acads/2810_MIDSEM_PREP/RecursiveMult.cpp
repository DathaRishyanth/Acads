#include <iostream>
#include <cmath>

using namespace std;

long long splitMultiply(long long x, long long y) {
    if (x < 10 || y < 10)  // Base case: single-digit multiplication
        return x * y;

    int n = max((int)log10(x) + 1, (int)log10(y) + 1); // Get number of digits
    int m = n / 2; // Split at half the digits

    long long power = pow(10, m); // Convert to integer safely
    long long a = x / power;
    long long b = x % power;
    long long c = y / power;
    long long d = y % power;

    long long e = splitMultiply(a, c);
    long long h = splitMultiply(b, d);
    long long f = splitMultiply(a + b, c + d) - e - h;

    return power * power * e + power * (f) + h;
}

int main() {
    long long x = 1234, y = 5678;
    cout << splitMultiply(x, y) << endl; // Expected: 1234 * 5678 = 7006652
    cout<<x*y<<endl;
    return 0;
}
