// Mohammad Jaafar
#include <iostream>
#include <vector>
using namespace std;

// struct to hold item information
struct Item
{
    int index;
    int current_bid;
    int maximal_bid;
};

// counting sort by maximal bid
vector<Item> counting_sort_maximal_bid(vector<Item> &items, int k)
{
    vector<int> count(k + 1, 0);
    vector<Item> result(items.size());

    for (int i = 0; i < items.size(); i++)
    {
        count[items[i].maximal_bid]++;
    }

    for (int i = k - 1; i >= 0; i--)
    {
        count[i] += count[i + 1];
    }

    for (int i = 0; i < items.size(); i++)
    {
        int j = count[items[i].maximal_bid] - 1;
        result[j] = items[i];
        count[items[i].maximal_bid]--;
    }

    return result;
}

// counting sort by current bid
vector<int> counting_sort_current_bid(vector<Item> &items, int k)
{
    vector<int> count(k + 1, 0);
    vector<int> result(items.size());

    for (int i = 0; i < items.size(); i++)
    {
        count[items[i].current_bid]++;
    }

    for (int i = k - 1; i >= 0; i--)
    {
        count[i] += count[i + 1];
    }

    for (int i = 0; i < items.size(); i++)
    {
        result[count[items[i].current_bid] - 1] = items[i].index;
        count[items[i].current_bid]--;
    }

    return result;
}

int main()
{
    int n;
    cin >> n;

    vector<Item> items(n);
    for (int i = 0; i < n; i++)
    {
        items[i].index = i;
        cin >> items[i].current_bid >> items[i].maximal_bid;
    }

    // sort by maximal bid
    items = counting_sort_maximal_bid(items, 100000);

    // sort by current bid
    vector<int> result = counting_sort_current_bid(items, 100);

    // output result
    for (int i = 0; i < n; i++)
    {
        cout << result[i] + 1 << " "; // add 1 to index to match problem statement
    }
    cout << endl;

    return 0;
}
