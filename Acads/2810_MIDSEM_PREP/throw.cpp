#include <bits/stdc++.h>
using namespace std;

bool search(array<int, 10> a, int key) {
    for (int ii = 0; ii < a.size(); ++ii)
            if (a[ii] == key)
                    throw true;
    return false;
}
int main() {
    array<int, 10> a;
    a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int key = 3;
    try {
            bool found = search(a, key);
            cout << "key " << key << " is not present in the array.\n";
    } catch (...) {
            cout << "key " << key << " is present in the array.\n";
    }
}
