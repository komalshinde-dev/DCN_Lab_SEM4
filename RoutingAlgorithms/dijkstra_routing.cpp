#include <iostream>     
#include <map>          // For map (associative container)
#include <string>       // For using strings as node names
#include <limits>       // For numeric_limits to represent infinity

using namespace std;

// Define Graph type as a map of node names to their neighbors and edge costs
using Graph = map<string, map<string, int>>;

// Function to build the graph based on user input
Graph create_graph() {
    Graph graph;
    int num_nodes;

    // Ask user for number of nodes
    cout << "Enter number of nodes: ";
    cin >> num_nodes;
    cin.ignore();  // Clear newline character from input buffer

    // Input all node names
    cout << "Enter node names:\n";
    for (int i = 0; i < num_nodes; ++i) {
        string node;
        getline(cin, node);           // Read node name
        graph[node] = map<string, int>();  // Initialize empty neighbor list
    }

    // Ask user for number of edges
    int num_edges;
    cout << "\nEnter number of edges: ";
    cin >> num_edges;
    cin.ignore();

    // Input all edges with costs
    cout << "Enter edges and costs:\n";
    for (int i = 0; i < num_edges; ++i) {
        string u, v;
        int cost;

        cout << "From node: ";
        getline(cin, u);  // Start node

        cout << "To node: ";
        getline(cin, v);  // End node

        cout << "Cost from " << u << " to " << v << ": ";
        cin >> cost;
        cin.ignore();     // Clear buffer

        // Add edge in both directions (assuming undirected graph)
        graph[u][v] = cost;
        graph[v][u] = cost;
    }

    return graph;  // Return the constructed graph
}

// Optional: Function to display the entire graph structure
void print_graph(const Graph& graph) {
    cout << "\n--- Graph Structure ---\n";
    for (const auto& node : graph) {
        cout << node.first << " -> ";
        for (const auto& neighbor : node.second) {
            cout << "(" << neighbor.first << ", cost: " << neighbor.second << ") ";
        }
        cout << endl;
    }
}

// Function implementing the Distance Vector Routing algorithm using Bellman-Ford
void distance_vector(const Graph& graph, const string& source) {
    cout << "\n--- Distance Vector Routing (Bellman-Ford Algorithm) ---\n";

    map<string, int> distance;  // Store shortest distances from source

    // Step 1: Initialize distances to all nodes as infinity
    for (const auto& pair : graph) {
        distance[pair.first] = numeric_limits<int>::max();  // infinity
    }
    distance[source] = 0;  // Distance to source is 0

    int V = graph.size();  // Number of vertices

    // Step 2: Relax all edges (V - 1) times
    for (int i = 0; i < V - 1; ++i) {
        for (const auto& u_pair : graph) {
            string u = u_pair.first;
            for (const auto& v_pair : u_pair.second) {
                string v = v_pair.first;
                int cost = v_pair.second;

                // Relax edge if a shorter path is found
                if (distance[u] != numeric_limits<int>::max() &&
                    distance[u] + cost < distance[v]) {
                    distance[v] = distance[u] + cost;
                }
            }
        }
    }

    // Step 3: Output the final shortest distances
    cout << "\nShortest distances from source '" << source << "':\n";
    for (const auto& p : distance) {
        cout << "To " << p.first << " = ";
        if (p.second == numeric_limits<int>::max()) {
            cout << "Infinity (unreachable)\n";
        } else {
            cout << p.second << endl;
        }
    }
}

int main() {
    // Step 1: Build the graph using user input
    Graph graph = create_graph();

    // Optional: Print the constructed graph for verification
    print_graph(graph);

    // Step 2: Ask user for source node
    cout << "\nEnter source node: ";
    string source;
    getline(cin, source);

    // Step 3: Run Distance Vector Routing from the source
    distance_vector(graph, source);

    return 0;
}
