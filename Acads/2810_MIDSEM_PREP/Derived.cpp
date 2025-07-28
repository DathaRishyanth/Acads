#include <bits/stdc++.h>
using namespace std;

class Shape {
public:
    Shape() {
        cout << "Shape created\n";
    }
    virtual int area() { return 0; }
    virtual ~Shape() {
        cout << "Destroyed Shape\n";
    }

protected:
    bool shapeCreated;
};

class Quad : public Shape {  // Virtual inheritance to prevent duplicate Shape copies
private:
    int a, b, c, d;
public:
    Quad(int a1, int a2, int a3, int a4) : a{a1}, b{a2}, c{a3}, d{a4} {}
    Quad() {
        cout << "Quad created\n";
    }
    virtual ~Quad() {
        cout << "Quad Destroyed\n";
    }
};

class Rectangle : public Quad {  // Inheriting only from Quad (Quad already gets Shape)
private:
    int a, b;
public:
    Rectangle(int a1, int b1) : Quad(), a{a1}, b{b1} {}  // Ensure Quad is initialized
    int area(){
        cout << "Area of rectangle\n";
        return a * b;
    }
    void setCreated() {
        shapeCreated = true;
    }
    ~Rectangle(){
        cout << "Destroyed Rect\n";
    }
};

class Square : public Quad {
public:
    int a;
    Square(int n) : Quad(), a{n} {}  // Ensure Quad is initialized
    int area() override {
        cout << "Area of square\n";
        return a * a;
    }
    ~Square() override {
        cout << "Destroyed Square\n";
    }
};

int main() {
    Shape* rect = new Rectangle(3, 4);
    Shape* sq = new Square(5);

    cout << rect->area() << "\n";
    cout << sq->area() << "\n";

    delete rect;
    delete sq;

    return 0;
}
