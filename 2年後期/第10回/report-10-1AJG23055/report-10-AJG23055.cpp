//codespaceでにてコンパイル
//AJG23055　牧野唯希
//今までの課題とは、大きく異なる範囲でのプログラミングだったが、動画と課題を参照して、理解し、実装することができた。

#include <iostream>
#include <vector>

using namespace std;

#define N_NODE 5

int graph[N_NODE][N_NODE] = {
    {0, 3, 1, 10000, 10000},
    {3, 0, 1, 3, 10000},
    {1, 1, 0, 2, 5},
    {10000, 3, 2, 0, 1},
    {10000, 10000, 5, 1, 0}
};

void dijkstra(int start) {
    vector<int> dist(N_NODE, 10000);
    vector<bool> visited(N_NODE, false);
    vector<int> parent(N_NODE, -1);
    
    dist[start] = 0;
    
    for (int count = 0; count < N_NODE - 1; count++) {
        int u = -1;
        for (int i = 0; i < N_NODE; i++) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }
        
        visited[u] = true;
        
        for (int v = 0; v < N_NODE; v++) {
            if (!visited[v] && graph[u][v] != 10000 && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }
    
    for (int i = 0; i < N_NODE; i++) {
        if (i != start) {
            cout << "route from node " << start << " to node " << i << ": ";
            vector<int> path;
            int current = i;
            while (current != -1) {
                path.push_back(current);
                current = parent[current];
            }
            for (int j = path.size() - 1; j >= 0; j--) {
                cout << path[j];
                if (j > 0) cout << "->";
            }
            cout << " cost = " << dist[i] << endl;
        }
    }
}

int main() {
    int start;
    cout << "Enter the start node: ";
    cin >> start;
    
    if (start < 0 || start >= N_NODE) {
        cout << "Invalid start node" << endl;
        return 1;
    }
    
    dijkstra(start);
    
    return 0;
}