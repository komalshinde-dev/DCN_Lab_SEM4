#include <iostream>     
#include <map>          // For using map to represent graph (adjacency list)
#include <queue>        // For priority queue used in Dijkstra's algorithm
#include <string>       // For using strings as node names
#include <limits>       // For representing infinity (max int value)

using namespace std;

// Define 'Graph' as a type alias for map of maps.
// Each node maps to another map of its neighbors and edge costs.
using Graph = map<string, map<string, int>>;

// Function to create a graph using user input
Graph create_graph() {
    Graph graph;
    int num_nodes;

    // Ask user for number of nodes
    cout << "Enter number of nodes: ";
    cin >> num_nodes;
    cin.ignore();  // Clear the newline character left in input buffer

    // Read each node's name and initialize its adjacency list
    cout << "Enter node names:\n";
    for (int i = 0; i < num_nodes; ++i) {
        string node;
        getline(cin, node);           // Read the node name
        graph[node] = map<string, int>();  // Initialize its neighbors map
    }

    int num_edges;
    cout << "\nEnter number of edges: ";
    cin >> num_edges;
    cin.ignore();  // Clear buffer again

    // Read each edge with its cost
    cout << "Enter edges and their costs:\n";
    for (int i = 0; i < num_edges; ++i) {
        string u, v;
        int cost;

        cout << "From node: ";
        getline(cin, u);

        cout << "To node: ";
        getline(cin, v);

        cout << "Cost from " << u << " to " << v << ": ";
        cin >> cost;
        cin.ignore();

        // Since the graph is undirected, add both directions
        graph[u][v] = cost;
        graph[v][u] = cost;
    }

    return graph;  // Return the constructed graph
}

// Function to print the graph structure (adjacency list)
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

// Function to perform Link-State routing using Dijkstra's algorithm
void link_state(const Graph& graph, const string& source) {
    cout << "\n--- Link-State Routing (Dijkstra's Algorithm) ---\n";

    // Distance map to store shortest distance from source to each node
    map<string, int> distance;

    // Initialize all distances to infinity (max integer value)
    for (const auto& node : graph) {
        distance[node.first] = numeric_limits<int>::max();
    }

    // Distance to source node is zero
    distance[source] = 0;

    // Priority queue (min-heap) to choose node with smallest tentative distance
    using P = pair<int, string>;  // Pair of (distance, node)
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({0, source});  // Start from the source node

    map<string, bool> visited;  // To track visited nodes

    // Main loop: process nodes until queue is empty
    while (!pq.empty()) {
        int current_dist = pq.top().first;    // Smallest distance
        string current_node = pq.top().second; // Node with that distance
        pq.pop();  // Remove it from queue

        // Skip if already visited
        if (visited[current_node]) continue;
        visited[current_node] = true;

        // Check all neighbors of the current node
        for (const auto& neighbor : graph.at(current_node)) {
            string neighbor_node = neighbor.first;
            int edge_cost = neighbor.second;

            // If a shorter path is found to the neighbor
            if (current_dist + edge_cost < distance[neighbor_node]) {
                distance[neighbor_node] = current_dist + edge_cost;
                pq.push({distance[neighbor_node], neighbor_node});  // Push updated distance to queue
            }
        }
    }

    // Display the final shortest distances from source to all other nodes
    cout << "\nShortest distances from source '" << source << "':\n";
    for (const auto& entry : distance) {
        cout << "To " << entry.first << " = ";
        if (entry.second == numeric_limits<int>::max()) {
            cout << "Infinity (unreachable)\n";
        } else {
            cout << entry.second << endl;
        }
    }
}

int main() {
    // Step 1: Create the graph from user input
    Graph graph = create_graph();

    // Step 2: Show the complete graph structure
    print_graph(graph);

    // Step 3: Ask the user for the source node
    cout << "\nEnter source node: ";
    string source;
    getline(cin, source);

    // Step 4: Run Link-State Routing (Dijkstra's Algorithm)
    link_state(graph, source);

    return 0;
}
