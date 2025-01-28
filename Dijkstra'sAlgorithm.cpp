#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <stack>

using namespace std;

// For the priority queue, (distance, vertex) define a pair. 
typedef pair<int, int> pii;

// The Dijkstra's Algorithm function
void dijkstra(const vector<vector<pii>>& graph, int source, int destination) {
    int n = graph.size();
    vector<int> distance(n, INT_MAX); // array distance
    vector<int> parent(n, -1);       // Parent array for path reconstruction
    priority_queue<pii, vector<pii>, greater<pii>> pq; // Min-heap

    distance[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        if (currentDist > distance[currentNode]) continue;

        for (const auto& neighbor : graph[currentNode]) {
            int neighborNode = neighbor.first;
            int edgeWeight = neighbor.second;

            if (distance[currentNode] + edgeWeight < distance[neighborNode]) {
                distance[neighborNode] = distance[currentNode] + edgeWeight;
                parent[neighborNode] = currentNode;
                pq.push({distance[neighborNode], neighborNode});
            }
        }
    }

    // Output the cost and shortest path
    if (distance[destination] == INT_MAX) {
        cout << "No path from " << source << " to " << destination << endl;
        return;
    }

    cout << "Shortest path cost: " << distance[destination] << endl;

    stack<int> path;
    for (int at = destination; at != -1; at = parent[at]) {
        path.push(at);
    }

    cout << "Path: ";
    while (!path.empty()) {
        cout << path.top();
        path.pop();
        if (!path.empty()) cout << " -> ";
    }
    cout << endl;
}

int main() {
    // Define graph as a adjacency list
    // graph[node] = { {neighbor, weight}, ... }
    vector<vector<pii>> graph = {
        {{1, 10}, {4, 3}},  // Neighbors of the vertex 0
        {{2, 2}},           // Neighbors of the vertex 1
        {{3, 9}},           // Neighbors of the vertex 2
        {},                 // Neighbors of the vertex 3
        {{1, 1}, {2, 8}}    // Neighbors of the vertex 4
    };

    int source, destination;
    cout << "Enter source vertex: ";
    cin >> source;
    cout << "Enter destination vertex: ";
    cin >> destination;

    dijkstra(graph, source, destination);

    return 0;
}

/* Example Input and Output: Enter source vertex: 0(User Input)
Enter destination vertex: 3(User Input)
Shortest path cost: 15
Path: 0 -> 4 -> 1 -> 2 -> 3 */
