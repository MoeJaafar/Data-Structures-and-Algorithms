// Mohammad Jaafar
#include <iostream>
#include <vector>
#include <list>

using namespace std;

// define a templated Graph class
template <typename T>
class Graph
{
public:
    // constructor takes the number of vertices
    Graph(int n) : numVertices(n), adjList(n) {}

    // method to add an edge to the graph
    void addEdge(int src, int dest, T weight)
    {
        adjList[src].push_back({dest, weight});
    }

    // method to check if there is a path between two vertices in the graph
    bool isReachable(int start, int end)
    {
        // initialize a vector to keep track of visited vertices
        vector<bool> visited(numVertices, false);
        // initialize a list to act as a queue for BFS
        list<int> queue;
        // mark the starting vertex as visited and add it to the queue
        visited[start] = true;
        queue.push_back(start);

        // perform BFS
        while (!queue.empty())
        {
            // get the current vertex from the front of the queue
            int current = queue.front();
            queue.pop_front();
            // if the current vertex is the end vertex, return true
            if (current == end)
            {
                return true;
            }
            // add unvisited neighbors to the queue and mark them as visited
            for (auto neighbor : adjList[current])
            {
                int neighborIndex = neighbor.first;
                if (!visited[neighborIndex])
                {
                    visited[neighborIndex] = true;
                    queue.push_back(neighborIndex);
                }
            }
        }
        // if the end vertex was not found, return false
        return false;
    }

private:
    // number of vertices in the graph
    int numVertices;
    // adjacency list representing the graph
    vector<list<pair<int, T>>> adjList;
};

// main function
int main()
{
    // read in the number of vertices in the graph
    int n;
    cin >> n;
    // create a graph with n vertices
    Graph<int> g(n);
    // read in the adjacency matrix and add edges to the graph as necessary
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int value;
            cin >> value;
            if (value == 1)
            {
                g.addEdge(i, j, 1);
            }
        }
    }
    // check if there is a path between every pair of vertices in the graph
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!g.isReachable(i, j))
            {
                // if there is no path between a pair of vertices, output "NO" and exit
                cout << "NO\n";
                return 0;
            }
        }
    }
    // if there is a path between every pair of vertices, output "YES"
    cout << "YES\n";
    return 0;
}
