#include <bits/stdc++.h>
using namespace std;

// Partition function that correctly places the pivot
int Partition(vector<int> &v, int l, int r, int pivot) {
    int i = l, j = r;
    while (i <= j) {
        while (v[i] < pivot) i++;
        while (v[j] > pivot) j--;
        if (i <= j) {
            swap(v[i], v[j]);
            i++;
            j--;
        }
    }
    return j;  // Returning the last index of left partition
}

// Find kth smallest element using Median of Medians
int kthSmallest(vector<int> v, int k) {
    if(v.size() == 1) return v[0];

    // Step 1: Find medians of groups of 5
    vector<int> medians;
    for (int i = 0; i < v.size(); i += 5) {
        vector<int> temp;
        for (int j = i; j <i + 5 && j < v.size(); j++) {
            temp.push_back(v[j]);
        }
        sort(temp.begin(), temp.end());
        medians.push_back(temp[temp.size() / 2]);
    }

    // Step 2: Find median of medians (recursively)
    int mom = (medians.size() == 1) ? medians[0] : kthSmallest(medians, medians.size() / 2);

    // Step 3: Partition the array around mom
    int pos = Partition(v, 0, v.size() - 1, mom);
    int count = pos + 1; // Elements <= mom

    if (count == k) return mom;
    if (count > k) {
        vector<int> left(v.begin(), v.begin() + pos + 1);
        return kthSmallest(left, k);
    } else {
        vector<int> right(v.begin() + pos + 1, v.end());
        return kthSmallest(right, k - count);
    }
}

// QuickSort function using Median of Medians
void quickSort(vector<int> &v, int l, int r) {
    if (l >= r) return;

    int pivot = kthSmallest(vector<int>(v.begin() + l, v.begin() + r + 1), (r - l) / 2 + 1);
    int pos = Partition(v, l, r, pivot);
    
    quickSort(v, l, pos);
    quickSort(v, pos + 1, r);
}

void insertionSort(vector<int> &v, int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        int key = v[i];
        int j = i - 1;
        while (j >= l && v[j] > key) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
    }
}

// Driver code
int main() {
    vector<int> v = {5, 4, 3, 2, 1,9,10,15,12,11,13,14,8,7,6};
    quickSort(v, 0, v.size() - 1);

    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    return 0;
}
