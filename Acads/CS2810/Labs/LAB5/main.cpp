#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

class CurrencySorter
{
public:
    void partition(vector<int> &nums, int low, int high, int &pivotIndex)
    {
        // Partions the array into two parts, one with elements less than the pivot and the other with elements greater than the pivot
        int pivot = nums[high];
        int i = low - 1;
        for (int j = low; j < high; j++)
        {
            if (nums[j] < pivot)
            {
                i++;
                swap(nums[i], nums[j]);
            }
        }
        swap(nums[i + 1], nums[high]); // Place the pivot element in its correct position
        pivotIndex = i + 1;
    }

    void quickSort(vector<int> &nums, int low, int high)
    {
        if (low < high)
        {
            int pivotIndex;
            partition(nums, low, high, pivotIndex); // Partition the array
            quickSort(nums, low, pivotIndex - 1);   // Recursively sort the left part
            quickSort(nums, pivotIndex + 1, high);  // Recursively sort the right part
        }
    }

    void operator()(vector<int> &nums)
    {
        quickSort(nums, 0, nums.size() - 1);
    }
};

class FibonacciGenerator
{
public:
    void multiply(long long (*F)[2], long long (*M)[2])
    {

        long long x = (F[0][0] * M[0][0] % MOD + F[0][1] * M[1][0] % MOD) % MOD;
        long long y = (F[0][0] * M[0][1] % MOD + F[0][1] * M[1][1] % MOD) % MOD;
        long long z = (F[1][0] * M[0][0] % MOD + F[1][1] * M[1][0] % MOD) % MOD;
        long long w = (F[1][0] * M[0][1] % MOD + F[1][1] * M[1][1] % MOD) % MOD;

        F[0][0] = x;
        F[0][1] = y;
        F[1][0] = z;
        F[1][1] = w;
    }

    void powerOfMatrix(long long (*F)[2], long long n)
    {
        if (n == 1)
            return;

        long long M[2][2] = {{1, 1}, {1, 0}};

        powerOfMatrix(F, n / 2);
        multiply(F, F); // Square the matrix

        if (n % 2 != 0)
            multiply(F, M); // Multiply by the original matrix
    }

    long long operator()(long long i)
    {
        if (i == 0)
            return 0;
        if (i == 1)
            return 1;

        long long F[2][2] = {{1, 1}, {1, 0}};
        powerOfMatrix(F, i - 1); // Compute F^(i-1)

        return F[0][0]; // The top-left element gives the i-th Fibonacci number
    }
};

class PrimeCalculator
{
public:
    vector<long long> listOfPrimes(long long L, long long R)
    {
        long long lim = 1000000;
        vector<bool> isPrime(lim + 1, true);
        isPrime[0] = isPrime[1] = false;

        // Sieve of Eratosthenes for finding primes upto 10^6
        for (long long i = 2; i * i <= lim; i++)
        {
            if (isPrime[i])
            {
                for (long long j = i * i; j <= lim; j += i)
                {
                    isPrime[j] = false;
                }
            }
        }

        // Store the primes upto 10^6
        vector<long long> smallPrimes;
        for (long long i = 2; i <= lim; i++)
        {
            if (isPrime[i])
                smallPrimes.push_back(i);
        }

        vector<bool> isPrimeInRange(R - L + 1, true);

        for (long long p : smallPrimes)
        {
            long long start = (L + p - 1) / p * p; // Find the first multiple of p in the range [L, R]
            for (long long j = start; j <= R; j += p)
            {
                if (j != p)
                    isPrimeInRange[j - L] = false; // Mark the multiples of p as non-prime
            }
        }

        vector<long long> primes;
        for (long long i = 0; i < R - L + 1; i++)
        {
            if (isPrimeInRange[i] && (i + L) >= 2)
                primes.push_back(i + L);
        }

        return primes;
    }

    void printPrimes(long long L, long long R)
    {
        // Print the primes in the range [L, R]
        vector<long long> primes = listOfPrimes(L, R);
        for (long long prime : primes)
        {
            cout << prime << " ";
        }
        cout << endl;
    }

    long long printPrimesSum(long long L, long long R)
    {
        // Return the sum of primes in the range [L, R]
        vector<long long> primes = listOfPrimes(L, R);
        return accumulate(primes.begin(), primes.end(), 0LL);
    }
};

class NumberAnalyzer
{
public:
    bool isSquareFree(int X) // Checks if a number is square free(Isn't divisible by a perfect square)
    {
        if (X % 4 == 0)
            return false;
        for (int i = 3; i * i <= X; i += 2)
        {
            if (X % (i * i) == 0) // If X is divisible by a perfect square
                return false;
        }
        return true;
    }
    int countDivisors(int X) // Returns the number of divisors
    {
        int numDivisors = 0;
        for (int i = 1; i * i <= X; i++)
        {
            if (X % i == 0)
                numDivisors += 2;
            if (i * i == X)
                numDivisors--;
        }
        return numDivisors;
    }
    long long sumOfDivisors(int X) // Returns the sum of divisors
    {
        long long sum = 0;
        for (int i = 1; i * i <= X; i++)
        {
            if (X % i == 0)
            {
                sum = sum + i + X / i;
            }
            if (i * i == X)
            {
                sum = sum - i;
            }
        }
        return sum;
    }
};

int main()
{
    int type;
    cin >> type;
    if (type == 1)
    {
        // Currency Sorter
        int t;
        cin >> t;
        CurrencySorter currencySorterObj;
        while (t--)
        {
            int n;
            cin >> n;
            vector<int> nums(n);
            for (int i = 0; i < n; i++)
                cin >> nums[i];
            currencySorterObj(nums);
            for (int i = 0; i < n; i++)
                cout << nums[i] << " ";
            cout << endl;
        }
    }
    else if (type == 2)
    {
        // Fibonacci Generator
        int t;
        cin >> t;
        FibonacciGenerator fibGenObj;
        while (t--)
        {
            long long n;
            cin >> n;
            cout << fibGenObj(n) << endl;
        }
    }
    else if (type == 3)
    {
        // Prime Calculator
        int t;
        cin >> t;
        PrimeCalculator primeCalculatorObj;
        while (t--)
        {
            string s;
            cin >> s;
            long long L, R;
            cin >> L >> R;
            if (s == "printPrimes")
            {
                primeCalculatorObj.printPrimes(L, R);
            }
            else
            {
                cout << primeCalculatorObj.printPrimesSum(L, R) << endl;
            }
        }
    }
    else
    {
        // Number Analyzer
        int t;
        cin >> t;
        while (t--)
        {

            NumberAnalyzer NumberAnalyerObj;
            string s;
            cin >> s;
            int x;
            cin >> x;
            if (s == "isSquareFree")
            {
                if (NumberAnalyerObj.isSquareFree(x))
                    cout << "yes" << endl;
                else
                    cout << "no" << endl;
            }
            else if (s == "countDivisors")
            {
                cout << NumberAnalyerObj.countDivisors(x) << endl;
            }
            else
            {
                cout << NumberAnalyerObj.sumOfDivisors(x) << endl;
            }
        }
    }
}