#include <iostream>
#include "dijkstras.cpp"
using namespace std;

int main() {
    int N, E;
    cin >> N >> E;
    Graph g;
    g.adjacencyList.resize(N);
    for(int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.adjacencyList[u].push_back({v, w});
        g.adjacencyList[v].push_back({u, w});
    }
    dijkstra(g, 0);
    for(int i = 0; i < N; i++) {
        vector<int> path = buildPath(g, i);
        for(int j = 0; j < (int)path.size(); j++) {
            cout << path[j];
            if(j < (int)path.size() - 1) cout << " ";
        }
        cout << "\nTotal cost is " << g.distance[i] << endl;
    }
    return 0;
}
