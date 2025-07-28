#include <bits/stdc++.h>
using namespace std;

// Function to multiply two matrices using Strassen's algorithm
vector<vector<int>> strassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }
    
    // Splitting matrices into quadrants
    int k = n / 2;
    vector<vector<int>> A11(k, vector<int>(k)), A12(k, vector<int>(k)), A21(k, vector<int>(k)), A22(k, vector<int>(k));
    vector<vector<int>> B11(k, vector<int>(k)), B12(k, vector<int>(k)), B21(k, vector<int>(k)), B22(k, vector<int>(k));
    
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];
            
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }
    // Calculating M1 to M7
    vector<vector<int>> M1 = strassen(A11, B12 - B22);
    vector<vector<int>> M2 = strassen(A11 + A12, B22);
    vector<vector<int>> M3 = strassen(A21 + A22, B11);
    vector<vector<int>> M4 = strassen(A22, B21 - B11);
    vector<vector<int>> M5 = strassen(A11 + A22, B11 + B22);
    vector<vector<int>> M6 = strassen(A12 - A22, B21 + B22);
    vector<vector<int>> M7 = strassen(A11 - A21, B11 + B12);

    // Combining results into C
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = M5[i][j] + M4[i][j] - M2[i][j] + M6[i][j];
            C[i][j + k] = M1[i][j] + M2[i][j];
            C[i + k][j] = M3[i][j] + M4[i][j];
            C[i + k][j + k] = M5[i][j] - M3[i][j] - M7[i][j] + M1[i][j];
        }
    }
    return C;
}