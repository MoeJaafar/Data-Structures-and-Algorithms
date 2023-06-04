// Mohammad Jaafar
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int kTableSize = 1000007;

class Map
{
public:
    virtual void put(const string &key, int value) = 0;
    virtual int get(const string &key) = 0;
    virtual bool contains(const string &key) = 0;
};

class HashMap : public Map
{
public:
    HashMap()
    {
        keys_.resize(kTableSize);
        values_.resize(kTableSize);
        for (int i = 0; i < kTableSize; i++)
        {
            keys_[i] = "";
            values_[i] = -1;
        }
    }

    void put(const string &key, int value)
    {
        int index = hash(key);
        while (keys_[index] != "" && keys_[index] != key)
        {
            index = (index + 1) % kTableSize;
        }
        keys_[index] = key;
        values_[index] = value;
    }

    int get(const string &key)
    {
        int index = hash(key);
        while (keys_[index] != "" && keys_[index] != key)
        {
            index = (index + 1) % kTableSize;
        }
        return values_[index];
    }

    bool contains(const string &key)
    {
        int index = hash(key);
        while (keys_[index] != "" && keys_[index] != key)
        {
            index = (index + 1) % kTableSize;
        }
        return keys_[index] != "";
    }

private:
    int hash(const string &key)
    {
        int hash_value = 0;
        for (char c : key)
        {
            hash_value = (hash_value * 31 + c) % kTableSize;
        }
        return hash_value;
    }

    vector<string> keys_;
    vector<int> values_;
};

int main()
{
    int n, m;
    cin >> n;
    string s;
    HashMap map;
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        map.put(s, 1);
    }
    cin >> m;
    vector<string> words;
    for (int i = 0; i < m; i++)
    {
        cin >> s;
        if (!map.contains(s))
        {
            words.push_back(s);
            map.put(s, 1);
        }
    }
    cout << words.size() << endl;
    for (const string &word : words)
    {
        cout << word << endl;
    }
    return 0;
}
