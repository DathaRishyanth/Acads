#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double

// Complex Number class

class ComplexNumber
{
public:
    ll real, imaginary;
    ComplexNumber()
    {
        real = 0;
        imaginary = 0;
    }
    ComplexNumber(ll real, ll imaginary)
    {
        this->real = real;
        this->imaginary = imaginary;
    }
    ComplexNumber operator+(ComplexNumber &c) // Overloading + operator
    {
        return ComplexNumber(this->real + c.real, this->imaginary + c.imaginary);
    }
    ComplexNumber operator-(ComplexNumber &c) // Overloading - operator
    {
        return ComplexNumber(this->real - c.real, this->imaginary - c.imaginary);
    }
    ComplexNumber operator*(ComplexNumber &c) // Overloading * operator
    {
        return ComplexNumber(this->real * c.real - this->imaginary * c.imaginary, this->real * c.imaginary + this->imaginary * c.real);
    }
};

template <typename T>
class Polynomial
{
public:
    ll degree;
    vector<T> coefficients;
    Polynomial(ll degree)
    {
        this->degree = degree;
        coefficients.resize(degree);
    }

    // Overloading >> operator for input
    friend istream &operator>>(istream &in, Polynomial<T> &p)
    {
        for (ll i = 0; i < p.degree; i++)
        {
            in >> p.coefficients[i];
        }
        return in;
    }

    // Overloading + operator for addition of two polynomials
    Polynomial<T> operator+(Polynomial<T> &p)
    {
        ll max_degree = max(this->degree, p.degree);
        Polynomial<T> sum(max_degree);
        for (ll i = 0; i < max_degree; i++)
        {
            sum.coefficients[i] = (i < this->degree ? this->coefficients[i] : T()) + (i < p.degree ? p.coefficients[i] : T());

        }
        return sum;
    }

    // Overloading - operator for subtraction of two polynomials
    Polynomial<T> operator-(Polynomial<T> &p)
    {
        ll max_degree = max(this->degree, p.degree);
        Polynomial<T> diff(max_degree);
        for (ll i = 0; i < max_degree; i++)
        {
            if (i < this->degree)
            {
                diff.coefficients[i] = this->coefficients[i];
            }
            if (i < p.degree)
            {
                diff.coefficients[i] = diff.coefficients[i] - p.coefficients[i];
            }
        }
        return diff;
    }
};

template <>
class Polynomial<ComplexNumber>
{
public:
    ll degree;
    vector<ComplexNumber> coefficients;
    Polynomial(ll degree)
    {
        this->degree = degree;
        coefficients.resize(degree);
    }

    // Overloading >> operator for input 
    friend istream &operator>>(istream &in, Polynomial<ComplexNumber> &p)
    {
        for (ll i = 0; i < p.degree; i++)
        {
            ll real, imag;
            in >> real >> imag;
            p.coefficients[i] = ComplexNumber(real, imag);
        }
        return in;
    }
    // Overloading + operator for addition of two polynomials
    Polynomial<ComplexNumber> operator+(Polynomial<ComplexNumber> &p)
    {
        ll max_degree = max(this->degree, p.degree);
        Polynomial<ComplexNumber> sum(max_degree);
        for (ll i = 0; i < max_degree; i++)
        {
            sum.coefficients[i].real = (i < this->degree ? this->coefficients[i].real : 0) + (i < p.degree ? p.coefficients[i].real : 0);
            sum.coefficients[i].imaginary = (i < this->degree ? this->coefficients[i].imaginary : 0) +(i < p.degree ? p.coefficients[i].imaginary : 0);

        }
        return sum;
    }

    // Overloading - operator for subtraction of two polynomials
    Polynomial<ComplexNumber> operator-(Polynomial<ComplexNumber> &p)
    {
        ll max_degree = max(this->degree, p.degree);
        Polynomial<ComplexNumber> diff(max_degree);
        for (ll i = 0; i < max_degree; i++)
        {
            if (i < this->degree)
            {
                diff.coefficients[i] = this->coefficients[i];
            }
            if (i < p.degree)
            {
                diff.coefficients[i] = diff.coefficients[i] - p.coefficients[i];
            }
        }
        return diff;
    }
};

template <typename T>
class Multiplication
{
public:
    Polynomial<T> karatsubaMultiply(Polynomial<T> &p, Polynomial<T> &q)
    {
        ll n = max(p.degree, q.degree);

        
        if (n == 1)
        {
            Polynomial<T> res(1);
            res.coefficients[0] = p.coefficients[0] * q.coefficients[0];
            return res;
        }   

        ll m = n / 2;

        // Splitting polynomials into lower and higher degree parts
        Polynomial<T> p_low(m), p_high(n - m), q_low(m), q_high(n - m);

        for (ll i = 0; i < m; i++)
        {
            if (i < p.degree)
                p_low.coefficients[i] = p.coefficients[i];
            if (i < q.degree)
                q_low.coefficients[i] = q.coefficients[i];
        }
        for (ll i = m; i < n; i++)
        {
            if (i < p.degree)
                p_high.coefficients[i - m] = p.coefficients[i];
            if (i < q.degree)
                q_high.coefficients[i - m] = q.coefficients[i];
        }

        // Recursively compute three multiplications
        Polynomial<T> r1 = karatsubaMultiply(p_low, q_low);
        Polynomial<T> r2 = karatsubaMultiply(p_high, q_high);

        Polynomial<T> sum_p = p_low + p_high;
        Polynomial<T> sum_q = q_low + q_high;
        Polynomial<T> r3 = karatsubaMultiply(sum_p, sum_q);

       
        r3 = r3 - r1 - r2;
        // Construct the result polynomial
        Polynomial<T> result(2 * n - 1);
        for (ll i = 0; i < r1.degree; i++)
            result.coefficients[i] = r1.coefficients[i];
        for (ll i = 0; i < r3.degree; i++)
            result.coefficients[i + m]  = result.coefficients[i + m] + r3.coefficients[i];
        for (ll i = 0; i < r2.degree; i++)
            result.coefficients[i + 2 * m] = result.coefficients[i + 2 * m] + r2.coefficients[i];

        return result;
    }
};


