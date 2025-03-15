#include <vector>
#include <limits>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    int vertex;
    int weight;
};

struct Graph {
    vector<vector<Node>> adjacencyList;
    vector<int> distance;
    vector<int> previous;
    vector<bool> visited;
};

void dijkstra(Graph &g, int source) {
    int n = g.adjacencyList.size();
    g.distance.assign(n, numeric_limits<int>::max());
    g.previous.assign(n, -1);
    g.visited.assign(n, false);
    auto cmp = [](const Node &a, const Node &b){ return a.weight > b.weight; };
    priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);
    g.distance[source] = 0;
    pq.push({source, 0});
    while(!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        int u = current.vertex;
        if(g.visited[u]) continue;
        g.visited[u] = true;
        for(const auto &neighbor : g.adjacencyList[u]) {
            int v = neighbor.vertex;
            int w = neighbor.weight;
            if(!g.visited[v] && g.distance[u] + w < g.distance[v]) {
                g.distance[v] = g.distance[u] + w;
                g.previous[v] = u;
                pq.push({v, g.distance[v]});
            }
        }
    }
}

vector<int> buildPath(const Graph &g, int target) {
    vector<int> path;
    int cur = target;
    while(cur != -1) {
        path.push_back(cur);
        cur = g.previous[cur];
    }
    reverse(path.begin(), path.end());
    return path;
}
