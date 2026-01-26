// Time Complexity: O(V + E)
void toposort(vector<vector<int>>& adj, stack<int>& topo, vector<bool>& visited, int v) {
    visited[v] = true;
    for (auto e: adj[v]) {
        if (!visited[e]) {
            toposort(adj, topo, visited, e);
        }
    }
    topo.push(v);
}

// Time Complexity: O(V + E)
void toposort(vector<vector<int>>& adj, vector<int>& indegree, int n) {
    queue<int> q; // Use a min heap for lexicographically smallest toposort
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        cout << v << " ";
        for (auto e: adj[v]) {
            indegree[e]--;
            if (indegree[e] == 0) {
                q.push(e);
            }
        }
    }
}