template <typename T>
class Evaluation : public Polynomial<T>
{
public:
    Evaluation(ll degree) : Polynomial<T>(degree) {}
    // Using Horner's method to evaluate the polynomial
    T evaluate(T x)
    {

        T result = this->coefficients[0];
        ll x_power = x;
        for (ll i = 1; i < this->degree; i++)
        {
            result += this->coefficients[i] * x_power;
            x_power *= x;
        }
        return result;
    }


};

template <>
class Evaluation<string> : public Polynomial<string>
{
public:
    Evaluation(ll degree) : Polynomial<string>(degree) {}
    string evaluate(ll x)
    {
        
        string result = "";
        ll x_power = pow(x, degree - 1);
        for (int i = degree - 1; i >= 0; i--)
        {
            for (ll j = 0; j < x_power; j++)
            {
                result += this->coefficients[i];
            }
            x_power /= x;
        }
        return result;
    }

};

template <typename T>
class Differentiator : public Polynomial<T>
{
public:
    Differentiator(ll degree) : Polynomial<T>(degree) {}
    Polynomial<T> differentiate()
    {
        // Differentiation of a constant polynomial is 0
        if (this->degree == 0)
        {
            Polynomial<T> diff(0);
            diff.coefficients[0] = 0;
            return diff;
        }
        Polynomial<T> diff(this->degree - 1);
        for (ll i = 0; i < this->degree - 1; i++)
        {
            // Differentiation of a polynomial ax^n is n*ax^(n-1)
            diff.coefficients[i] = this->coefficients[i + 1] * (i + 1);
        }
        return diff;
    }
};

int main()
{
    ll q;
    cin >> q;
    while (q--)
    {
        ll t;
        cin >> t;
        if (t == 1)
        {
            string s;
            cin >> s;
            if (s == "complex")
            {
                ll n;
                cin >> n;
                Polynomial<ComplexNumber> p1(n);
                cin >> p1;
                ll m;
                cin >> m;
                Polynomial<ComplexNumber> p2(m);
                cin >> p2;
                Multiplication<ComplexNumber> Mult;
                Polynomial<ComplexNumber> result = Mult.karatsubaMultiply(p1, p2);
                for(int i = 0;i<n+m-1;i++){
                    cout << result.coefficients[i].real << " " << result.coefficients[i].imaginary << " ";
                }
                cout << endl;
            }
            else if (s == "integer")
            {
                ll n;
                cin >> n;
                Polynomial<ll> p1(n);
                cin >> p1;
                ll m;
                cin >> m;
                Polynomial<ll> p2(m);
                cin >> p2;
                Multiplication<ll> Mult;
                Polynomial<ll> result = Mult.karatsubaMultiply(p1, p2);
                for (ll i = 0; i < n+m-1; i++)
                {
                    cout << result.coefficients[i] << " ";
                }
                cout << endl;
            }
            else if (s == "float")
            {
                ll n;
                cin >> n;
                Polynomial<ld> p1(n);
                cin >> p1;
                ll m;
                cin >> m;
                Polynomial<ld> p2(m);
                cin >> p2;
                Multiplication<ld> Mult;
                Polynomial<ld> result = Mult.karatsubaMultiply(p1, p2);
                for (ll i = 0; i < n+m-1; i++)
                {
                    cout << fixed << setprecision(6) << result.coefficients[i] << " ";
                   
                }
                cout << endl;
            }
        }
        else if(t == 2){
            string s;
            cin >> s;
            if(s == "integer"){
                ll n;
                cin >> n;
                Evaluation<ll> e(n);
                cin >> e;
                ll x;
                cin >> x;
                cout << e.evaluate(x) << endl;
            }
            else if(s == "float"){
                ll n;
                cin >> n;
                Evaluation<ld> e(n);
                cin >> e;
                ld x;
                cin >> x;
                cout << fixed << setprecision(6) << e.evaluate(x) << endl;
            }
            else if(s == "string"){
                ll n;
                cin >> n;
                Evaluation<string> e(n);
                cin >> e;
                ll x;
                cin >> x;
                cout << e.evaluate(x) << endl;
            }
        }
        else if(t == 3){
            string s;
            cin >> s;
            
            if(s == "integer"){
                ll n;
                cin >> n;
                Differentiator<ll> d(n);
                cin >> d;
                Polynomial<ll> result = d.differentiate();
                for(ll i = 0; i < result.degree; i++){
                    cout << result.coefficients[i] << " ";
                }
                cout << endl;
            }
            else if(s == "float"){
                ll n;
                cin >> n;
                Differentiator<ld> d(n);
                cin >> d;
                Polynomial<ld> result = d.differentiate();
                for(ll i = 0; i < result.degree; i++){
                    cout << fixed << setprecision(6) << result.coefficients[i] << " ";
                    
                }
                cout << endl;
            }
        }
    }
}