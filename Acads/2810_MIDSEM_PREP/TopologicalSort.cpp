#include <bits/stdc++.h>
using namespace std;

// Function to print the topological order of the graph
void topologicalSort(vector<vector<int>> &adjList, vector<bool> &visited, stack<int> &s, int node)
{
    visited[node] = true;
    for (int i = 0; i < adjList[node].size(); i++)
    {
        if (!visited[adjList[node][i]])
        {
            topologicalSort(adjList, visited, s, adjList[node][i]);
        }
    }
    s.push(node);
}

int main()
{
    // Directed Acyclic Graph
    vector<vector<int>> adjList = {{1, 2}, {2, 3}, {3}, {4}, {}};
    int n = adjList.size();
    vector<bool> visited(n, false);
    stack<int> s;

    for (int i = 1; i < n; i++)
    {
        if (!visited[i])
        {
            topologicalSort(adjList, visited, s, i);
        }
    }

    while (!s.empty())
    {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}