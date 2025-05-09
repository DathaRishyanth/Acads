#include <bits/stdc++.h>
using namespace std;

class Card
{
public:
    virtual int getArea() = 0; // Pure virtual function to get area

    bool compareCardPointers(Card *a, Card *b) // Comparision function for 2 cards
    {
        return a->getArea() < b->getArea();
    }

    bool operator<(Card *other) // overloading < operator
    {
        return compareCardPointers(this, other);
    }

    virtual void read(istream &stream) = 0;  // Pure virtual function to read card data
    virtual void print(ostream &stream) = 0; // Pure virtual function to print card data

    friend istream &operator>>(istream &stream, Card *a)
    {
        a->read(stream);
        return stream;
    }

    friend ostream &operator<<(ostream &stream, Card *a)
    {
        a->print(stream);
        return stream;
    }
};

// Derived classes for square
class Square : public Card
{
private:
    int edge, area;

public:
    Square() : edge(0), area(0) {}
    Square(int e) : edge(e), area(e * e) {}

    void read(istream &stream)
    {
        stream >> edge;
        area = edge * edge;
    }

    void print(ostream &stream)
    {
        stream << "SQUARE " << edge << "\n";
    }

    int getArea()
    {
        return area;
    }
};

// Derived classes for rectangle
class Rectangle : public Card
{
private:
    int length, breadth, area;

public:
    Rectangle() : length(0), breadth(0), area(0) {}
    Rectangle(int l, int b) : length(l), breadth(b), area(l * b) {}

    void read(istream &stream)
    {
        stream >> length >> breadth;
        area = length * breadth;
    }

    void print(ostream &stream)
    {
        stream << "RECTANGLE " << length << " " << breadth << "\n";
    }

    int getArea()
    {
        return area;
    }
};

// Derived classes for triangle
class Triangle : public Card
{
private:
    int base, height, area;

public:
    Triangle() : base(0), height(0), area(0) {}
    Triangle(int b, int h) : base(b), height(h), area((b * h) / 2) {}

    void read(istream &stream)
    {
        stream >> base >> height;
        area = (base * height) / 2;
    }

    void print(ostream &stream)
    {
        stream << "TRIANGLE " << base << " " << height << "\n";
    }

    int getArea()
    {
        return area;
    }
};

class CardOrganizer
{
private:
    vector<Card *> cards; // Vector to store cards
    vector<int> piles;    // Vector to store piles
    vector<int> tailIndex;
    vector<int> prev;
    vector<Card *> lis; // Vector to store longest increasing subsequence

public:
    CardOrganizer() {}

    void addCard(Card *a)
    {
        cards.push_back(a);

        int area = a->getArea();
        auto it = lower_bound(piles.begin(), piles.end(), area);
        if (it == piles.end()) // If no pile with less area found
        {
            piles.push_back(area);
        }
        else
        {
            *it = area;
        }

        int n = cards.size();
        if (prev.size() < n)
            prev.resize(n, -1);

        auto lisIt = lower_bound(tailIndex.begin(), tailIndex.end(), area,
                                 [&](int idx, int val)
                                 { return cards[idx]->getArea() < val; });

        int pos = lisIt - tailIndex.begin();

        if (lisIt == tailIndex.end())
            tailIndex.push_back(n - 1);
        else
            *lisIt = n - 1;

        if (pos > 0)
            prev[n - 1] = tailIndex[pos - 1];

        lis.clear();
        if (!tailIndex.empty())
        {
            int idx = tailIndex.back();
            while (idx != -1)
            {
                lis.push_back(cards[idx]);
                idx = prev[idx];
            }
            reverse(lis.begin(), lis.end());
        }
    }

    size_t getPileCount() const // Returns the number of piles
    {
        return piles.size();
    }

    const vector<Card *> &getLis() const // Returns the longest increasing subsequence
    {
        return lis;
    }

    ~CardOrganizer()
    {
        for (Card *c : cards)
            delete c;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    CardOrganizer Organizer;
    int q;
    cin >> q;

    while (q--)
    {
        int cmd;
        cin >> cmd;

        if (cmd == 1)
        {
            string shape;
            cin >> shape;

            Card *card = nullptr;

            if (shape == "SQUARE")
            {
                card = new Square();
            }
            else if (shape == "RECTANGLE")
            {
                card = new Rectangle();
            }
            else if (shape == "TRIANGLE")
            {
                card = new Triangle();
            }

            if (card)
            {
                cin >> card;
                Organizer.addCard(card);
            }
        }
        else if (cmd == 2)
        {
            int pileCount = Organizer.getPileCount();
            cout << pileCount << '\n';
        }
        else if (cmd == 3)
        {
            const vector<Card *> &lis = Organizer.getLis();
            cout << lis.size() << '\n';
            for (Card *card : lis)
            {
                cout << card;
            }
        }
    }

    return 0;
}