// Mohammad Jaafar
//  This code implements Dijkstra's algorithm to find the shortest path from a source node to a target node
//  in a weighted graph with edges that have a minimum bandwidth.
//  The program reads in the graph and its edges as input from standard input and outputs the shortest path
//  distance, minimum bandwidth, and the path from the source to the target node.

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <algorithm>

using namespace std;

template <typename T, typename Compare = std::less<T>>
class priority_qeueue
{
public:
    // Inserts an element into the priority queue
    void push(const T &value)
    {
        data.push_back(value);
        std::push_heap(data.begin(), data.end(), compare);
    }

    // Removes the top element from the priority queue
    void pop()
    {
        std::pop_heap(data.begin(), data.end(), compare);
        data.pop_back();
    }

    // Returns the top element of the priority queue
    const T &top() const
    {
        return data.front();
    }

    // Checks if the priority queue is empty
    bool empty() const
    {
        return data.empty();
    }

    // Returns the size of the priority queue
    size_t size() const
    {
        return data.size();
    }

private:
    std::vector<T> data;
    Compare compare;
};

// Class for the graph data structure
template <typename T>
class Graph
{
private:
    vector<vector<pair<T, T>>> graph; // 2D vector to store the graph with weights as pairs
    int n;                            // Number of nodes in the graph

public:
    Graph(int n) : n(n)
    {
        graph.assign(n, vector<pair<T, T>>(n, make_pair(0, 0))); // Initialize the graph with 0 weights
    }

    // Method to add edges to the graph
    void addEdge(int u, int v, pair<T, T> weight)
    {
        graph[u][v] = weight;
    }

    // Method to get neighbors of a given node
    vector<pair<int, pair<T, T>>> getNeighbors(int u)
    {
        vector<pair<int, pair<T, T>>> neighbors;
        for (int v = 0; v < n; v++)
        {
            if (graph[u][v].first != 0)
            {
                neighbors.push_back(make_pair(v, graph[u][v]));
            }
        }
        return neighbors;
    }
};

// Define a pair of integers
typedef pair<int, int> pii;

// Define infinity
const int INF = numeric_limits<int>::max();

int main()
{
    int n, m;
    cin >> n >> m;
    // Create a graph with n nodes
    Graph<int> g(n);

    // Read in the edges and their weights from standard input
    for (int i = 0; i < m; i++)
    {
        int u, v, w, b;
        cin >> u >> v >> w >> b;
        g.addEdge(u - 1, v - 1, make_pair(w, b)); // Add edge to graph (subtract 1 for 0-indexing)
    }

    int s, t, W;
    cin >> s >> t >> W;
    s--;
    t--; // Subtract 1 for 0-indexing

    // Initialize distance, previous node, and bandwidth vectors
    vector<int> dist(n, INF);
    vector<int> prev(n, -1);
    vector<int> bandwidth(n, INF);
    dist[s] = 0;
    bandwidth[s] = INF;

    // Priority queue to store nodes to be visited in Dijkstra's algorithm
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push(make_pair(0, s));

    // Run Dijkstra's algorithm
    while (!pq.empty())
    {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (u == t)
            break; // If target node is reached, exit loop

        // Iterate over the neighbors of the current node
        for (auto e : g.getNeighbors(u))
        {
            int v = e.first;         // The neighbor node
            int w = e.second.first;  // The weight of the edge
            int b = e.second.second; // The bandwidth of the edge

            // Calculate the new distance and bandwidth
            int newDist = d + w;
            int newBandwidth = min(bandwidth[u], b);

            // If the new distance is less than the current distance and the new bandwidth is greater than or equal to W,
            // update the distance, previous node, and bandwidth vectors and add the neighbor to the priority queue
            if (newDist < dist[v] && newBandwidth >= W)
            {
                dist[v] = newDist;
                prev[v] = u;
                bandwidth[v] = newBandwidth;
                pq.push(make_pair(newDist, v));
            }
        }
    }
    // If target node is not reachable from source node, output "IMPOSSIBLE"
    if (prev[t] == -1)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else // Otherwise, output the shortest path distance, minimum bandwidth, and path
    {
        vector<int> path;
        int curr = t;
        while (curr != s)
        {
            path.push_back(curr + 1);
            curr = prev[curr];
        }
        path.push_back(s + 1);
        reverse(path.begin(), path.end()); // Reverse the path to get the correct order

        cout << path.size() << " " << dist[t] << " " << bandwidth[t] << endl;
        for (auto v : path)
        {
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}
