#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii; 
vector<vector<pii>> AL;     
vector<int> taken;          
priority_queue<pii, vector<pii>, greater<pii>> pq; 

void process(int u) {
    taken[u] = 1;
    for (auto &[v, w] : AL[u]) {
        if (!taken[v]) {
            pq.emplace(w, v); 
        }
    }
}

int main() {
    int V, E; cin >> V >> E;
    AL.assign(V, vector<pii>());
    for (int i = 0; i < E; i++) {
        int u, v, w; cin >> u >> v >> w;
        AL[u].emplace_back(v, w);
        AL[v].emplace_back(u, w);
    }
    taken.assign(V, 0);
    process(0); 
    int mst_cost = 0, num_taken = 0;
    while (!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();
        if (taken[u]) continue;
        mst_cost += w;
        process(u);
        ++num_taken;
        if (num_taken == V - 1) break; 
    }

    cout << "MST cost: " << mst_cost << endl;
    return 0;
}