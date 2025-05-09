#include <bits/stdc++.h>
using namespace std;

class Node{ //class for storing a node along with Hypescore
    private:
        int hypeScore;
    public:
        Node(){}
        Node(int x) : hypeScore{x}{}

};

class GraphAlgorithm{
    public:
        vector<vector<Node*>> adjList; //for storing the Graph
        GraphAlgorithm(){}
        GraphAlgorithm(int N){
            adjList.resize(N);
        }
        virtual void Query(); // virtual function
        friend istream &operator >>(istream &stream,GraphAlgorithm &G); //For inputting the graph

};

class IsCycle : public GraphAlgorithm{
    public:
        bool Cycle; //will set to True if the graph has a cyle
        IsCycle(bool a = false): Cycle{a}{} 
        void Query(); //checks if the graph has cycle 

};

class IndepComponent : public GraphAlgorithm{
    public:
        int numComponents; // Stores the number of components
        int maxCardinality; //stores the maxCardinality
        IndepComponent(int x,int y) : numComponents{x},maxCardinality{y}{}
       void Query(); //returns the number of components and maximum cardinality of the components


};

class ValidOrder : public GraphAlgorithm{
    public:
        vector<int> Order; //Stores the topo sort
        ValidOrder(){}
        void Query(); //Outputs the topo sort if there exists a topo sort else outputs NO

};

class MaxHype: public GraphAlgorithm{
    public:
        
        int maxHype; //Stores the maxHype points
        MaxHype(int X) : maxHype(X){}
        void Query(); // Computes the max Hype points that can be obtained
};


class Comparator{
    public:
        bool operator()(Node &a,Node &b); // Compares 2 nodes for checking if a appears before b 

};

