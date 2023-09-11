#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

// Function to find the minimum cost using Uniform Cost Search
int tspUniformCost(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    
    // Priority queue to store the states (node, cost)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    // Visited array to mark visited nodes
    vector<bool> visited(n, false);
    
    // Enqueue the starting node with cost 0
    pq.push(make_pair(0, start));
    
    int minCost = 0;
    
    while (!pq.empty()) {
        pair<int, int> top = pq.top();
        pq.pop();
        
        int node = top.second;
        int cost = top.first;
        
        // Skip if node is already visited
        if (visited[node])
            continue;
        
        // Mark node as visited
        visited[node] = true;
        
        // Add cost to minimum cost
        minCost += cost;
        
        // Enqueue all unvisited neighbors
        for (int i = 0; i < n; i++) {
            if (i != node && !visited[i]) {
                pq.push(make_pair(graph[node][i], i));
            }
        }
    }
    
    // Add cost to return to the starting node
    minCost += graph[start][0];
    
    return minCost;
}

int main() {
    int n;
    cout << "Enter the number of cities: ";
    cin >> n;
    
    // Create the adjacency matrix representing the graph
    vector<vector<int>> graph(n, vector<int>(n));
    
    cout << "Enter the cost matrix: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }
    
    int start;
    cout << "Enter the starting city: ";
    cin >> start;
    
    int minCost = tspUniformCost(graph, start);
    
    cout << "Minimum cost: " << minCost << endl;
    
    return 0;
}

