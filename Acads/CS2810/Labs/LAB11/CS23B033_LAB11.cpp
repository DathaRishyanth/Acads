#include <bits/stdc++.h>
using namespace std;

// Generic Min-Priority Queue Implementation
template <typename T, typename Compare = less<T>>
class MinPriorityQueue
{
private:
    vector<T> heap;
    Compare comp;

    void percolateUp(size_t idx)
    {
        while (idx > 0)
        {
            size_t parent = (idx - 1) / 2;
            if (comp(heap[idx], heap[parent]))
            {
                swap(heap[idx], heap[parent]);
                idx = parent;
            }
            else
                break;
        }
    }

    void percolateDown(size_t idx)
    {
        size_t size = heap.size();
        while (2 * idx + 1 < size)
        {
            size_t left = 2 * idx + 1, right = 2 * idx + 2, smallest = idx;
            if (left < size && comp(heap[left], heap[smallest]))
                smallest = left;
            if (right < size && comp(heap[right], heap[smallest]))
                smallest = right;
            if (smallest != idx)
            {
                swap(heap[idx], heap[smallest]);
                idx = smallest;
            }
            else
                break;
        }
    }

public:
    MinPriorityQueue() {}

    size_t size() const
    {
        return heap.size();
    }

    void push(const T &val)
    {
        heap.push_back(val);
        percolateUp(heap.size() - 1);
    }

    void pop()
    {
        if (!heap.empty())
        {
            heap[0] = heap.back();
            heap.pop_back();
            if (!heap.empty())
                percolateDown(0);
        }
    }

    const T &top() const
    {
        return heap.front();
    }

    bool empty() const
    {
        return heap.empty();
    }
};

// Node class representing rooms in the graph
class Node
{
private:
    string roomName;
    int distance;
    int parity; // 0 for even, 1 for odd

public:
    Node(string name, int dist, int parity_) : roomName(name), distance(dist),parity(parity_) {}

    string getRoomName() const { return roomName; }
    int getDistance() const { return distance; }
    int getParity() const { return parity; }

    bool operator<(const Node &other) const
    {
        return distance > other.distance; 
    }
    bool operator>(const Node &other) const
    {
        return distance < other.distance; 
    }
    bool operator==(const Node &other) const
    {
        return roomName == other.roomName;
    }
};

void dijkstra(map<string, vector<pair<string, int>>> &adjList, Node &start, Node &end)
{
    map<string, vector<int>> dist;              
    MinPriorityQueue<Node,greater<Node>> pq; 

    for (auto &pair : adjList)
    {
        dist[pair.first] = {INT_MAX, INT_MAX};
    }

    dist[start.getRoomName()] = {0, INT_MAX};
    pq.push(Node(start.getRoomName(), 0, 0)); // Start with even parity

    while (!pq.empty())
    {
        Node u = pq.top();
        pq.pop();

        if (u == end && u.getParity() == 0) //Found the end node with even number of edges.
        {
            cout << u.getDistance() << endl;
            return;
        }

        for (auto &neighbor : adjList[u.getRoomName()])
        {
            Node v = Node(neighbor.first, 0, 0); 
            int weight = neighbor.second;
            int new_parity = (u.getParity() + 1) % 2; //change parity

            if (dist[v.getRoomName()][new_parity] > dist[u.getRoomName()][u.getParity()] + weight) 
            {
                dist[v.getRoomName()][new_parity] = dist[u.getRoomName()][u.getParity()] + weight;
                v = Node(v.getRoomName(), dist[v.getRoomName()][new_parity], new_parity);
                pq.push(v); 
            }
        }
    }
    cout << -1 << endl; // even length path does not exist
}

int main()
{
    int n, m;
    cin >> n >> m;
    map<string, vector<pair<string, int>>> adjList;
    vector<string> rooms(n);
    for (int i = 0; i < n; i++)
    {
        cin >> rooms[i];
    }
    for (int i = 0; i < m; i++)
    {
        string u, v;
        int w;
        cin >> u >> v >> w;
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});
    }

    string start, end;
    cin >> start >> end;
    Node startNode(start, 0, 0); // Start with even parity
    Node endNode(end, 0, 0);     // End with even parity
    dijkstra(adjList, startNode, endNode); // Call Dijkstra's algorithm
}