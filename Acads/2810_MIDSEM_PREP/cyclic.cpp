#include <bits/stdc++.h>
using namespace std;

bool isCyclicUtil(vector<vector<int>> &adjList, vector<bool> &visited, vector<bool> &recStack, int node)
{
    if (!visited[node])
    {
        visited[node] = true;
        recStack[node] = true;
        for (int i = 0; i < adjList[node].size(); i++)
        {
            if (!visited[adjList[node][i]] && isCyclicUtil(adjList, visited, recStack, adjList[node][i]))
            {
                return true;
            }
            else if (recStack[adjList[node][i]])
            {
                return true;
            }
        }
    }
    recStack[node] = false;
    return false;
}

bool isCyclic(vector<vector<int>> &adjList)
{
    int n = adjList.size();
    vector<bool> visited(n, false);
    vector<bool> recStack(n, false);
    for (int i = 0; i < n; i++)
    {
        if (isCyclicUtil(adjList, visited, recStack, i))
        {
            return true;
        }
    }
    return false;
}