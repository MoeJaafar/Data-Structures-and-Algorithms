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
void merge_sort(vector<pair<string, int>> &words, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        merge_sort(words, l, m);
        merge_sort(words, m + 1, r);
        int i = l, j = m + 1, k = 0;
        vector<pair<string, int>> temp(r - l + 1);
        while (i <= m && j <= r)
        {
            if (words[i].second == words[j].second)
            {
                if (words[i].first < words[j].first)
                {
                    temp[k++] = words[i++];
                }
                else
                {
                    temp[k++] = words[j++];
                }
            }
            else if (words[i].second > words[j].second)
            {
                temp[k++] = words[i++];
            }
            else
            {
                temp[k++] = words[j++];
            }
        }
        while (i <= m)
        {
            temp[k++] = words[i++];
        }
        while (j <= r)
        {
            temp[k++] = words[j++];
        }
        for (int a = l, b = 0; a <= r; a++, b++)
        {
            words[a] = temp[b];
        }
    }
}

int main()
{
    int n;
    cin >> n;

    Map *map = new HashMap();
    Map *map_ = new HashMap();
    vector<string> words(n);
    for (int i = 0; i < n; i++)
    {
        cin >> words[i];
        if (map->contains(words[i]))
        {
            map->put(words[i], map->get(words[i]) + 1);
        }
        else
        {
            map->put(words[i], 1);
        }
    }

    vector<pair<string, int>> pairs;
    for (string word : words)
    {
        if (map->contains(word) && !map_->contains(word))
        {
            map_->put(word, 1);
            pairs.push_back(make_pair(word, map->get(word)));
        }
    }

    merge_sort(pairs, 0, pairs.size() - 1);

    for (auto &pair : pairs)
    {
        cout << pair.first << " " << pair.second << endl;
    }

    return 0;
}
