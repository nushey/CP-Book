#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define vll vector<ll>

struct Edge {
    ll w;
    ll xyzA;
    ll xyzB;
    Edge() {w = xyzA =  xyzB = 0;}
    Edge(ll wx, ll xyzAx, ll xyzBx) { w = wx, xyzA = xyzAx, xyzB = xyzBx;}
    bool operator<(const Edge& other) const { return w < other.w; }
};

#define pll pair<ll,ll>
#define ve vector<Edge>
#define ALL(x) begin(x),end(x)
#define vi vector<int>
#define vll vector<pll>

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

ll tunnelCost(int x1, int y1, int z1, int x2, int y2, int z2){
    return min({abs(x1-x2), abs(y1-y2), abs(z1-z2)});
}

int main(){

    ios::sync_with_stdio(0);
    cout.tie(0);cin.tie(0);
    int n;
    cin >> n;
    ve EL;
    vll vx, vy, vz;
    for(int i = 0; i < n; i++){
        ll x,y,z;
        cin >> x >> y >> z;
        vx.emplace_back(x,i);
        vy.emplace_back(y,i);
        vz.emplace_back(z,i);
    }
    sort(ALL(vx));
    sort(ALL(vy));
    sort(ALL(vz));
    for(int i = 0; i < n-1; i++){
        EL.emplace_back(abs(vx[i].first - vx[i+1].first), vx[i].second, vx[i+1].second);
        EL.emplace_back(abs(vy[i].first - vy[i+1].first), vy[i].second, vy[i+1].second);
        EL.emplace_back(abs(vz[i].first - vz[i+1].first), vz[i].second, vz[i+1].second);
    }

    sort(ALL(EL));
    ll mst_cost = 0;
    UFDS UF(n);
    for(auto &[w, x, y] : EL){
        if(UF.isSameSet(x,y)){
            continue;
        };
        mst_cost += w;
        UF.unionSet(x,y);
    }
    cout << mst_cost;
    cout << "\n";


    return 0;
}




