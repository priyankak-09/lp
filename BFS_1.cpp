#include <omp.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX_THREADS = 4; // Maximum number of threads

vector<vector<int> > graph; // Adjacency list representation of the graph
vector<bool> visited;       // Keep track of visited vertices
queue<int> q;               // Queue for BFS traversal

void parallel_bfs(int start_vertex) {
    int num_vertices = graph.size();

    // Initialize visited array
    #pragma omp parallel for
    for (int i = 0; i < num_vertices; ++i) {
        visited[i] = false;
    }

    // Mark the start vertex as visited and enqueue it
    visited[start_vertex] = true;
    q.push(start_vertex);

    while (!q.empty()) {
        #pragma omp parallel num_threads(MAX_THREADS)
        {
            #pragma omp for
            for (int i = 0; i < static_cast<int>(q.size()); ++i) {
                int u = q.front();
                q.pop();

                // Process vertex u
                // Example: Print the vertex
                #pragma omp critical
                {
                    cout << "Visiting vertex: " << u << endl;
                }

                // Explore neighbors of vertex u
                for (size_t j = 0; j < graph[u].size(); ++j) {
                    int v = graph[u][j];
                    if (!visited[v]) {
                        // Mark v as visited and enqueue it
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }
}

int main() {
    // Initialize the graph (example)
    int num_vertices = 10;
    graph.resize(num_vertices);
    visited.resize(num_vertices);

    // Add edges (example)
    graph[0].push_back(1);
    graph[0].push_back(5);
    graph[1].push_back(0);
    graph[1].push_back(2);
    graph[1].push_back(3);
    graph[2].push_back(1);
    graph[3].push_back(1);
    graph[3].push_back(4);
    graph[4].push_back(3);
    graph[4].push_back(5);
    graph[5].push_back(0);
    graph[5].push_back(4);
   
    
    // Perform parallel BFS from vertex 0
    parallel_bfs(0);

    return 0;
}

