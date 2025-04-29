#include <bits/stdc++.h>
using namespace std;

#define LOCAL
#define L(i, j, n) for (int i = (j); i < (int)n; i ++)
#define LI(i, j, n) for (int i = (j); i <= (int)n; i ++)
#define R(i, j, n) for (int i = (j); i > (int)n; i --)
#define RI(i, j, n) for (int i = (j); i >= (int)n; i --)
#define SZ(x) int((x).size())
#define ALL(x) begin(x),end(x)
#define IS_IN(x, v) ((x).find(v) != (x).end())
#define vec vector
#define pb push_back

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pil = pair<int, ll>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;


const int N = (int)2e5+5;
const int MOD = (int)1e9 + 7;
const int oo = (int)1e9;

struct Edge {
    ll w;
    ll xyzA;
    ll xyzB;
    Edge() {w = xyzA =  xyzB = 0;}
    Edge(ll wx, ll xyzAx, ll xyzBx) { w = wx, xyzA = xyzAx, xyzB = xyzBx;}
    bool operator<(const Edge& other) const { return w < other.w; }
};

class UFDS{
    private:
        vec<int> p, rank, setSize;
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

int dfs(int u, int v, vec<vec<pii>> &mst, vec<bool> &visited, int maxEdge) {
    if (u == v) return maxEdge; 
    visited[u] = true;
    for (auto &[neighbor, weight] : mst[u]) {
        if (!visited[neighbor]) {
            int result = dfs(neighbor, v, mst, visited, max(maxEdge, weight));
            if (result != -1) return result; 
        }
    }

    return -1; 
}


int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int tt = 1;
    while(true){
        int c,s,q;
        cin >> c >> s >> q;
        if(c == 0 && s == 0 && q == 0) break;
        vec<Edge> EL(s);
        vec<vec<pii>> mst(c); 
        for(int i = 0; i < s; i++){
            int u,v,d;
            cin >> u >> v >> d;
            u--;v--;
            EL[i] = Edge(d, u , v);
        }
        sort(ALL(EL));
        UFDS UF(c);
        for(auto &[w, x, y] : EL){
            if(UF.isSameSet(x,y)){
                continue;
            };
            UF.unionSet(x,y);
            mst[x].push_back({y, w});
            mst[y].push_back({x, w});
        }
        if(tt != 1) cout << "\n" << "\n";
        cout << "Case #" << tt << "\n";
        for(int i = 0; i < q; i++){
            int u,v;
            cin >> u >> v;
            u--;v--;
            vec<bool> visited(c, false);
            int cost = dfs(u, v, mst, visited, 0);
            if(cost != -1) cout << cost;
            else cout << "no path";
            if(i != q-1) cout << "\n";
        }
        tt++;
    }
    cout << "\n";
    
    return 0;

}