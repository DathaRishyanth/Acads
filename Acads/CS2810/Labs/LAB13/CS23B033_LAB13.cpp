#include <bits/stdc++.h>
using namespace std;

class Sentinel
{
protected:
    int id;
    string name;
    string rank;
    vector<Sentinel *> children; // children of the sentinel

public:
    Sentinel() {}
    virtual ~Sentinel() {}
    Sentinel(int _id, string _name, string _rank) : id(_id), name(_name), rank(_rank) {}
    virtual int countHigherRanked(vector<int> &nums) = 0; 

    // Getters
    int getID() { return id; }
    string getName() { return name; }
    string getRank() { return rank; }

    void addChild(Sentinel *child)
    {
        children.push_back(child);
    }

    vector<Sentinel *> &getChildren()
    {
        return children;
    }
};

class Senapati : public Sentinel
{
public:
    Senapati(int id, string name) : Sentinel(id, name, "SENAPATI") {}
    int countHigherRanked(vector<int> &nums)
    {
        return 0; // Senapati has no higher ranked sentinels
    }
};

class Dandanayaka : public Sentinel
{
public:
    Dandanayaka(int id, string name) : Sentinel(id, name, "DANDANAYAKA") {}
    int countHigherRanked(vector<int> &nums)
    {
        return nums[0]; // Dandanayaka has one higher ranked sentinel (Senapati)
    }
};

class Chaturangini : public Sentinel
{
public:
    Chaturangini(int id, string name) : Sentinel(id, name, "CHATURANGINI") {}
    int countHigherRanked(vector<int> &nums)
    {
        return nums[0] + nums[1]; // Chaturangini has two higher ranked sentinels (Senapati and Dandanayaka)
    }
};

class Comparator
{
public:
    bool operator()(pair<string, int> a, pair<string, int> b)
    { // comparator functor
        map<string, int> rankValue = {
            {"CHATURANGINI", 0},
            {"DANDANAYAKA", 1},
            {"SENAPATI", 2}};

        if (rankValue[a.first] == rankValue[b.first])
        {
            return a.second < b.second;
        }
        return rankValue[a.first] > rankValue[b.first];
    }
};

void dfs(Sentinel *root, vector<bool> &visited, vector<vector<int>> &dp)
{
    dp[root->getID()][1] = 1;
    dp[root->getID()][0] = 0;
    visited[root->getID()] = true;
    for (auto &node : root->getChildren())
    {
        if (!visited[node->getID()])
        {
            dfs(node, visited, dp);
            dp[root->getID()][1] += min(dp[node->getID()][0], dp[node->getID()][1]);
            dp[root->getID()][0] += dp[node->getID()][1];
        }
    }
}

template <typename Node>
class Kingdom
{
private:
    vector<Node *> nodes;

public:
    void addEdge(int a, int b)
    {
        nodes[a]->addChild(nodes[b]);
        nodes[b]->addChild(nodes[a]);
    }
    Node *getNode(int i)
    {
        return nodes[i];
    }
    vector<Node *> getNodes()
    {
        return nodes;
    }

    void addNode(Node *node)
    {
        nodes.push_back(node);
    }

    int minVertexCover()
    {
        int n = nodes.size();
        vector<bool> visited(n, false);
        vector<vector<int>> dp(n, vector<int>(2));

        dfs(nodes[0], visited, dp);
        int result = min(dp[0][0], dp[0][1]);
        return result;
    }
};

int main()
{
    int n;
    cin >> n;
    Kingdom<Sentinel> kingdom;
    vector<pair<int, int>> edges;
    vector<int> Num(3, 0);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
    }
    for (int i = 0; i < n; i++)
    {
        string name, type;
        cin >> name >> type;
        if (type == "SENAPATI")
        {
            Sentinel *node = new Senapati(i, name);
            kingdom.addNode(node);
            Num[0]++;
        }
        else if (type == "DANDANAYAKA")
        {
            Sentinel *node = new Dandanayaka(i, name);
            kingdom.addNode(node);
            Num[1]++;
        }
        else if (type == "CHATURANGINI")
        {
            Sentinel *node = new Chaturangini(i, name);
            kingdom.addNode(node);
            Num[2]++;
        }
    }

    for (auto &p : edges)
    {
        int u = p.first;
        int v = p.second;
        kingdom.addEdge(u, v);
    }
    vector<pair<string, int>> list;
    vector<Sentinel *> nodes(kingdom.getNodes());
    for (int i = 0; i < n; i++)
    {
        string rank = nodes[i]->getRank();
        int id = nodes[i]->getID();
        list.push_back({rank, id});
    }
    sort(list.begin(), list.end(), Comparator());
    int vertexCover = kingdom.minVertexCover();
    int queries;
    cin >> queries;
    while (queries--)
    {
        int q;
        cin >> q;
        if (q == 1)
        {
            cout << vertexCover << "\n";
        }
        else if (q == 2)
        {
            for (auto &p : list)
            {
                cout << p.second << " ";
            }
            cout << "\n";
        }
        else if (q == 3)
        {
            int id;
            cin >> id;
            cout << nodes[id]->countHigherRanked(Num) << "\n";
        }
    }

    for (int i = 0; i < n; i++)
    {
        delete kingdom.getNode(i);
    }
}