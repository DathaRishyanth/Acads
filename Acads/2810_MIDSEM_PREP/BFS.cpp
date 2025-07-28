#include <bits/stdc++.h>
using namespace std;

void dfs(vector<vector<int>> &adjList, vector<bool> &visited, int node){
    visited[node] = true;
    cout << node << " ";
    for(int i = 0; i < adjList[node].size(); i++){
        if(!visited[adjList[node][i]]){
            dfs(adjList, visited, adjList[node][i]);
        }
    }
    
}

void bfs(vector<vector<int>>& adjList, vector<bool>&visited, int node){
    queue<int> q;
    q.push(node);
    
    while(!q.empty()){
        int a = q.front();
        q.pop();
        visited[a] = true;

        for(auto &n : adjList[a]){
            if(!visited[])
        }

    }
}

int main(){
    //disccnnected graph
    vector<vector<int>> adjList = {{1, 2}, {0, 3}, {0, 3}, {1, 2}, {5}, {4}};
    int n = adjList.size();
    vector<bool> visited(n, false);
    bool isDisconnected = false;
    dfs(adjList, visited, 0);
    for(int i = 0; i < n; i++){
        if(!visited[i]){
            isDisconnected = true;
            break;
        }
    }

    if(isDisconnected){
        cout << "Graph is disconnected" << endl;
    } else {
        cout << "Graph is connected" << endl;
    }
   
}
