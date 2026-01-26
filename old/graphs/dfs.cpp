// Time Complexity: O(V + E)
void dfs(vector<vector<int>>& adj, vector<bool>& visited, int v) {
    visited[v] = true;
    // pre-visited

    for (auto e: adj[v]) {
        if (!visited[e]) {
            dfs(adj, visited, e);
        }
    }

    // post-visited
}