//Mohammad Jaafar
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct point
{
    int x, y;

    bool operator<(const point& second) const
    {
        if (x != second.x)
        {
            return x < second.x;
        }
        return y < second.y;
    }
    bool operator>(const point& second) const
    {
        if (x != second.x)
        {
            return x > second.x;
        }
        return y > second.y;
    }
};

struct segment
{
    point p1, p2;


    bool operator<(const segment& second) const
    {
        if (p1.x != second.p1.x)
        {
            return p1.x < second.p1.x;
        }
        return p1.y < second.p1.y;
    }
    bool operator>(const segment& second) const
    {
        if (p1.x != second.p1.x)
        {
            return p1.x > second.p1.x;
        }
        return p1.y > second.p1.y;
    }
};


bool compare_segments(segment s1, segment s2)
{
    if (s1.p1.x != s2.p1.x) return s1.p1.x < s2.p1.x;
    return s1.p1.y < s2.p1.y;
}

// Returns true if the line segments intersect, false otherwise
bool intersect(segment s1, segment s2)
{
    long long x1 = s1.p1.x, y1 = s1.p1.y, x2 = s1.p2.x, y2 = s1.p2.y;
    long long x3 = s2.p1.x, y3 = s2.p1.y, x4 = s2.p2.x, y4 = s2.p2.y;

    long long dx1 = x2 - x1, dy1 = y2 - y1, dx2 = x4 - x3, dy2 = y4 - y3;
    long long dx3 = x1 - x3, dy3 = y1 - y3;

    long long div = dy2 * dx1 - dx2 * dy1;
    if (div == 0) return false; // Parallel lines

    double s = (dx2 * dy3 - dy2 * dx3) / (double)div;
    double t = (dx1 * dy3 - dy1 * dx3) / (double)div;

    if (s < 0 || s > 1 || t < 0 || t > 1) return false; // Intersection point outside of both segments

    return true;
}

template<typename T>
void quickSort(vector<T>& arr, int low, int high, bool (*compare)(T, T))
{
    if (low < high)
    {
        int pivot = partition(arr, low, high, compare);

        quickSort(arr, low, pivot - 1, compare);
        quickSort(arr, pivot + 1, high, compare);
    }
}

