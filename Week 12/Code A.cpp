// Mohammad Jaafar
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <utility>
#include <limits>

using namespace std;

// This program implements Prim's algorithm to find the minimum spanning tree of a graph
// The graph is created by adding vertices with penalties and edges with distances, and then finding the minimum spanning tree using Prim's algorithm

// Class representing the graph
class Graph
{
public:
    // Insert a vertex with a penalty
    void insertVertex(const string &name, int penalty)
    {
        vertices[name] = penalty;
    }

    // Insert an edge between two vertices with a distance
    void insertEdge(const string &a, const string &b, double distance)
    {
        // Calculate the weight of the edge as the distance divided by the sum of the penalties of the two vertices
        double weight = distance / (vertices[a] + vertices[b]);

        // Add the edge to the adjacency list of both vertices
        adjList[a].push_back({b, weight});
        adjList[b].push_back({a, weight});
    }

    // Find the minimum spanning tree of the graph using Prim's algorithm
    vector<pair<string, string>> primMST()
    {
        unordered_map<string, bool> visited;
        mst.clear(); // Reset the MST vector
        auto cmp = [](const auto &a, const auto &b)
        {
            return a.second > b.second;
        };
        priority_queue<pair<pair<string, string>, double>, vector<pair<pair<string, string>, double>>, decltype(cmp)> pq(cmp);

        // Iterate over all vertices
        for (const auto &vertex : vertices)
        {
            // If the vertex has not been visited yet, add its edges to the priority queue
            if (!visited[vertex.first])
            {
                visited[vertex.first] = true;
                for (const auto &edge : adjList[vertex.first])
                {
                    pq.push({{vertex.first, edge.first}, edge.second});
                }

                // Find the minimum spanning tree using Prim's algorithm
                while (!pq.empty())
                {
                    auto edge = pq.top();
                    pq.pop();

                    // If the second vertex of the edge has not been visited yet, add its edges to the priority queue
                    if (!visited[edge.first.second])
                    {
                        visited[edge.first.second] = true;
                        for (const auto &nextEdge : adjList[edge.first.second])
                        {
                            pq.push({{edge.first.second, nextEdge.first}, nextEdge.second});
                        }

                        // Add the edge to the MST if it connects a visited and an unvisited vertex
                        mst.push_back(edge.first);
                    }
                }
            }
        }
        return mst;
    }

private:
    unordered_map<string, int> vertices;                         // Map of vertices and their penalties
    unordered_map<string, vector<pair<string, double>>> adjList; // Adjacency list of the graph
    vector<pair<string, string>> mst;                            // Minimum spanning tree of the graph
};

// Main function
int main()
{
    int N;
    cin >> N;

    Graph g;

    // Iterate over all commands
    for (int i = 0; i < N; ++i)
    {
        string command;
        cin >> command;

        // If the command is ADD, insert a vertex with a penalty
        if (command == "ADD")
        {
            string branch_name;
            int penalty;
            cin >> branch_name >> penalty;
            g.insertVertex(branch_name, penalty);
        }
        // If the command is CONNECT, insert an edge between two vertices with a distance
        else if (command == "CONNECT")
        {

            string branch_name_1, branch_name_2;
            double distance;
            cin >> branch_name_1 >> branch_name_2 >> distance;
            g.insertEdge(branch_name_1, branch_name_2, distance);
        }
        else if (command == "PRINT_MIN")
        {
            auto mst = g.primMST(); // calculate the minimum spanning tree using Prim's algorithm
            // output the MST pairs in the format "distance:branch1 branch2 ..."
            for (const auto &edge : mst)
            {
                cout << edge.first << ":" << edge.second << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
