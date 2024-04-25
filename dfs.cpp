#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

class Graph {
    int V;
    vector<vector<int> > adj;

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void parallelDFS(int start) {
        vector<bool> visited(V, false);
        stack<int> stack;
        stack.push(start);

        #pragma omp parallel
        {
            while (!stack.empty()) {
                int v;

                #pragma omp critical
                {
                    v = stack.top();
                    stack.pop();
                }

                if (!visited[v]) {
                    visited[v] = true;
                    cout << v << " ";

                    #pragma omp for schedule(static)
                    for (int i = adj[v].size() - 1; i >= 0; --i) {
                        int u = adj[v][i];
                        if (!visited[u]) {
                            #pragma omp critical
                            {
                                stack.push(u);
                            }
                        }
                    }
                }
            }
        }
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);

    cout << "DFS traversal starting from node 0: ";
    g.parallelDFS(0);
    cout << endl;

    return 0;
}
