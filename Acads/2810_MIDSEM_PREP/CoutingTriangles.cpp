#include <bits/stdc++.h>
using namespace std;

int countTriangles(vector<vector<int>> &adjList, int n){
    int count = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < adjList[i].size(); j++){
            for(int k = 0; k < adjList[adjList[i][j]].size(); k++){
                if(find(adjList[adjList[adjList[i][j]][k]].begin(), adjList[adjList[adjList[i][j]][k]].end(), i) != adjList[adjList[adjList[i][j]][k]].end()){
                    count++;
                }
            }
        }
    }
    return count;
}



int main(){
    //a graph with some 10 vertices and triangles within it
    vector<vector<int>> adjList = {{1, 2}, {0, 3}, {0, 3}, {1, 2}, {5}, {4}, {6, 7, 8}, {6, 8}, {6, 7}, {}};
    int n = adjList.size();
    int count = 0;
    
}