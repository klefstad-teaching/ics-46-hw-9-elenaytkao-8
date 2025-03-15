#include "dijkstras.h"
#include <algorithm>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    int n = G.numVertices;
    vector<int> dist(n, INF);
    dist[source] = 0;
    previous[source] = -1;

    using Pair = pair<int,int>;
    priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
    pq.push({0, source});

    vector<bool> visited(n, false);
    while(!pq.empty()) {
        auto [curDist, u] = pq.top();
        pq.pop();
        if (visited[u]) {
            continue;
        }
        visited[u] = true;
        for (auto &e : G[u]) {
            int v = e.dst;
            int w = e.weight;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                previous[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

vector<int> extract_shortest_path(const vector<int>& distances,
                                  const vector<int>& previous,
                                  int destination)
{
    vector<int> path;
    int cur = destination;
    while (cur != -1) {
        path.push_back(cur);
        cur = previous[cur];
    }
    reverse(path.begin(), path.end());
    return path;
}

// Prints the path plus its total cost.
void print_path(const vector<int>& path, int total)
{
    for (int i = 0; i < (int)path.size(); i++) {
        cout << path[i];
        if (i < (int)path.size() - 1) cout << " ";
    }
    cout << "\nTotal cost is " << total << endl;
}
