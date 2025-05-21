#include <bits/stdc++.h>
using namespace std;

#define vec vector
class SegTree{
    private:
        int n;
        vec<int> A, st, lazy;
        int l(int p) { return p << 1;}
        int r(int p) { return (p << 1)+1;}
        int conquer(int a, int b){
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
                st[p] = conquer(st[l(p)], st[r(p)]);
            }
        }
        void propagate(int p, int L, int R){
            if(lazy[p] != -1){
                st[p] = lazy[p];
                if(L != R){
                    lazy[l(p)] = lazy[r(p)] = lazy[p];
                }
                lazy[p] = -1;
            }
        }
        int query(int p, int L, int R, int i, int j){
            propagate(p, L, R);
            if(L >= i && R <= j) return st[p];
            int m = L + (R-L)/2;
            return conquer(query(l(p), L, m, i, j),query(r(p), m+1, R, i,j));
        }
        void update(int p, int L, int R, int i, int j, int v){
            propagate(p, L, R);
            if(L >= i && R <= j){
                lazy[p] = v;
                propagate(p, L, R);
            }
            else{
                int m = L + (R-L)/2;
                update(l(p), L, m, i, j, v);
                update(r(p), m+1, R, i, j, v);
                st[p] = conquer(st[l(p)],st[r(p)]);
            }
        }
    public:
        SegTree(int sz) : n(sz), st(4*n), lazy(4*n, -1) {}
        SegTree(const vec<int> &init) : SegTree((int) init.size()){
            A = init;
            build(1, 0, n-1);
        }
        void update(int i, int j, int val) {update(1, 0, n-1, i, j, val);}
        int query(int i, int j) {return query(1, 0, n-1, i, j) ;}
};