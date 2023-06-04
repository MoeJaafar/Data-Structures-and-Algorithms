// Mohammad Jaafar
#include <string>
#include <iostream>
#include <vector>

using namespace std;

// The node class represents a single key-value pair in the map
template <typename K, typename V>
class Node
{
public:
    K key;
    V value;
    Node<K, V> *next;

    Node(K key, V value)
    {
        this->key = key;
        this->value = value;
        this->next = nullptr;
    }
};

// The hashing function hashes a key of any type to a size_t value ; O(1), constant time
template <typename K>
size_t hashing(const K &key)
{
    std::hash<K> hasher;
    return hasher(key);
}

// The Entry struct represents a single entry in the input data
struct Entry
{
    string date;
    string receipt;
    double cost;
};

// The unordered_mapp class implements a hash table using separate chaining
template <typename K, typename V>
class unordered_mapp
{
public:
    std::vector<Node<K, V> *> table; // The hash table
    size_t size;                     // The number of elements in the hash table
    int realSize = 0;                // The number of unique keys in the hash table

    // Default constructor
    unordered_mapp(int sz)
    {
        // Initialize the hash table with an initial capacity of sz
        table.resize(sz);
        size = 0;
    }

    // Insert a key-value pair into the map ;  worst case O(n), average case O(1) and amortized O(1), where n is the number of elements in the hash table
    void insert(K key, V value)
    {
        // Resize the hash table if it's more than 75% full
        if (size >= table.size() * 0.75)
        {
            resize();
        }
        realSize++;
        // Compute the hash value for the key
        int index = hashing<K>(key) % table.size();

        // Check if the key already exists in the map
        Node<K, V> *curr = table[index];
        while (curr)
        {
            if (curr->key == key)
            {
                // Key already exists, update the value
                curr->value = value;
                return;
            }
            curr = curr->next;
        }

        // Key does not exist, create a new node and insert it at the head of the list
        Node<K, V> *newNode = new Node<K, V>(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        size++;
    }

    /* Look up the value associated with a given key ; worst case O(n), average case O(1) and amortized O(1),
     where n is the number of elements in the hash table.
     Note that the worst case time complexity of the insert and operator[] methods is O(n) because in the worst case scenario,
     all keys would hash to the same index,
     causing the linked list at that index to grow to size n. However,
     the average case and amortized time complexities are O(1) because
     the probability of this worst case scenario occurring is low
     */
    V &operator[](K key)
    {
        // Compute the hash value for the key
        size_t index = hashing<K>(key) % table.size();

        // Search the linked list at the index for the key
        Node<K, V> *curr = table[index];
        while (curr)
        {
            if (curr->key == key)
            {
                // Key found, return the value
                return curr->value;
            }
            curr = curr->next;
        }

        // Key not found, insert a new node with the default value
        insert(key, V());
        return table[index]->value;
    }

    // Print the contents of the hash table in the required output format ; worst case O(n^2), where n is the number of elements in the hash table
    void print_map()
    {
        for (const auto &bucket : table)
        {
            for (const Node<K, V> *curr = bucket; curr; curr = curr->next)
            {
                string date = curr->key;

                // Compute total cost and number of unique receipts for this date

                double total_cost = 0;

                unordered_mapp<string, bool> unique_receipts(100);

                for (auto &entry : curr->value)
                {
                    total_cost += entry.cost;
                    unique_receipts[entry.receipt];
                    unique_receipts[entry.receipt] = true;
                }
                int num_unique_receipts = unique_receipts.realSize;

                // output results
                cout << date << " $" << total_cost << " " << num_unique_receipts << endl;
            }
        }
    }
    void resize()
    {
        // Create a new hash table with double the capacity ; worst case O(n), where n is the number of elements in the hash tabl
        std::vector<Node<K, V> *> newTable(table.size() * 2, nullptr);

        // Move all nodes from the old table to the new table
        for (auto &bucket : table)
        {
            Node<K, V> *curr = bucket;
            while (curr)
            {
                Node<K, V> *next = curr->next;
                size_t index = hashing<K>(curr->key) % newTable.size();
                curr->next = newTable[index];
                newTable[index] = curr;
                curr = next;
            }
        }

        // Replace the old table with the new table
        table = std::move(newTable);
    }
};

int main()
{
    int n;
    cin >> n;
    int currentSize = 100;
    unordered_mapp<string, vector<Entry>> hash_table(100);

    // initialize hash table with initial size of 100

    vector<Entry> vv;
    for (int i = 0; i < n; i++)
    {
        string date, time, receipt, cost_str, title;
        cin >> date >> time >> receipt >> cost_str;
        getline(cin, title);

        // extract cost from cost_str (remove $ sign)
        double cost = stod(cost_str.substr(1));

        // create entry
        Entry entry = {date, receipt, cost};

        // add entry to hash table
        hash_table[date];
        hash_table[date].push_back(entry);
        if (hash_table.size > currentSize)
        {
            // rehash table with double the capacity
            hash_table.resize();
            currentSize *= 2;
        }
    }
    // print the map contents to user
    hash_table.print_map();
}
