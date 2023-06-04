// Mohammad Jaafar
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Hash table implementation using separate chaining
class Map
{
public:
    virtual void put(int key, int value) = 0;
    virtual int get(int key) = 0;
    virtual bool contains(int key) = 0;
    virtual void remove(int key) = 0;
};

class HashMap : public Map
{
    struct Node
    {
        int key;
        int value;
        Node *next;

        Node(int k, int v) : key(k), value(v), next(nullptr) {}
    };

    vector<Node *> table;
    int capacity;

public:
    HashMap(int c) : capacity(c)
    {
        table.resize(capacity, nullptr);
    }

    void put(int key, int value) override
    {
        int index = hash<int>()(key);

        Node *current = table[index];
        Node *prev = nullptr;

        while (current)
        {
            if (current->key == key)
            {
                current->value = value;
                return;
            }
            prev = current;
            current = current->next;
        }

        Node *newNode = new Node(key, value);
        if (!prev)
        {
            table[index] = newNode;
        }
        else
        {
            prev->next = newNode;
        }
    }

    int get(int key) override
    {
        int index = hash<int>()(key);

        Node *current = table[index];

        while (current)
        {
            if (current->key == key)
            {
                return current->value;
            }
            current = current->next;
        }

        return -1;
    }

    bool contains(int key) override
    {
        int index = hash<int>()(key);

        Node *current = table[index];

        while (current)
        {
            if (current->key == key)
            {
                return true;
            }
            current = current->next;
        }

        return false;
    }

    void remove(int key) override
    {
        int index = hash<int>()(key);

        Node *current = table[index];
        Node *prev = nullptr;

        while (current)
        {
            if (current->key == key)
            {
                if (!prev)
                {
                    table[index] = current->next;
                }
                else
                {
                    prev->next = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }
};

// Custom hash function
struct CustomHash
{
    size_t operator()(const pair<int, int> &p) const
    {
        return hash<int>()(p.first) ^ hash<int>()(p.second);
    }
};

// Set implementation using a hash table
class Set
{
public:
    virtual void add(int value) = 0;
    virtual void remove(int value) = 0;
    virtual bool contains(int value) = 0;
};

class HashSet : public Set
{
    HashMap table;
    int size;

public:
    HashSet(int capacity) : table(capacity), size(0) {}
    void add(int value) override
    {
        if (!table.contains(value))
        {
            table.put(value, 1);
            size++;
        }
    }

    void remove(int value) override
    {
        if (table.contains(value))
        {
            table.remove(value);
            size--;
        }
    }

    bool contains(int value) override
    {
        return table.contains(value);
    }

    int getSize()
    {
        return size;
    }
};

int main()
{
    int n, W;
    cin >> n >> W;
    vector<int> w(n);
    vector<int> c(n);
    for (int i = 0; i < n; i++)
    {
        cin >> w[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> c[i];
    }

    // Initialize dp array
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Fill in dp array using recurrence relation
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= W; j++)
        {
            if (j >= w[i - 1])
            {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i - 1]] + c[i - 1]);
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // Backtrack to find set of items that give maximum cost
    HashSet indices(n + 1);
    int i = n;
    int j = W;
    while (i > 0 && j > 0)
    {
        if (dp[i][j] != dp[i - 1][j])
        {
            indices.add(i);
            j -= w[i - 1];
        }
        i--;
    }

    // Output results
    cout << indices.getSize() << endl;
    for (int i = 1; i <= n; i++)
    {
        if (indices.contains(i))
        {
            cout << i << " ";
        }
    }
    cout << endl;

    return 0;
}
