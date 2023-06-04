//Mohammad Jaafar
#include <bits/stdc++.h>
using namespace std;

int n = 0;

// Define a class template for a graph with vertices of type V and edges of type E
template <typename V, typename E>
class Graph
{
public:
    map<V, map<V, E>> vertices; // Use a map to store vertices and their edges with weights

    // Function to add an edge from vertex u to vertex v with weight "weight"
    void addingEdge(V u, V v, E weight)
    {
        vertices[u][v] = weight;
    }
    
     // Function to add a vertex with label v to the graph
    void addingVer(V v)
    {
        vertices[v] = map<V, E>();
    }

    // Function to check if there is a negative cycle in the graph using the Bellman-Ford algorithm
    bool foundNegativeCycle()
    {
        map<V, int> dist; // Map to store the shortest distance to each vertex from the starting vertex
        map<V, V> pre; // Map to store the predecessor vertex of each vertex in the shortest path
        V beginn = vertices.begin()->first; // Choose the starting vertex as the first vertex in the map

        // Initialize dist and pre maps
        for (auto v : vertices)
        {
            dist[v.first] = 10000; // Set the distance of each vertex to a large number
            pre[v.first] = V(); // Set the predecessor of each vertex to a null vertex
        }

        dist[beginn] = 0; // Set the distance of the starting vertex to zero

        // Perform Bellman-Ford algorithm for n iterations where n is the number of vertices in the graph
        for (int i = 1; i <= vertices.size(); i++)
        {
            for (auto u : vertices)
            {
                for (auto v : u.second)
                {
                    E weight = v.second; // Get the weight of the edge from vertex u to vertex v
                    int alt = dist[u.first] + (int)weight; // Calculate the new distance to vertex v through vertex u
                    if (alt < dist[v.first])   // If the new distance is smaller than the current distance to vertex v
                    {
                        dist[v.first] = alt; // Update the distance to vertex v
                        pre[v.first] = u.first; // Update the predecessor of vertex v in the shortest path
                    }
                }
            }
        }

        // Check for negative cycles by iterating over all edges in the graph
        for (auto u : vertices)
        {
            for (auto v : u.second)
            {
                E weight = v.second; // Get the weight of the edge from vertex u to vertex v
                int alt = dist[u.first] + (int)weight; // Calculate the new distance to vertex v through vertex u
                if (alt < dist[v.first])   // If the new distance is smaller than the current distance to vertex v
                {
                    // Negative cycle is found
                    vector<V> cycle; // Vector to store the vertices in the negative cycle
                    V current = v.first; // Start from the vertex v in the negative cycle
                    V cnt = v.first;
                    for (int i = 0; i < n; i++)
                    {
                        cnt = pre[cnt]; // Move cnt back n steps to get to the start of the negative cycle
                    }
                    current = cnt;
                    while (true)   // Traverse the negative cycle until the starting vertex is reached again
                    {
                        cycle.push_back(current); // Add the current vertex to the cycle vector
                        // Break out of the loop if we reach the starting vertex and the cycle has more than one vertex
                        if (current == cnt && cycle.size() > 1)
                        {
                            break;
                        }
                        current = pre[current];
                    }
                    // Reverse the cycle vector since we traversed it backwards
                    reverse(cycle.begin(), cycle.end());
                    // Output the cycle and return true
                    cout << "YES" << endl;
                    cout << cycle.size() - 1 << endl;
                    for (int i = 0; i < cycle.size() - 1; i++)
                    {
                        cout << cycle[i] << " ";
                    }
                    return true;
                }
            }
        }

// If no negative cycle was found, output "NO" and return false
        cout << "NO" << endl;
        return false;
    }
};

int main()
{
    cin >> n; // Reads the size of the graph
    Graph<int, int> graph; // Creates an instance of the Graph class
    // Loop over the vertices of the graph and add them to the graph
    for (int i = 1; i <= n; i++)
    {
        graph.addingVer(i);

        // Loop over the edges of the vertex and add them to the graph
        for (int j = 1; j <= n; j++)
        {
            int weight;
            cin >> weight; // Reads the weight of the edge
            if (weight != 100000)   // If weight is not infinity
            {
                graph.addingEdge(i, j, weight); // Add the edge to the graph
            }
        }
    }

// Call the foundNegativeCycle function to check if there is a negative cycle in the graph
    graph.foundNegativeCycle();

    return 0;

}
