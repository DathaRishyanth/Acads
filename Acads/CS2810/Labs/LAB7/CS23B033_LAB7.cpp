#include <bits/stdc++.h>
using namespace std;

class Comparator  // Comparator class to sort in ascending or descending order
{
private:
    bool greater;

public:
    Comparator() {}
    Comparator(bool a) : greater{a} {}
    void setComparator(bool a) { greater = a; }
    bool operator()(int a, int b)
    {
        if (greater)
        {
            return a > b; // Sort in descending order
        }
        else
        {
            return a < b; // Sort in ascending order
        }
    }
};

class Point // Point class to store x, y coordinates and index of the point
{
public:
    int x, y, index;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x{a}, y{b} {}
    bool operator<(const Point &p) const
    {
        return x < p.x || (x == p.x && y < p.y);
    }
    bool operator==(const Point &p) const
    {
        return x == p.x && y == p.y;
    }
    bool operator!=(const Point &p) const
    {
        return x != p.x || y != p.y;
    }
};

class ChessBoard
{
private:
    vector<vector<long long>> board;
    int n;

public:
    ChessBoard() {}
    ChessBoard(int _n) : n{_n}
    {
        board.resize(n, vector<long long>(n));
    }

    void sortRows(Comparator &comparator)
    {
        for (auto &row : board)
        {
            mergeSort(row, 0, row.size() - 1, comparator);
        }
    }
    void mergeSort(vector<long long> &arr, int l, int r, Comparator &comparator)
    {
        if (l >= r)
            return;
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, comparator);  // Sort left half
        mergeSort(arr, m + 1, r, comparator); // Sort right half
        merge(arr, l, m, r, comparator); // Merge the two halves
    }
    void merge(vector<long long> &arr, int l, int m, int r, Comparator &comparator)
    {
        vector<long long> left(arr.begin() + l, arr.begin() + m + 1); 
        vector<long long> right(arr.begin() + m + 1, arr.begin() + r + 1);
        int i = 0, j = 0, k = l;
        while (i < left.size() && j < right.size())
        {
            if (comparator(left[i], right[j]))
            {
                arr[k++] = left[i++];
            }
            else
            {
                arr[k++] = right[j++];
            }
        }
        while (i < left.size())
            arr[k++] = left[i++];
        while (j < right.size())
            arr[k++] = right[j++];
    }

    long long mergeAndCount(vector<long long> &arr, int left, int mid, int right)
    {
        vector<long long> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;
        long long inv_count = 0;

        while (i <= mid && j <= right)
        {
            if (arr[i] <= arr[j])
            {
                temp[k++] = arr[i++];
            }
            else
            {
                temp[k++] = arr[j++];
                inv_count += (mid - i + 1);
            }
        }

        while (i <= mid)
            temp[k++] = arr[i++];
        while (j <= right)
            temp[k++] = arr[j++];

        for (int i = left; i <= right; i++)
        {
            arr[i] = temp[i - left];
        }

        return inv_count;
    }

    long long sortAndCount(vector<long long> &arr, int left, int right)
    {
        if (left >= right)
            return 0;

        int mid = left + (right - left) / 2;
        long long leftCount = sortAndCount(arr, left, mid); // Count inversions in left half
        long long rightCount = sortAndCount(arr, mid + 1, right); // Count inversions in right half
        long long mergeCount = mergeAndCount(arr, left, mid, right); // Count inversions in merge step

        return leftCount + rightCount + mergeCount;
    }

    long long countInversions()
    {
        vector<long long> flattened;
        flattened.reserve(board.size() * board[0].size()); // Pre-allocate memory
        for (const auto &row : board)
        {
            flattened.insert(flattened.end(), row.begin(), row.end());
        }
        return sortAndCount(flattened, 0, flattened.size() - 1);
    }

    friend istream &operator>>(istream &stream, ChessBoard &cb)
    { // For input of ChessBoard object
        stream >> cb.n;
        cb.board.resize(cb.n, vector<long long>(cb.n));
        for (int i = 0; i < cb.n; i++)
        {
            for (int j = 0; j < cb.n; j++)
            {
                stream >> cb.board[i][j];
            }
        }
        return stream;
    }

    friend ostream &operator<<(ostream &stream, ChessBoard &cb)
    {
        // For output of ChessBoard object
        for (int i = 0; i < cb.n; i++)
        {
            for (int j = 0; j < cb.n; j++)
            {
                stream << cb.board[i][j] << " ";
            }
            stream << endl;
        }
        return stream;
    }
};

long long squaredDistance(Point a, Point b)
{
    return (1LL * (a.x - b.x) * (a.x - b.x)) + (1LL * (a.y - b.y) * (a.y - b.y));
}

