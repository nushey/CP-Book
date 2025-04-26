#include <bits/stdc++.h>
#include "./DS/UFDS.cpp"

struct Edge {
    int w,u,v;
    Edge(int wx, int ux, int vx) { w = wx, u = ux, v = vx;}
    bool operator<(const Edge& other) const { return w < other.w; }
};

int main(){
    int V,E; cin >> V >> E;
    vector<Edge> EL(E);
    for(int i = 0; i < E; i++){
        int u,v,w; cin >> u >> v >> w;
        EL[i] = Edge(w,u,v);
    }
    sort(EL.begin(), EL.end());
    int mst_cost = 0, num_taken = 0;
    UFDS UF(V);
    for(auto &[w, u, v] : EL){
        if(UF.isSameSet(u,v)) continue;
        mst_cost += w;
        UF.unionSet(u,v);
        ++num_taken;
        if(num_taken == V-1) break;
    }

    return 0;
}