template<typename T>
int partition(vector<T>& arr, int low, int high, bool (*compare)(T, T))
{
    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (compare(arr[j], pivot))
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

/*Time complexity(Quick Sort): O(n log n) on average, O(n^2) worst-case when the pivot selection is bad.
In-place: Yes
Stability: Not guaranteed, but can be made stable by choosing the pivot carefully (e.g., always selecting the first or last element).
*/

struct Node
{
    segment s;
    int height;
    Node* left;
    Node* right;

    Node(segment s) : s(s), height(1), left(nullptr), right(nullptr) {}
};

// AVL tree
class AVLTree
{
public:
    AVLTree() : root(nullptr) {}

    void insert(segment s)
    {
        root = insertNode(root, s);
    }

    void remove(segment s)
    {
        root = removeNode(root, s);
    }

    bool intersectsWith(segment s) const
    {
        return intersectsWith(root, s);
    }
    bool empty() const
    {
        return !root;
    }

    Node* mint() const
    {
        if (!root)
        {
            return nullptr;
        }
        Node* node = root;
        while (node->left)
        {
            node = node->left;
        }
        return node;
    }
    bool doIntersect(segment s1, segment s2) const
    {
        int m1 = orientation(s1.p1, s1.p2, s2.p1);
        int m2 = orientation(s1.p1, s1.p2, s2.p2);
        int m3 = orientation(s2.p1, s2.p2, s1.p1);
        int m4 = orientation(s2.p1, s2.p2, s1.p2);
        if (m1 != m2 && m3 != m4)
        {
            return true;
        }
        if (m1 == 0 && onSegment(s1.p1, s1.p2, s2.p1))
        {
            return true;
        }
        if (m2 == 0 && onSegment(s1.p1, s1.p2, s2.p2))
        {
            return true;
        }
        if (m3 == 0 && onSegment(s2.p1, s2.p2, s1.p1))
        {
            return true;
        }
        if (m4 == 0 && onSegment(s2.p1, s2.p2, s1.p2))
        {
            return true;
        }
        return false;
    }

private:
    Node* root;

    int height(Node* node) const
    {
        return node ? node->height : 0;
    }

    int balanceFactor(Node* node) const
    {
        return height(node->right) - height(node->left);
    }

    void updateHeight(Node* node)
    {
        node->height = max(height(node->left), height(node->right)) + 1;
    }

    Node* rotateRight(Node* node)
    {
        Node* left = node->left;
        node->left = left->right;
        left->right = node;
        updateHeight(node);
        updateHeight(left);
        return left;
    }

    Node* rotateLeft(Node* node)
    {
        Node* right = node->right;
        node->right = right->left;
        right->left = node;
        updateHeight(node);
        updateHeight(right);
        return right;
    }

    Node* balance(Node* node)
    {
        updateHeight (node);
        int bf = balanceFactor(node);
        if (bf == 2)
        {
            if (balanceFactor(node->right) < 0)
            {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        else if (bf == -2)
        {
            if (balanceFactor(node->left) > 0)
            {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        return node;
    }

    Node* insertNode(Node* node, segment s)
    {
        if (!node)
        {
            return new Node(s);
        }
        if (s < node->s)
        {
            node->left = insertNode(node->left, s);
        }
        else
        {
            node->right = insertNode(node->right, s);
        }
        return balance(node);
    }
    Node* removeNode(Node* node, segment s)
    {
        if (!node)
        {
            return nullptr;
        }
        if (s < node->s)
        {
            node->left = removeNode(node->left, s);
        }
        else if (node->s < s)
        {
            node->right = removeNode(node->right, s);
        }
        else
        {
            if (!node->left || !node->right)
            {
                Node* temp = node->left ? node->left : node->right;
                if (!temp)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                {
                    *node = *temp;
                }
                delete temp;
            }
            else
            {
                Node* temp = node->right;
                while (temp->left)
                {
                    temp = temp->left;
                }
                node->s = temp->s;
                node->right = removeNode(node->right, temp->s);
            }
        }
        if (!node)
        {
            return node;
        }
        return balance(node);
    }

    bool intersectsWith(Node* node, segment s) const
    {
        while (node)
        {
            if (doIntersect(node->s, s))
            {
                return true;
            }
            if (node->left && node->left->height >= node->right->height)
            {
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }
        return false;
    }
    int orientation(point p1, point p2, point r) const
    {
        long val = (p2.y - p1.y) * (r.x - p2.x) - (p2.x - p1.x) * (r.y - p2.y);
        if (val == 0)
        {
            return 0;
        }
        return (val > 0) ? 1 : 2;
    }

    bool onSegment(point p1, point p2, point r) const
    {
        if (r.x >= min(p1.x, p2.x) && r.x <= max(p1.x, p2.x)
                && r.y >= min(p1.y, p2.y) && r.y <= max(p1.y, p2.y))
        {
            return true;
        }
        return false;
    }
};



int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n;
    cin >> n;

    vector<segment> segments(n);
    for (long long i = 0; i < n; i++)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        segments[i] = { {x1, y1}, {x2, y2} };
    }

    quickSort(segments, 0, n - 1, compare_segments);

    AVLTree TheTree;

    vector<segment> active_segments;
    for (long long i = 0; i < n; i++)
    {
        segment curr_seg = segments[i];
        long long curr_x = curr_seg.p1.x;
        TheTree.insert(curr_seg);
        for (auto active_seg : active_segments)
        {
            if (intersect(curr_seg, active_seg))
            {
                cout << "INTERSECTION" << endl;
                cout << curr_seg.p1.x << " " << curr_seg.p1.y << " "
                     << curr_seg.p2.x << " " << curr_seg.p2.y << endl;
                cout << active_seg.p1.x << " " << active_seg.p1.y << " "
                     << active_seg.p2.x << " " << active_seg.p2.y << endl;
                return 0;
            }
        }

        for (auto it = active_segments.begin(); it != active_segments.end();)
        {
            if (it->p2.x < curr_x)
            {
                TheTree.remove(curr_seg);
                it = active_segments.erase(it);
            }
            else
            {
                it++;
            }
        }
        active_segments.push_back(curr_seg);
    }

    cout << "NO INTERSECTIONS" << endl;
    return 0;

}
/*The AVL tree is a self-balancing binary search tree that maintains a balanced tree height through the use of rotation operations.

 The height of the left and right sub-trees of any node in an AVL tree differ by at most 1.

 This guarantees that the time complexity of the basic operations (insertion, removal, and searching) is O(log n).

 The worst-case time complexity of the quicksort algorithm used to sort the line segments is O(n^2),

 which occurs when the pivot selection is bad. However, the average-case time complexity is O(n log n),

 which is significantly faster. The quicksort algorithm is performed in-place, meaning that the memory requirements for sorting are minimal.

 Stability is not guaranteed, but can be made stable by choosing the pivot carefully (e.g., always selecting the first or last element).

 The line segments are stored in an AVL tree, where each node represents a segment. The AVL tree is balanced,

 ensuring that all operations have a time complexity of O(log n).

 The insertion and removal operations maintain the balance of the tree by performing rotation operations as needed.

 The "intersect" function checks if two line segments intersect using the cross product of the vectors formed by the line segments.

 If the cross product is 0, then the line segments are parallel. If the intersection point is outside of both line segments,

 then there is no intersection.

 The "doIntersect" function uses the "orientation" function to determine the orientation of three points.

 If the orientations of the points formed by two line segments are different, then the line segments intersect.

 -----------------------------
    The line segments intersection problem addressed in this code has many practical applications in various fields,

    such as computer graphics, computational geometry, and robotics. For example,

    it is used in computer graphics to determine whether two lines (e.g., edges of polygons) intersect, which is necessary for several operations like clipping, filling, and texturing. In computational geometry,

    it plays a significant role in various algorithms such as line sweep, point location, and Voronoi diagrams. In robotics,

    determining if two lines intersect is crucial for robot motion planning, collision avoidance, and robot vision applications.

    Therefore, having an efficient algorithm for line segments intersection is essential in many fields,

     making this problem of significant importance.

     */