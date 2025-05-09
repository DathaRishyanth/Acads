#include <bits/stdc++.h>
using namespace std;

class Node
{
private:
    int hypeScore;
    int num; 

public:
    Node() {}
    Node(int x, int y) : hypeScore{x}, num{y} {}
    // Getters
    int getHypeScore() const
    {
        return hypeScore;
    }
    int getNum() const
    {
        return num;
    }
};

class GraphAlgorithm
{
public:
    vector<vector<Node>> adjList; // Adjacency list of the graph
    vector<int> hypeScores;       // Hype scores of each node

    GraphAlgorithm() {}
    GraphAlgorithm(int N)
    {
        adjList.resize(N + 1);
        hypeScores.resize(N + 1);
    }

    virtual void Query()
    {
        return;
    }

    friend istream &operator>>(istream &stream, GraphAlgorithm &G)
    { // Input the graph
        int n, m;
        stream >> n >> m;
        G.adjList.resize(n + 1);
        G.hypeScores.resize(n + 1);

        for (int i = 1; i <= n; i++)
        {
            stream >> G.hypeScores[i];
        }
        for (int i = 0; i < m; i++)
        {
            int x, y;
            stream >> x >> y;
            G.adjList[x].emplace_back(G.hypeScores[y], y);
        }
        return stream;
    }
};

class IsCycle : public GraphAlgorithm
{
public:
    bool Cycle; // Will be set to true if the graph has a cycle

    IsCycle(bool a = false) : Cycle{a} {}

    void Query()
    {
        // store all the nodes with indegree 0
        vector<int> indegree(adjList.size(), 0);
        for (int i = 1; i < adjList.size(); i++)
        {

            for (auto &j : adjList[i])
            {
                indegree[j.getNum()]++;
            }
        }

        queue<int> q;
        for (int i = 1; i < adjList.size(); i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }

        int count = 0;
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            count++;
            for (auto &neighbor : adjList[node])
            {
                indegree[neighbor.getNum()]--;
                if (indegree[neighbor.getNum()] == 0)
                {
                    q.push(neighbor.getNum());
                }
            }
        }
        // If not all nodes are processed, there is a cycle
        if (count < adjList.size() - 1)
        {
            Cycle = true;
        }
    }
};

class IndepComponent : public GraphAlgorithm
{
public:
    int numComponents;  // Number of SCCs
    int maxCardinality; // Maximum size of any SCC

    IndepComponent(int x, int y) : numComponents{x}, maxCardinality{y} {}

    void Query()
    {
        int n = adjList.size() - 1;                
        vector<vector<int>> adjListTranspose(n + 1); // Transposed graph

        // Building the Transposed Graph
        for (int i = 1; i <= n; i++)
        {
            for (auto &j : adjList[i])
            {
                adjListTranspose[j.getNum()].push_back(i);
            }
        }

        // First DFS to get the finishing order
        stack<int> s;
        vector<bool> visited(n + 1, false);

        function<void(int)> dfs1 = [&](int node)
        {
            visited[node] = true;
            for (auto &neighbor : adjList[node])
            {
                if (!visited[neighbor.getNum()])
                {
                    dfs1(neighbor.getNum());
                }
            }
            s.push(node);
        };

        for (int i = 1; i <= n; i++)
        {
            if (!visited[i])
            {
                dfs1(i);
            }
        }

        // Second DFS on the transposed graph to find SCCs
        fill(visited.begin(), visited.end(), false);
        int numComponents = 0, maxCardinality = 0;

        function<int(int)> dfs2 = [&](int node)
        {
            visited[node] = true;
            int size = 1;
            for (int neighbor : adjListTranspose[node])
            {
                if (!visited[neighbor])
                {
                    size += dfs2(neighbor);
                }
            }
            return size;
        };

        while (!s.empty())
        {
            int node = s.top();
            s.pop();

            if (!visited[node])
            {
                numComponents++;
                int cardinality = dfs2(node);
                maxCardinality = max(maxCardinality, cardinality);
            }
        }

        this->numComponents = numComponents;
        this->maxCardinality = maxCardinality;
    }
};

class ValidOrder : public GraphAlgorithm
{
public:
    vector<int> Order; // Stores the topological order

    ValidOrder() {}

    void Query()
    {
        int n = adjList.size() - 1;
        vector<int> indegree(n + 1, 0);
        priority_queue<int, vector<int>, greater<int>> pq;

        // Compute the indegree of each node
        for (int i = 1; i <= n; i++)
        {
            for (auto &j : adjList[i])
            {
                indegree[j.getNum()]++;
            }
        }

        // Push all nodes with indegree 0 into the priority queue
        for (int i = 1; i <= n; i++)
        {
            if (indegree[i] == 0)
            {
                pq.push(i);
            }
        }

        // Process nodes in topological order and lexigraphical order
        while (!pq.empty())
        {
            int node = pq.top();
            pq.pop();
            Order.push_back(node);

            for (auto &neighbor : adjList[node])
            {
                indegree[neighbor.getNum()]--;
                if (indegree[neighbor.getNum()] == 0)
                {
                    pq.push(neighbor.getNum());
                }
            }
        }

        // If all nodes are not processed, there is no valid order
        if (Order.size() < n)
        {
            Order.clear();
            Order.push_back(-1);
        }
    }
};

