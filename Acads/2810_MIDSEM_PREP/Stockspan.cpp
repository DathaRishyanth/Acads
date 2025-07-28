#include <bits/stdc++.h>
using namespace std;

struct SubarrayInfo {
    int totalSum;
    int maxSum;
    int maxPrefix;
    int maxSuffix;
};

SubarrayInfo Compare(SubarrayInfo L, SubarrayInfo R) {
    SubarrayInfo result;
    result.totalSum = L.totalSum + R.totalSum;
    result.maxPrefix = max(L.maxPrefix, L.totalSum + R.maxPrefix);
    result.maxSuffix = max(R.maxSuffix, R.totalSum + L.maxSuffix);
    result.maxSum = max({L.maxSum, R.maxSum, L.maxSuffix + R.maxPrefix});
    return result;
}

SubarrayInfo FMS_COMPARE(vector<int> &A, int low, int high) {
    if (low == high) {
        return {A[low], A[low], A[low], A[low]};
    }
    
    int mid = (low + high) / 2;
    SubarrayInfo Left = FMS_COMPARE(A, low, mid);
    SubarrayInfo Right = FMS_COMPARE(A, mid + 1, high);
    
    return Compare(Left, Right);
}

int main() {
    vector<int> stockPrices = {100, 180, 260, 310, 40, 535, 695};
    vector<int> diffArray;
    for (int i = 1; i < stockPrices.size(); i++) {
        diffArray.push_back(stockPrices[i] - stockPrices[i - 1]);
    }
    SubarrayInfo result = FMS_COMPARE(diffArray, 0, diffArray.size() - 1);
    cout << "Maximum Subarray Sum: " << result.maxSum << endl;
    return 0;
}
