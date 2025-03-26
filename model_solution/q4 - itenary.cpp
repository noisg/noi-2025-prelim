#define MAXN 300'000

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m, seq[2*MAXN+5], depth[MAXN+5], parent[MAXN+5], freq[MAXN+5];
bool vis[MAXN+5], itinerary_from[MAXN+5];
vector<int> adj[MAXN+5];

void input() {
    cin >> n >> m;

    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= m; i++) {
        cin >> seq[i];
    }
}

void lcaInitDFS(int v, int d, int p) {
    depth[v] = d;
    parent[v] = p;

    for (int u : adj[v]) {
        if (u != p) {
            lcaInitDFS(u, d + 1, v);
        }
    }
}

void lcaInit() {
    lcaInitDFS(1, 0, 1);
}

vector<int> getVerticesAlongPath(int u, int v) {
    vector<int> half_u, half_v;

    while (depth[u] > depth[v]) {
        half_u.push_back(u);
        u = parent[u];
    }

    while (depth[v] > depth[u]) {
        half_v.push_back(v);
        v = parent[v];
    }

    while (u != v) {
        half_u.push_back(u);
        u = parent[u];
        half_v.push_back(v);
        v = parent[v];
    }

    half_u.push_back(u);
    reverse(half_v.begin(), half_v.end());

    for (int w : half_v) {
        half_u.push_back(w);
    }

    return half_u;
}

bool markPaths() {
    for (int i = 1; i <= n; i++) {
        freq[i] = 0;
        vis[i] = false;
    }

    for (int i = 1; i < m; i++) {
        vector<int> path = getVerticesAlongPath(seq[i], seq[i+1]);

        for (int j = 0; j < path.size() - 1; j++) {
            int u = path[j];
            int v = path[j+1];
            int edge_index = depth[u] > depth[v] ? u : v;
            freq[edge_index]++;
            if (freq[edge_index] > 2) return false;
        }

        for (int j = 0; j < path.size(); j++) {
            vis[path[j]] = true;
        }
    }

    return true;
}

void fillItineraryDFS(int v) {
    itinerary_from[v] = true;
    vis[v] = true;

    for (int u : adj[v]) {
        if (vis[u]) continue;
        fillItineraryDFS(u);
    }
}

void fillItinerary() {
    for (int i = 1; i <= n; i++) {
        itinerary_from[i] = false;
    }

    if (!markPaths()) return;

    vector<int> path = getVerticesAlongPath(seq[1], seq[m]);
    for (int v : path) {
        fillItineraryDFS(v);
    }
}

void output() {
    for (int i = 1; i <= n; i++) {
        cout << (itinerary_from[i] ? 1 : 0) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    input();
    lcaInit();
    fillItinerary();
    output();

    return 0;
}