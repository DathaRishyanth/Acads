#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX

// Implementation of the Bellman-Ford algorithm
// to find the shortest path from a single source vertex
// to all other vertices in a weighted graph.
// The graph can contain negative weight edges but no negative weight cycles.
// The algorithm works by relaxing all edges repeatedly
// and updating the distance to each vertex until no further updates are possible.
// The time complexity of the Bellman-Ford algorithm is O(V * E),
// where V is the number of vertices and E is the number of edges in the graph.

vector<int> bellmanFord(int V, vector<vector<int>>& edges, int S) {
    // Initialize distances from source to all vertices as infinite
    vector<int> dist(V, INF);
    dist[S] = 0; // Distance from source to itself is always 0

    // Relax all edges |V| - 1 times
    for (int i = 1; i <= V - 1; i++) {
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Check for negative weight cycles
    for (const auto& edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            cout << "Graph contains negative weight cycle" << endl;
            return {}; // Return empty vector if negative cycle is detected
        }
    }

    return dist; // Return the shortest distances from source to all vertices
}

vector<int> FloyydWarshall(int V, vector<vector<int>>& edges) {
    // Initialize distance matrix with INF
    vector<vector<int>> dist(V, vector<int>(V, INF));
    
    // Set distance from each vertex to itself as 0
    for (int i = 0; i < V; i++) {
        dist[i][i] = 0;
    }

    // Set distances for direct edges
    for (const auto& edge : edges) {
        int u = edge[0], v = edge[1], w = edge[2];
        dist[u][v] = min(dist[u][v], w); // Handle multiple edges between same vertices
    }

    // Floyd-Warshall algorithm to find shortest paths between all pairs of vertices
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Convert the distance matrix to a single vector of shortest distances
    vector<int> result(V * V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            result[i * V + j] = dist[i][j];
        }
    }

    return result;
}