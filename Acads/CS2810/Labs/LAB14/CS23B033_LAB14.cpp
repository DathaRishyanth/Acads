#include <bits/stdc++.h>
using namespace std;

// Abstract class for Island
class Island
{
private:
    string ID;
    pair<int, int> centroid;

public:
    virtual void read(istream &stream) = 0;
    Island() {}
    Island(string _id) : ID(_id) {}
    friend istream &operator>>(istream &stream, Island *&a)
    {
        a->read(stream);
        return stream;
    }
    // Setter
    void setCentroid(int x, int y)
    {
        centroid.first = x;
        centroid.second = y;
    }

    // Getters
    pair<int, int> getCentroid()
    {
        return centroid;
    }
    string getId()
    {
        return ID;
    }
};

// Derived class for Rectangular Island
class Rectangle : public Island
{
private:
    vector<pair<int, int>> coordinates;

public:
    Rectangle(string id) : Island(id) {}
    vector<pair<int, int>> getCoordinates() const {
        return coordinates;
    }    
    void read(istream &stream) override
    {
        int sumX = 0, sumY = 0;
        for (int i = 0; i < 4; i++)
        {
            int x, y;
            stream >> x >> y;
            coordinates.emplace_back(x, y);
            sumX += x;
            sumY += y;
        }
        (this)->setCentroid(sumX / 4, sumY / 4);
    }
};

// Derived class for Triangular Island
class Triangle : public Island
{
private:
    vector<pair<int, int>> coordinates;

public:
    Triangle(string id) : Island(id) {}
    vector<pair<int, int>> getCoordinates() const {
        return coordinates;
    }
    
    void read(istream &stream) override
    {
        
        int sumX = 0, sumY = 0;
        for (int i = 0; i < 3; i++)
        {
            int x, y;
            stream >> x >> y;
            coordinates.emplace_back(x, y);
            sumX += x;
            sumY += y;
        }
        this->setCentroid(sumX / 3, sumY / 3);
    }
};

// Derived class for Circular Island
class Circle : public Island
{
private:
    pair<int, int> center;
    int radius;

public:
    Circle(string id) : Island(id) {}
    void read(istream &stream) override
    {
        int x, y, r;
        stream >> x >> y >> r;
        center = {x, y};
        radius = r;
        this->setCentroid(x, y);
    }
    int getRadius() const {
        return radius;
    }
};

