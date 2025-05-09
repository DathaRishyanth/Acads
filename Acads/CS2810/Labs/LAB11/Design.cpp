#include <bits/stdc++.h>
using namespace std;

template<typename T> 
class Edge;

// class for Nodes(Rooms)
template<typename T>
class Node{
    private:
        T roomID;
    public:
        Node(T &s) : roomID{s}{}
        T getRoomID() const { return roomID; } //returns roomID
        friend class Edge<T>;
        
};

//class for storing Edges 
template<typename T>
class Edge{
    private:
        Node<T> u,v;
        int w;
    public:
        Edge(string first,string second,int _w) : u{Node(first)},v{Node(second)},w{_w}{} //Constructor class for Edge class
        bool operator <(Edge a); //comparator for priority queue
};


template<typename T>
class PriorityQueue{
    private:
        vector<Node<T>*,int> elements;
    public:
        PriorityQueue(){} 
        const size_t size() const; //returns the size of the priority queue
        void push(const T& num); // pushes an element into the priority queue
        void pop(); // Pops the min element
        const T& top() const; // Returns the top element
        const bool empty() const; // Checks if the priority queue is empty
      

};

// Dijkstra's Algorithm
void dijkstra(map<string,vector<pair<string,int>>>& adjList, string& start,string& end);

