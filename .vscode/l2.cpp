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
        cout<<"addition to the minimum cost if node is visited :"<<minCost<<endl;
        
        // Enqueue all unvisited neighbors
        cout<<"enqueueing all unvisited neighbours :"<<endl;
        for (int i = 0; i < n; i++) {
            if (i != node && !visited[i]) {
                pq.push(make_pair(graph[node][i], i));
                cout <<graph[node][i]<<endl;
            }
        }
    }
    
    // Add cost to return to the starting node
    minCost += graph[start][0];
    cout<<"Final minimum cost :"<<minCost<<endl;
    
    return minCost;
}

// Function to find the minimum cost using Greedy BFS
int tspGreedyBFS(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    
    // Queue to store the states (node, cost)
    queue<pair<int, int>> q;
    
    // Visited array to mark visited nodes
    vector<bool> visited(n, false);
    
    // Enqueue the starting node with cost 0
    q.push(make_pair(start, 0));
    
    
    int minCost = 0;
    
    while (!q.empty()) {
        pair<int, int> front = q.front();
        q.pop();
        
        int node = front.first;
        int cost = front.second;
        
        // Skip if node is already visited
        if (visited[node])
            continue;
        
        // Mark node as visited
        visited[node] = true;
        cout<<"Node visited"<<visited[node]<<endl;
        
        // Add cost to minimum cost
        minCost += cost;
        cout<<"New cost"<<minCost<<endl;
        
        // Enqueue all unvisited neighbors in increasing order of cost
        vector<pair<int, int>> neighbors;
        for (int i = 0; i < n; i++) {
            if (i != node && !visited[i]) {
                neighbors.push_back(make_pair(graph[node][i], i));
                cout<<"Enqueueing unvisited in increasing order"<<graph[node][i]<<endl;
               
            }
        }
        
        sort(neighbors.begin(), neighbors.end());
        
        for (const auto& neighbor : neighbors) {
            q.push(make_pair(neighbor.second, neighbor.first));
        }
    }
    
    // Add cost to return to the starting node
    minCost += graph[start][0];
    cout<<"Adding cost to the starting state: "<<minCost<<endl;
    
    return minCost;
}

// Heuristic function for A* search
int tspHeuristic(const vector<vector<int>>& graph, vector<bool>& visited, int node, int depth) {
    int n = graph.size();
    
    // Mark the current node as visited
    visited[node] = true;
    
    // If all nodes have been visited, return the cost of returning to the starting node
    if (depth == n - 1)
        return graph[node][0];
    
    int minCost = INF;
    
    // Explore unvisited neighbors recursively and select the minimum cost
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int cost = graph[node][i] + tspHeuristic(graph, visited, i, depth + 1);
            minCost = min(minCost, cost);
            cout<<"updated cost: "<<minCost<<endl;
        }
    }
    
    // Mark the current node as unvisited for backtracking
    visited[node] = false;
    
    return minCost;
}

// Function to find the minimum cost using A* search
int tspAStar(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    
    // Vector to mark visited nodes
    vector<bool> visited(n, false);
    
    // Calculate the heuristic cost for the starting node
    int heuristic = tspHeuristic(graph, visited, start, 0);
    
    // Priority queue to store the states (node, cost)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    // Enqueue the starting node with cost 0 + heuristic
    pq.push(make_pair(0 + heuristic, start));
    
    int minCost = 0;
    
    while (!pq.empty()) {
        pair<int, int> top = pq.top();
        pq.pop();
        
        int node = top.second;
        int cost = top.first - tspHeuristic(graph, visited, node, 0);
        cout<<"cost: "<<cost<<endl;
        // Skip if node is already visited
        if (visited[node])
            continue;
        
        // Mark node as visited
        visited[node] = true;
        cout<<"visited node: "<<visited[node]<<endl;
        
        // Add cost to minimum cost
        minCost += cost;
        cout<<"Updating the cost: "<<minCost<<endl;
        
        // Enqueue all unvisited neighbors with updated cost + heuristic
        for (int i = 0; i < n; i++) {
            if (i != node && !visited[i]) {
                int newCost = cost + graph[node][i] + tspHeuristic(graph, visited, i, 0);
                pq.push(make_pair(newCost, i));
            }
        }
    }
    
    // Add cost to return to the starting node
    minCost += graph[start][0];
    
    return minCost;
}

int main() {
    
    
    // Create the adjacency matrix representing the graph
    vector<vector<int>> graph = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    
   
    int start=0;
    
    
    int minCostUniform = tspUniformCost(graph, start);
    
    
    
    cout << "Minimum cost using Uniform Cost Search: " << minCostUniform << endl;
    cout<<"--------------------------------------------------------------------------"<<endl;
    int minCostGreedy = tspGreedyBFS(graph, start);
    cout << "Minimum cost using Greedy BFS: " << minCostGreedy << endl;
    cout<<"--------------------------------------------------------------------------"<<endl;
    int minCostAStar = tspAStar(graph, start);
    cout << "Minimum cost using A* Search: " << minCostAStar << endl;
    
    return 0;
}
