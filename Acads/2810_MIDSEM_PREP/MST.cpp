#include <bits/stdc++.h>
using namespace std;


vector<vector<int>> MST(int n, vector<vector<int>>& edges) {
    vector<vector<pair<int, int>>> graph(n);
    for (const auto& edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    vector<bool> inMST(n, false);
    vector<int> minEdge(n, INT_MAX);
    vector<int> parent(n, -1);
    minEdge[0] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0}); // {weight, node}

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;

        for (const auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (!inMST[v] && weight < minEdge[v]) {
                minEdge[v] = weight;
                parent[v] = u;
                pq.push({weight, v});
            }
        }
    }

    vector<vector<int>> mstEdges;
    for (int i = 1; i < n; i++) {
        if (parent[i] != -1) {
            mstEdges.push_back({parent[i], i, minEdge[i]});
        }
    }

    return mstEdges;
}

// Find MST using Kruskal's algorithm

vector<vector<int>> kruskalMST(int n, vector<vector<int>>& edges) {
    sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[2] < b[2]; // Sort by weight
    });

    vector<int> parent(n), rank(n, 0);
    iota(parent.begin(), parent.end(), 0); // Initialize parent

    function<int(int)> find = [&](int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]); // Path compression
        }
        return parent[u];
    };

    auto unionSets = [&](int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    };

    vector<vector<int>> mstEdges;
    for (const auto& edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];
        if (find(u) != find(v)) {
            unionSets(u, v);
            mstEdges.push_back({u, v, w});
        }
    }

    return mstEdges;
}