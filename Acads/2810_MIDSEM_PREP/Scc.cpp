#include <bits/stdc++.h>
using namespace std;

// Function to perform DFS and find strongly connected components
void dfs(int node, vector<vector<int>>& adjList, vector<bool>& visited, stack<int>& Stack) {
    visited[node] = true;
    for (int neighbor : adjList[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adjList, visited, Stack);
        }
    }
    Stack.push(node);
}


int main(){
    vector<vector<int>> adjList(5);
    adjList[0] = {1, 2};
    adjList[1] = {0, 3, 4};
    adjList[2] = {0};
    adjList[3] = {1};
    adjList[4] = {1};

    vector<bool> visited(5, false);
    stack<int> Stack;
    for (int i = 0; i < 5; i++) {
        if (!visited[i]){
            dfs(i, adjList, visited, Stack);
        }
    }

    vector<vector<int>> transposedAdjList(5);
    for (int i = 0; i < 5; i++) {
        for (int neighbor : adjList[i]) {
            transposedAdjList[neighbor].push_back(i);
        }
    }

    fill(visited.begin(), visited.end(), false);
    vector<vector<int>> sccs;
    while (!Stack.empty()) {
        int node = Stack.top();
        Stack.pop();
        if (!visited[node]){
            vector<int> scc;
            dfs(node, transposedAdjList, visited, Stack);
            for (int i = 0; i < 5; i++){
                if (visited[i]){
                    scc.push_back(i);
                    visited[i] = false;
                }
            }
            sccs.push_back(scc);
        }
    }





}