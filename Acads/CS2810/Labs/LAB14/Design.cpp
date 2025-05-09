#include <bits/stdc++.h>
using namespace std;

// Abstract class for Island
class Island {
    private:
    string ID;
    pair<int, int> centroid;
public:
    virtual void read(istream &stream) = 0;
    virtual ~Island();
    Island(){}
    Island(string _id) : ID(_id){}
    friend istream &operator>>(istream &stream, Island* &a) {
        a->read(stream);
        return stream;
    }
    //Setter
    void setCentroid(int x,int y){
        centroid.first = x;
        centroid.first = y;
    }

    //Getters
    pair<int,int> getCentroid(){
        return centroid;
    }
    string getId(){
        return ID;
    }
};

// Derived class for Rectangular Island
class Rectangle : public Island {
private:
    vector<pair<int, int>> coordinates;
public:
    Rectangle(string id) : Island(id){}
    void read(istream &stream) override {
        int sumX = 0, sumY = 0;
        for (int i = 0; i < 4; i++) {
            int x, y;
            stream >> x >> y;
            coordinates.emplace_back(x, y);
            sumX += x;
            sumY += y;
        }
        (this)->setCentroid(sumX/4,sumY/4);
    }
};

// Derived class for Triangular Island
class Triangle : public Island {
private:
    vector<pair<int, int>> coordinates;
public:
    Triangle(string id) : Island(id){}
    void read(istream &stream) override {
        int sumX = 0, sumY = 0;
        for (int i = 0; i < 3; i++) {
            int x, y;
            stream >> x >> y;
            coordinates.emplace_back(x, y);
            sumX += x;
            sumY += y;
        }
        this->setCentroid(sumX/3,sumY/3);
    }

};

// Derived class for Circular Island
class Circle : public Island {
private:
    pair<int, int> center;
    int radius;
public:
    Circle(string id) : Island(id){}
    void read(istream &stream) override {
        int x, y, r;
        stream >> x >> y >> r;
        center = {x, y};
        radius = r;
        this->setCentroid(x,y);
    }
};


class Archipelago{
    private:
        vector<Island*> islands;
    public:
    void addIsland(Island* island){
        islands.push_back(island);
    }
    void process(); // Outputs YES if there is such a path and prints the path, else prints NO and prints the
    // longest possible path


};
