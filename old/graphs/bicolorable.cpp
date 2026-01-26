// Time Complexity: O(V + E)
bool bicolorable(vector<vector<int>>&adj, vector<bool>& visited, vector<bool>& color, int v) {
    visited[v] = true;

    for (auto e: adj[v]) {
        if (!visited[e]) {
            color[e] = !color[v];
            if (!bicolorable(adj, visited, color, e)) {
                return false;
            }
        } else if (color[e] == color[v]) {
            return false;
        }
    }

    return true;
}