#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;

class Graph
{
private:
    vector<vector<int>> adj;

public:
    friend istream &operator>>(istream &stream, Graph &g);
    friend ostream &operator<<(ostream &stream, Graph &g);

    // overloading + operator
    void operator+(Graph &g)
    {
        int n1 = adj.size();
        int n2 = g.adj.size();

        // resize the vector if the size of the graph is smaller than the graph to be added
        int n = max(n1, n2);
        adj.resize(n);
        for (int i = 0; i < n; i++)
        {
            adj[i].resize(n);
        }
        g.adj.resize(n);
        for (int i = 0; i < n; i++)
        {
            g.adj[i].resize(n);
        }

        for (int i = 0; i < adj.size(); i++)
        {
            for (int j = 0; j < adj[0].size(); j++)
            {
                adj[i][j] = adj[i][j] || g.adj[i][j];
                adj[j][i] = adj[j][i] || g.adj[j][i];
            }
        }
    }

    void operator-(Graph &g)
    {
        int n1 = adj.size();
        int n2 = g.adj.size();

        // resize the vector if the size of the graph is smaller than the graph to be added
        int n = max(n1, n2);
        adj.resize(n);
        for (int i = 0; i < n; i++)
        {
            adj[i].resize(n);
        }
        g.adj.resize(n);
        for (int i = 0; i < n; i++)
        {
            g.adj[i].resize(n);
        }

        for (int i = 0; i < adj.size(); i++)
        {
            for (int j = 0; j < adj[0].size(); j++)
            {
                adj[i][j] = adj[i][j] && g.adj[i][j];
                adj[j][i] = adj[j][i] && g.adj[j][i];
            }
        }
    }

    // overloading ! operator
    void operator!()
    {
        for (int i = 0; i < adj.size(); i++)
        {
            for (int j = 0; j < adj.size(); j++)
            {
                if (i != j)
                {
                    adj[i][j] = 1 - adj[i][j];
                }
            }
        }
    }

    // Function to check if there is a path between u and v
    bool isReachable(int u, int v)
    {
        int n = adj.size();
        vector<bool> visited(n, false);

        queue<int> q;
        q.push(u);
        visited[u] = true;

        while (!q.empty())
        {
            int f = q.front();
            q.pop();

            if (v == f)
                return true;

            for (int j = 0; j < n; j++)
            {
                if (adj[f][j] && !visited[j])
                {
                    q.push(j);
                    visited[j] = true;
                }
            }
        }
        return false;
    }

    void addEdge(int u, int v)
    {
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    void removeEdge(int u, int v)
    {
        adj[u][v] = 0;
        adj[v][u] = 0;
    }
};

// Operator for graph input
istream &operator>>(istream &stream, Graph &g)
{
    int n, m;
    stream >> n >> m;
    g.adj.resize(n);
    for (int i = 0; i < n; i++)
    {
        g.adj[i].resize(n);
    }
    while (m--)
    {
        int u, v;
        stream >> u >> v;
        g.adj[u][v] = 1;
        g.adj[v][u] = 1;
    }
    return stream;
}

// Operator for Graph output
ostream &operator<<(ostream &stream, Graph &g)
{
    int n = g.adj.size();
    for (int i = 0; i < n; i++)
    {
        stream << "Vertex " << i << ":";
        for (int j = 0; j < n; j++)
        {
            if (g.adj[i][j] && g.adj[j][i])
            {
                stream << " " << j;
            }
        }
        stream << "\n";
    }
    return stream;
}

int main()
{
    string cmd;
    cin >> cmd;
    Graph G;
    while (true)
    {
        if (cmd == "Graph")
        {
            cin >> G;
        }
        else if (cmd == "printGraph")
        {
            cout << G;
        }
        else if (cmd == "union")
        {
            string temp;
            cin >> temp;
            Graph G1;
            cin >> G1;
            G + G1;
        }
        else if (cmd == "intersection")
        {
            string temp;
            cin >> temp;
            Graph G2;
            cin >> G2;
            G - G2;
        }
        else if (cmd == "complement")
        {
            !G;
        }
        else if (cmd == "isReachable")
        {
            int u, v;
            cin >> u >> v;
            if (G.isReachable(u, v))
                cout << "Yes" << "\n";
            else
                cout << "No" << "\n";
        }
        else if (cmd == "add_edge")
        {
            int u, v;
            cin >> u >> v;
            G.addEdge(u, v);
        }
        else if (cmd == "remove_edge")
        {
            int u, v;
            cin >> u >> v;
            G.removeEdge(u, v);
        }
        else if (cmd == "end")
        {
            return 0;
        }
        cin >> cmd;
    }
}