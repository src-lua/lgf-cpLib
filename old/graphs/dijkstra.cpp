// Time Complexity: O((V + E) * log(V))
void dijkstra(vector<vector<pair<int, int>>>& adj, vector<int>& dist, int s) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s});
    dist[s] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto e: adj[u]) {
            int v = e.first;
            int w = e.second;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}