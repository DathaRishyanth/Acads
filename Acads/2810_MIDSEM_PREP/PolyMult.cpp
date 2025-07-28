#include <bits/stdc++.h>
using namespace std;
#define M_PI 3.14159265358979323846

typedef complex<double> cd;

// Recursive FFT function
void fft(vector<cd> &a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[i * 2];   // Even indices
        a1[i] = a[i * 2 + 1]; // Odd indices
    }

    fft(a0, invert);
    fft(a1, invert);

    double angle = 2 * M_PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(angle), sin(angle));

    for (int i = 0; 2 * i < n; i++) {
        cd t = w * a1[i];
        a[i] = a0[i] + t;
        a[i + n / 2] = a0[i] - t;
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

vector<int> multiply(vector<int> &a, vector<int> &b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1; 

    fa.resize(n);
    fb.resize(n);

    fft(fa, false); 
    fft(fb, false); 

    for (int i = 0; i < n; i++)
        fa[i] *= fb[i]; 

    fft(fa, true); 

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real()); 

    return result;
}

// Driver code
int main() {
    vector<int> p = {3, 2, 5};
    vector<int> q = {1, 4, 2};  

    vector<int> result = multiply(p, q);

    cout << "Resultant Polynomial Coefficients: ";
    for (int coeff : result)
        cout << coeff << " ";
    cout << endl;

    return 0;
}
