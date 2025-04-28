#include <bits/stdc++.h>

using namespace std;

#define ll long long

struct Edge {
    ll w;
    int u,v;
    Edge() {w = u = v = 0;}
    Edge(ll wx, int ux, int vx) { w = wx, u = ux, v = vx;}
    bool operator<(const Edge& other) const { return w < other.w; }
};

#define vi vector<int>
#define vll vector<ll>

class UFDS{
    private:
        vi p, rank, setSize;
        int numSets;
    public:
        UFDS(int N){
            p.assign(N,0); for(int i = 0; i < N; i++) p[i] = i;
            rank.assign(N,0);
            setSize.assign(N, 1);
            numSets = N;
        }
        int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i]));}
        bool isSameSet(int i, int j) { return findSet(i) == findSet(j);}
        int numDisjointSets() { return numSets;}
        int sizeOfSet(int i) { return setSize[findSet(i)];}
        void unionSet(int i, int j){
            if(isSameSet(i,j)) return;
            int x = findSet(i), y = findSet(j);
            if(rank[x] > rank[y]) swap(x,y);
            p[x] = y;
            if(rank[x] == rank[y]) ++rank[y];
            setSize[y] += setSize[x];
            --numSets;
        }
};

int main(){

    bool fst = 1;
    while(true){
        int n,m;
        cin >> n >> m;
        if(n == 0 && m == 0) break;
        vector<Edge> EL(m);
        ll original = 0;
        for(int i = 0; i < m; i++){
            int u,v; 
            ll w;
            cin >> u >> v >> w;
            original += w;
            EL[i] = Edge(w,u,v);
        }
        sort(EL.begin(), EL.end(), [](const Edge &lhs, const Edge &rhs){
            return lhs.w < rhs.w;
        });
        int num_taken = 0;
        ll mst_cost = 0;
        UFDS UF(n);
        for(auto &[w, u, v] : EL){
            if(UF.isSameSet(u,v)){
                continue;
            };
            mst_cost += w;
            UF.unionSet(u,v);
            ++num_taken;
        }
        cout << original - mst_cost;
        cout << "\n";
    }
    return 0;

}