class Archipelago
{
private:
    vector<Island *> islands;

public:
    void addIsland(Island *island)
    {
        islands.push_back(island);
    }
    void process() // Outputs YES if there is such a path and prints the path, else prints NO and prints the longest possible path
    {
        int n = islands.size();

        vector<vector<bool>> adj(n, vector<bool>(n, false));

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                pair<int, int> ci = islands[i]->getCentroid();
                pair<int, int> cj = islands[j]->getCentroid();
        
                double dist = sqrt(pow(ci.first - cj.first, 2) + pow(ci.second - cj.second, 2));
        
                double reach_i = 0, reach_j = 0;
        
                
                if (auto circle = dynamic_cast<Circle*>(islands[i])) {
                    reach_i = circle->getRadius();
                } else if (auto rect = dynamic_cast<Rectangle*>(islands[i])) {
                    for (auto &v : rect->getCoordinates())
                    {
                        //dist from centroid to each vertex
                        double d = sqrt(pow(v.first - ci.first, 2) + pow(v.second - ci.second, 2));
                        reach_i = max(reach_i, d);
                    }
                } else if (auto tri = dynamic_cast<Triangle*>(islands[i])) {
                    for (auto &v : tri->getCoordinates())
                    {
                        //dist from centroid to each vertex
                        double d = sqrt(pow(v.first - ci.first, 2) + pow(v.second - ci.second, 2));
                        reach_i = max(reach_i, d);
                    }
                }
        
               
                if (auto circle = dynamic_cast<Circle*>(islands[j])) {
                    reach_j = circle->getRadius();
                } else if (auto rect = dynamic_cast<Rectangle*>(islands[j])) {
                    for (auto &v : rect->getCoordinates())
                    {
                        //dist from centroid to each vertex
                        double d = sqrt(pow(v.first - cj.first, 2) + pow(v.second - cj.second, 2));
                        reach_j = max(reach_j, d);
                    }
                } else if (auto tri = dynamic_cast<Triangle*>(islands[j])) {
                    for (auto &v : tri->getCoordinates())
                    {
                        //dist from centroid to each vertex
                        double d = sqrt(pow(v.first - cj.first, 2) + pow(v.second - cj.second, 2));
                        reach_j = max(reach_j, d);
                    }
                }
        
                if (dist <= reach_i + reach_j)
                    adj[i][j] = adj[j][i] = true;
            }
        }
        
        

       
        int n_mask = (1 << n);
        vector<vector<int>> dp(n_mask, vector<int>(n, -1));   // dp[mask][i] = max path length ending at node i with visited mask
        vector<vector<int>> next(n_mask, vector<int>(n, -1)); // For reconstructing the path

        // Initialize: single nodes
        for (int i = 0; i < n; i++)
        {
            dp[1 << i][i] = 1;
        }

        int max_length = 1;
        int max_mask = 0;
        int max_last = 0;

        // Filling the DP table
        for (int mask = 1; mask < n_mask; mask++)
        {
            for (int i = 0; i < n; i++)
            {
                if (!(mask & (1 << i)))
                    continue; // i is not in the mask

                int prev_mask = mask & ~(1 << i); // mask without i
                if (prev_mask == 0)
                    continue; // i is the only set bit

                for (int j = 0; j < n; j++)
                {
                    if (!(prev_mask & (1 << j)))
                        continue; // j is not in prev_mask
                    if (!adj[i][j])
                        continue; // i and j are not adjacent

                    if (dp[prev_mask][j] != -1 && dp[prev_mask][j] + 1 > dp[mask][i])
                    {
                        dp[mask][i] = dp[prev_mask][j] + 1;
                        next[mask][i] = j;

                        if (dp[mask][i] > max_length)
                        {
                            max_length = dp[mask][i];
                            max_mask = mask;
                            max_last = i;
                        }
                    }
                }
            }
        }

        // Check if a Hamiltonian path exists 
        bool found = false;
        int final_mask = n_mask - 1;
        int last_node = -1;

        for (int i = 0; i < n; i++)
        {
            if (dp[final_mask][i] == n)
            {
                found = true;
                last_node = i;
                break;
            }
        }

        if (found)
        {
            // Hamiltonian path exists
            cout << "YES" << endl;

        
            vector<int> path;
            int current_mask = final_mask;
            int current_node = last_node;

            while (current_node != -1)
            {
                path.push_back(current_node);
                int next_node = next[current_mask][current_node];
                current_mask &= ~(1 << current_node);
                current_node = next_node;
            }

            // Print the path
            for (int i = path.size() - 1; i >= 0; i--)
            {
                cout << islands[path[i]]->getId() << " ";
            }
            cout << endl;
        }
        else
        {
            // No Hamiltonian path
            cout << "NO" << endl;
            cout << max_length << endl;

            // Reconstruct the longest path
            vector<int> path;
            int current_mask = max_mask;
            int current_node = max_last;

            while (current_node != -1)
            {
                path.push_back(current_node);
                int next_node = next[current_mask][current_node];
                current_mask &= ~(1 << current_node);
                current_node = next_node;
            }

            // Print the longest path
            for (int i = path.size() - 1; i >= 0; i--)
            {
                cout << islands[path[i]]->getId() << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    int n;
    cin >> n;
    Archipelago archipelago;
    for (int i = 0; i < n; i++)
    {
        string type, id;
        cin >> type >> id;
        Island *island = nullptr;
        if (type == "RECTANGLE")
        {
            island = new Rectangle(id);
        }
        else if (type == "TRIANGLE")
        {
            island = new Triangle(id);
        }
        else if (type == "CIRCLE")
        {
            island = new Circle(id);
        }
        if (island)
        {
            cin >> island;
            archipelago.addIsland(island);
        }
    }
    archipelago.process();
}
