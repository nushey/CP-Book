#include <bits/stdc++.h>
using namespace std;
#define L(i, j, n) for (int i = (j); i < (int)n; i++)
#define LI(i, j, n) for (int i = (j); i <= (int)n; i++)
#define R(i, j, n) for (int i = (j); i > (int)n; i--)
#define RI(i, j, n) for (int i = (j); i >= (int)n; i--)
#define SZ(x) int((x).size())
#define ALL(x) begin(x), end(x)
#define IS_IN(x, v) ((x).find(v) != (x).end())
#define vec vector
#define pb push_back

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pil = pair<int, ll>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

const int MOD = (int)1e9 + 7;
const int oo = (int)1e9;

vec<vec<char>> g;
vec<vec<int>> dist;

vec<int> dx = {1, -1, 0, 0};
vec<int> dy = {0, 0, 1, -1};

void escape(pii start, int n, int m)
{
    int i = start.first;
    int j = start.second;
    queue<pii> q;
    dist[i][j] = 0;
    q.push({i, j});
    while (!q.empty())
    {
        pii node = q.front();
        q.pop();
        int c = dist[node.first][node.second];
        L(k, 0, 4)
        {
            int x = node.first + dx[k];
            int y = node.second + dy[k];
            int newC = c + 1;
            if ((x >= 0 && x < n && y >= 0 && y < m && g[x][y] != '#') && (dist[x][y] > newC || dist[x][y] == -1))
            {
                dist[x][y] = newC;
                if (x == n - 1 || y == m - 1 || x == 0 || y == 0)
                {
                    cout << dist[x][y] + 1 << endl;
                    return;
                }
                q.push({x, y});
            }
        }
    }
    cout << "IMPOSSIBLE" << endl;
}

void bfs(vec<pii> &fire, int n, int m)
{
    queue<pii> q;
    for (auto &[x, y] : fire)
    {
        q.push({x, y});
        dist[x][y] = 0;
    }

    while (!q.empty())
    {
        pii node = q.front();
        q.pop();
        int c = dist[node.first][node.second];
        L(i, 0, 4)
        {
            int x = node.first + dx[i];
            int y = node.second + dy[i];
            int newC = c + 1;
            if ((x >= 0 && x < n && y >= 0 && y < m && g[x][y] != '#') && (dist[x][y] > newC || dist[x][y] == -1))
            {
                dist[x][y] = newC;
                q.push({x, y});
            }
        }
    }
}

void solve()
{
    int m, n;
    cin >> m >> n;
    vec<int> out;
    g.assign(n, vec<char>(m));
    dist.assign(n, vec<int>(m, -1));
    vec<pii> fire;
    pii start;
    L(i, 0, n)
    {
        L(j, 0, m)
        {
            cin >> g[i][j];
            if (g[i][j] == '*')
                fire.pb({i, j});
            else if (g[i][j] == '@')
                start = {i, j};
        }
    }
    if (start.first == n - 1 || start.first == 0 || start.second == m - 1 || start.second == 0)
        cout << 1 << endl;
    else
    {
        bfs(fire, n, m);
        escape(start, n, m);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin.tie(0);
    int TC;
    cin >> TC;
    while (TC--)
    {
        solve();
    }
    return 0;
}