class MaxHype : public GraphAlgorithm
{
public:
    int maxHype; // Stores the max hype points

    MaxHype(int X) : maxHype(X) {}

    void Query()
    {
        int n = adjList.size() - 1;                 
        vector<vector<int>> adjListTranspose(n + 1); // Transposed graph

        // Building the Transposed Graph
        for (int i = 1; i <= n; i++)
        {
            for (auto &j : adjList[i])
            {
                adjListTranspose[j.getNum()].push_back(i);
            }
        }

        // First DFS to determine finishing order
        stack<int> s;
        vector<bool> visited(n + 1, false);

        function<void(int)> dfs1 = [&](int node)
        {
            visited[node] = true;
            for (auto &neighbor : adjList[node])
            {
                if (!visited[neighbor.getNum()])
                {
                    dfs1(neighbor.getNum());
                }
            }
            s.push(node);
        };

        for (int i = 1; i <= n; i++)
        {
            if (!visited[i])
            {
                dfs1(i);
            }
        }

        // Second DFS on Transposed Graph to Find SCCs
        fill(visited.begin(), visited.end(), false);
        vector<int> sccId(n + 1, -1); 
        vector<int> sccHype;          // Stores hype value of each SCC
        int sccCount = 0;

        function<int(int)> dfs2 = [&](int node)
        {
            visited[node] = true;
            int hypeSum = hypeScores[node];
            sccId[node] = sccCount;

            for (int neighbor : adjListTranspose[node])
            {
                if (!visited[neighbor])
                {
                    hypeSum += dfs2(neighbor);
                }
            }
            return hypeSum;
        };

        while (!s.empty())
        {
            int node = s.top();
            s.pop();

            if (!visited[node])
            {
                int hype = dfs2(node);
                sccHype.push_back(hype); 
                sccCount++;              
            }
        }

        //  Build Condensed Graph
        vector<vector<int>> sccGraph(sccCount);
        vector<int> inDegree(sccCount, 0); 

        for (int i = 1; i <= n; i++)
        {
            for (auto &j : adjList[i])
            {
                int u = sccId[i], v = sccId[j.getNum()];
                if (u != v)
                {
                    sccGraph[u].push_back(v);
                    inDegree[v]++;
                }
            }
        }

        // Compute Longest Path in DAG
        vector<int> dp(sccCount, 0);
        queue<int> q;

        // Push nodes with in-degree 0
        for (int i = 0; i < sccCount; i++)
        {
            if (inDegree[i] == 0)
            {
                q.push(i);
                dp[i] = sccHype[i];
            }
        }

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int v : sccGraph[u])
            {
                dp[v] = max(dp[v], dp[u] + sccHype[v]);
                if (--inDegree[v] == 0)
                {
                    q.push(v);
                }
            }
        }

        // Store the maximum total hype score
        this->maxHype = *max_element(dp.begin(), dp.end());
    }
};

class Comparator
{
public:
    bool operator()(Node &a, Node &b); // Compares 2 nodes for checking if a appears before b
};

int main()
{
    GraphAlgorithm G;
    cin >> G;

    GraphAlgorithm *I = new IsCycle();
    I->adjList = G.adjList;
    GraphAlgorithm *C = new IndepComponent(0, 0);
    C->adjList = G.adjList;
    GraphAlgorithm *V = new ValidOrder();
    V->adjList = G.adjList;
    GraphAlgorithm *M = new MaxHype(0);
    M->adjList = G.adjList;
    M->hypeScores = G.hypeScores;

    I->Query();
    C->Query();
    V->Query();
    M->Query();

    int q;
    cin >> q;
    while (q--)
    {
        int x;
        cin >> x;
        if (x == 1)
        {
            if (((IsCycle *)I)->Cycle)
            {
                cout << "YES" << endl;
            }
            else
            {
                cout << "NO" << endl;
            }
        }
        else if (x == 2)
        {
            cout << ((IndepComponent *)C)->numComponents << " " << ((IndepComponent *)C)->maxCardinality << endl;
        }
        else if (x == 3)
        {
            if (((ValidOrder *)V)->Order[0] == -1)
            {
                cout << "NO" << endl;
                continue;
            }
            for (auto &i : ((ValidOrder *)V)->Order)
            {
                cout << i << " ";
            }
            cout << endl;
        }
        else if (x == 4)
        {
            cout << ((MaxHype *)M)->maxHype << endl;
        }
    }

    delete I;
    delete C;
    delete V;
    delete M;
}