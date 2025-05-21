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

class SegTree{
    private:
        int n;
        vec<ll> A, st, lazy;
        int l(int p) { return p << 1;}
        int r(int p) { return (p << 1)+1;}
        ll conquer(ll a, ll b){
            if(a == -1) return b;
            if(b == -1) return a;
            return a+b;
        }
        void build(int p, int L, int R){
            if(L == R) st[p] = A[L];
            else{
                int m = L + (R-L)/2;
                build(l(p), L, m);
                build(r(p), m+1, R);
                // st[p] = conquer(st[l(p)], st[r(p)]);
            }
        }
        void propagate(int p,int L,int R){
            if(lazy[p] != 0){
                st[p] += lazy[p];               
                if(L != R){
                    lazy[l(p)] += lazy[p];
                    lazy[r(p)] += lazy[p];
                }
                lazy[p] = 0;
            }
        }
        ll query(int p, int L, int R, int i, int j){
            propagate(p, L, R);
            if(L > j || R < i) return -1;
            if(L >= i && R <= j) return st[p];
            int m = L + (R-L)/2;
            return conquer(query(l(p), L, m, i, j),query(r(p), m+1, R, i,j));
        }
        void update(int p, int L, int R, int i, int j, int v){
            propagate(p, L, R);
            if(L > j || R < i) return;
            if(L >= i && R <= j){
                lazy[p] += v;
                propagate(p, L, R);
                return;
            }
            int m = L + (R-L)/2;
            update(l(p), L, m, i, j, v);
            update(r(p), m+1, R, i, j, v);
            // st[p] = conquer(st[l(p)],st[r(p)]);
        }
    public:
        SegTree(int sz) : n(sz), st(4*n), lazy(4*n, 0) {}
        SegTree(const vec<ll> &init) : SegTree((int) init.size()){
            A = init;
            build(1, 0, n-1);
        }
        void update(int i, int j, int val) {update(1, 0, n-1, i, j, val);}
        ll query(int i, int j) {return query(1, 0, n-1, i, j) ;}
};

void solve()
{
    int n, q;
    cin >> n >> q;
    vec<ll> arr(n);
    for(auto &x : arr) cin >> x;
    SegTree st(arr);
    L(k, 0, q){
        int t;
        cin >> t;
        if(t == 1){
            int i,j,u;
            cin >> i >> j >> u;
            st.update(i-1, j-1, u);
        }
        else{
            int idx;
            cin >> idx;
            cout << st.query(idx-1,idx-1) << "\n";
        }
    }
}


int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int TT = 1;
    while (TT--)
    {
        solve();
    }
}