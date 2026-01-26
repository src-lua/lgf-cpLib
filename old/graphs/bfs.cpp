// Time Complexity: O(V + E)
void bfs(vector<vector<int>>& adj, vector<bool>& visited, int start) {
    queue<int> operation_order;

    visited[start] = true;
    operation_order.push(start);

    while (!operation_order.empty()) {
        auto top = operation_order.front();
        operation_order.pop();

        for (auto e : adj[top]) {
            if (!visited[e]) {
                visited[e] = true;
                operation_order.push(e);
            }
        }
    }
}