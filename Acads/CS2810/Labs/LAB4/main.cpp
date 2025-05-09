#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

#define MOD 1000000007

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int power(int x, int y, int M)
{
    if (y == 0)
        return 1;
    
    int p = power(x, y / 2, M) % M;
    p = (1LL * p * p) % M;

    return (y % 2 == 0) ? p : (1LL * x * p) % M;
}

//binary exponentiation using recursion
int exp(int a,int p){
    if(p==0) return 1;
    if(p%2==0){
        int x = exp(a,p/2);
        return x*x;
    }
    return a*exp(a,p-1);

}

class Complex
{
private:
    double a, b;

public:
    Complex() : a(0), b(0) {}
    Complex(double i, double j) : a(i), b(j) {}

    Complex operator+(const Complex &n2) const
    {
        return Complex(a + n2.a, b + n2.b);
    }

    Complex operator-(const Complex &n2) const
    {
        return Complex(a - n2.a, b - n2.b);
    }

    Complex operator*(const Complex &n2) const
    {
        return Complex(a * n2.a - b * n2.b, a * n2.b + b * n2.a);
    }

    friend ostream &operator<<(ostream &stream, const Complex &n);
};

ostream &operator<<(ostream &stream, const Complex &n)
{
    stream << setprecision(3) << fixed << n.a << " " << n.b;
    return stream;
}

class Rational
{
private:
    int p, q;

public:
    Rational() : p(0), q(1) {}
    Rational(int a, int b)
    {
        if (b == 0)
            throw invalid_argument("Denominator cannot be zero");
        p = a, q = b;
        reduce();
    }

    void operator+(const Rational &n) const
    {
        double a = (double)p / q;
        double b = (double)n.p / n.q;
        cout << fixed << setprecision(3) << a + b << "\n";
    }

    void operator-(const Rational &n) const
    {
        double a = (double)p / q;
        double b = (double)n.p / n.q;
        cout << fixed << setprecision(3) << a - b << "\n";
    }

    void operator*(const Rational &n) const
    {
        double a = (double)p / q;
        double b = (double)n.p / n.q;
        cout << fixed << setprecision(3) << a * b << "\n";
    }

    void reduce()
    {
        int factor = gcd(p, q);
        p /= factor;
        q /= factor;
        if (q < 0)
        {
            p = -p;
            q = -q;
        }
    }
    void print()
    {
        cout << p << " " << q << "\n";
    }

    friend ostream &operator<<(ostream &stream, const Rational &n);
};

ostream &operator<<(ostream &stream, const Rational &n)
{
    stream << fixed << setprecision(3) << (double)n.p / n.q;
    return stream;
}

class Natural
{
private:
    int n;

public:
    Natural(int num) : n(num) {}

    bool isPrime()
    {
        if (n <= 1)
            return false;
        for (int i = 2; i * i <= n; i++)
            if (n % i == 0)
                return false;
        return true;
    }

    int modularInverse()
    {
        if (gcd(n, MOD) != 1)
            return -1; // Modular inverse does not exist
        return power(n, MOD - 2, MOD);
    }
};

int main()
{
    int num_commands;
    cin >> num_commands;
    while (num_commands--)
    {
        string type, op;
        cin >> type >> op;

        if (type == "complex")
        {
            double a, b, c, d;
            cin >> a >> b >> c >> d;
            Complex c1(a, b), c2(c, d);
            if (op == "add")
                cout << c1 + c2 << "\n";
            else if (op == "sub")
                cout << c1 - c2 << "\n";
            else if (op == "mult")
                cout << c1 * c2 << "\n";
        }
        else if (type == "rational")
        {
            if (op == "reduce")
            {
                int p, q;
                cin >> p >> q;
                Rational r1(p, q);
                r1.reduce();
                r1.print();
            }
            else
            {
                int a, b, c, d;
                cin >> a >> b >> c >> d;
                Rational r1(a, b), r2(c, d);
                if (op == "add")
                    r1 + r2;
                else if (op == "sub")
                    r1 - r2;
                else if (op == "mult")
                    r1 * r2;
                
            }
        }
        else
        {
            int n;
            cin >> n;
            Natural N(n);
            if (op == "isprime")
                cout << N.isPrime() << "\n";
            else
                cout << N.modularInverse() << "\n";
        }
    }
}
