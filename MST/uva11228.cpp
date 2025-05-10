#include <bits/stdc++.h>
using namespace std;

struct Edge {
    double w; int u,v;
    Edge(double wx, int ux, int vx) { w = wx, u = ux, v = vx;}
    bool operator<(const Edge& other) const { return w < other.w; }
};

#define vi vector<int>
#define ii pair<int,int>
#define dd pair<double,double>
#define ALL(x) begin(x),end(x)
#define vii vector<ii>

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

double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main(){
    int t;
    cin >> t;
    for(int i = 1; i <= t; i++){
        int n,r; cin >> n >> r;
        vector<dd> coords(n);
        vector<Edge> AL;
        UFDS dsu(n);
        for(int i = 0; i < n; i++){
            cin >> coords[i].first >> coords[i].second;
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n && i!=j; j++){
                double d = dist(coords[i].first, coords[i].second, coords[j].first, coords[j].second);
                AL.push_back(Edge(d, i, j));
                if(d <= r) dsu.unionSet(i,j);
            }
        }
        sort(ALL(AL));
        double road = 0, rail = 0; 
        UFDS mst_dsu(n);
        int num_taken = 0, states = dsu.numDisjointSets();

        for (auto &[w, u, v] : AL) {
            if (mst_dsu.isSameSet(u, v)) {
                continue;
            }
            if (w <= r) {
                road += w;
            } else {
                rail += w;
            }
            mst_dsu.unionSet(u, v);
            ++num_taken;
        }

        cout << "Case #" << i << ": " << states << " " << round(road) << " " << round(rail) << "\n";

    }
    
    return 0;
}