bool isBetterPair(const pair<Point, Point> &a, const pair<Point, Point> &b)
{
    long long d1 = squaredDistance(a.first, a.second);
    long long d2 = squaredDistance(b.first, b.second);

    if (d1 != d2) 
        return d1 < d2;
    if (a.first.x != b.first.x) // If distance is same, compare x and y coordinates
        return a.first.x < b.first.x;
    if (a.first.y != b.first.y) // If x coordinates are same, compare y coordinates
        return a.first.y < b.first.y;
    if (a.second.x != b.second.x) // If y coordinates are same, compare x coordinates of second point
        return a.second.x < b.second.x;
    if (a.second.y != b.second.y) // If x coordinates of second point are same, compare y coordinates of second point
        return a.second.y < b.second.y;
    return a.first.index < b.first.index; // If all coordinates are same, compare index of the points
}

vector<Point> getStrip(vector<Point> &SortedY, Point midPoint, long long d)
{
    // Returns points in the strip of width 2d centered at midPoint
    vector<Point> strip;
    for (Point p : SortedY)
    {
        if (abs(p.x - midPoint.x) < d)
        {
            strip.push_back(p);
        }
    }
    return strip;
}

pair<Point, Point> closestPairRecursion(vector<Point> &SortedX, vector<Point> &SortedY)
{
    int n = SortedX.size();
    if (n <= 3)
    {
        pair<Point, Point> best = {SortedX[0], SortedX[1]};
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                pair<Point, Point> candidate = {SortedX[i], SortedX[j]};
                if (isBetterPair(candidate, best))
                {
                    best = candidate;
                }
            }
        }
        return best;
    }

    int mid = n / 2;
    Point midPoint = SortedX[mid];

    vector<Point> leftX(SortedX.begin(), SortedX.begin() + mid);
    vector<Point> rightX(SortedX.begin() + mid, SortedX.end());

    vector<Point> leftY, rightY;
    for (Point p : SortedY)
    {
        if (p.x < midPoint.x || (p.x == midPoint.x && p.y < midPoint.y))
        {
            leftY.push_back(p);
        }
        else
        {
            rightY.push_back(p);
        }
    }

    pair<Point, Point> left = closestPairRecursion(leftX, leftY);
    pair<Point, Point> right = closestPairRecursion(rightX, rightY);

    pair<Point, Point> best = isBetterPair(left, right) ? left : right;
    long long d = squaredDistance(best.first, best.second);

    vector<Point> strip = getStrip(SortedY, midPoint, sqrt(d));
    pair<Point, Point> bestStrip = best;

    for (int i = 0; i < strip.size(); i++)
    {
        for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) * (strip[j].y - strip[i].y) < d; j++)
        {
            pair<Point, Point> candidate = {strip[i], strip[j]};
            if (isBetterPair(candidate, bestStrip))
            {
                bestStrip = candidate;
            }
        }
    }

    return isBetterPair(bestStrip, best) ? bestStrip : best;
}

pair<Point, Point> closestPair(vector<Point> &points)
{
    vector<Point> sortedX = points;
    vector<Point> sortedY = points;

    sort(sortedX.begin(), sortedX.end(), [](Point a, Point b)
         { return a.x < b.x || (a.x == b.x && a.y < b.y); });

    sort(sortedY.begin(), sortedY.end(), [](Point a, Point b)
         { return a.y < b.y || (a.y == b.y && a.x < b.x); });

    return closestPairRecursion(sortedX, sortedY);
}

int main()
{
    string cmd;
    ChessBoard cb;
    while (true)
    {
        cin >> cmd;
        if (cmd == "CREATE_2D")
        {
            cin >> cb;
        }
        else if (cmd == "SORT_2D")
        {
            string comparator;
            cin >> comparator;
            bool greater;
            if (comparator == "descending")
            {
                greater = true;
            }
            else
            {
                greater = false;
            }
            Comparator comp(greater);
            cb.sortRows(comp);
        }
        else if (cmd == "DISPLAY_2D")
        {
            cout << cb;
        }
        else if (cmd == "INVERSION_2D")
        {
            cout << cb.countInversions() << endl;
        }
        else if (cmd == "CLOSEST_2D")
        {
            int n;
            cin >> n;
            vector<Point> points;
            for (int i = 0; i < n; i++)
            {
                int x, y;
                cin >> x >> y;
                points.push_back(Point(x, y));
            }
            auto closest = closestPair(points);

            int pos1, pos2;
            for (int i = 0; i < n; i++)
            {
                if (points[i].x == closest.first.x && points[i].y == closest.first.y)
                {
                    pos1 = i;
                }
                if (points[i].x == closest.second.x && points[i].y == closest.second.y)
                {
                    pos2 = i;
                }
            }
            if (pos1 < pos2)
            {
                cout << closest.first.x << " " << closest.first.y << " " << closest.second.x << " " << closest.second.y << endl;
            }
            else
            {
                cout << closest.second.x << " " << closest.second.y << " " << closest.first.x << " " << closest.first.y << endl;
            }
        }
        else if (cmd == "END")
        {
            break;
        }
    }
}
