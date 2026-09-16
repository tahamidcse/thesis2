#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int n;
vector<vector<int>> capacity;
vector<vector<int>> adj;

// DFS to find an augmenting path from s to t
int dfs(int cur, int t, int flow, vector<int>& parent, vector<bool>& visited) {
    if (cur == t)
        return flow;

    visited[cur] = true;

    for (int next : adj[cur]) {
        if (!visited[next] && capacity[cur][next] > 0) {
            parent[next] = cur;
            int new_flow = min(flow, capacity[cur][next]);
            int result = dfs(next, t, new_flow, parent, visited);
            if (result > 0)
                return result;
        }
    }

    return 0;
}

// Wrapper to find one augmenting path
int find_path(int s, int t, vector<int>& parent) {
    vector<bool> visited(n, false);
    parent[s] = -1;
    return dfs(s, t, INF, parent, visited);
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while ((new_flow = find_path(s, t, parent)) > 0) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> n >> m;

    capacity.assign(n, vector<int>(n, 0));
    adj.assign(n, vector<int>());

    for (int i = 0; i < m; i++) {
        int u, v, cap;
        cin >> u >> v >> cap;
        // If multiple edges between u and v, add capacities
        if (capacity[u][v] == 0 && capacity[v][u] == 0) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        capacity[u][v] += cap;
    }

    int s, t;
    cin >> s >> t;

    cout << "Max flow from " << s << " to " << t << " = " 
         << maxflow(s, t) << "\n";

    return 0;
}
