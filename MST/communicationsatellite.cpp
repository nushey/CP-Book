#include <bits/stdc++.h>

using namespace std;

#define ALL(x) begin(x),end(x)

#define pdi pair<double, int>
#define coord pair<double,double>
#define vi vector<int>
vector<coord> coords;
vi radius;
vector<vector<pdi>> AL;
vi taken;          
priority_queue<pdi, vector<pdi>, greater<pdi>> pq; 

void process(int u) {
    taken[u] = 1;
    for(auto &[d, v] : AL[u]){
        if(!taken[v]){
            pq.emplace(d,v);
        }
    }
}

double dist(double x1, double y1, double x2, double y2, int r1, int r2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) - r1 - r2;
}

int main(){

    ios::sync_with_stdio(0);
    cout.tie(0);cin.tie(0);

    int n;
    cin >> n;
    cout << fixed << setprecision(6);
    coords.resize(n);
    taken.assign(n,0);
    radius.assign(n,0);
    AL.assign(n, vector<pdi>());
    for(int i = 0; i < n; i++){
        cin >> coords[i].first >> coords[i].second;
        cin >> radius[i];
    }
    for(int i = 0; i < n; i++){
        for(int j =  i+1; j < n; j++){
            double d = dist(coords[i].first, coords[i].second, coords[j].first, coords[j].second, radius[i], radius[j]);
            AL[i].emplace_back(d,j);
            AL[j].emplace_back(d,i);
        }
    }
    process(0);
    double mst_cost = 0.0, num_taken = 0;
    while (!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();
        if (taken[u]) continue;
        mst_cost += w;
        process(u);
        ++num_taken;
        if(num_taken == n-1) break;
    }
    cout << mst_cost << "\n";
    return 0;
}