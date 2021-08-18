#include <bits/stdc++.h>
using namespace std;
#define int ll
typedef long long ll;
typedef long double ld;
typedef long long var;
typedef pair<int, int>prii;
typedef pair<ll, ll>prll;
typedef vector<int>veci;
typedef vector<ll>vecl;
typedef vector<veci> graph;
typedef map<int, int> mapii;
typedef set<int> seti;
typedef bitset<64> bits;
typedef string str;
#define vec vector
#define fir first
#define sec second
#define $ '\n'
#define $$ endl
#define MAX LONG_LONG_MAX
#define INF LONG_LONG_MAX
#define MIN LONG_LONG_MIN
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define len(o) ((int)o.size())
#define psh push_back
template <typename T> istream& operator >> (istream &in, vector<T> &v) { 
    for (T &t : v) in >> t;
    return in;
}
template <typename T> ostream& operator << (ostream &out, const vector<T> &v) {
    for (const T &t : v) out << t << ' ';
    return out;
}
template <typename T> ostream& operator << (ostream &out, const set<T> &v) {
    for (const T &t : v) out << t << ' ';
    return out;
}


inline void solve();
signed main() {
//*
    freopen("points.in", "r", stdin);
    freopen("points.out", "w", stdout);
//*/
    int t = 1;
   // cin >> t; 
    while (t--) {
        solve();
    }
    cout.flush();
    cerr << "\nTime: " << setprecision(2) <<
        int(1000 * (double)clock() / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

template <class T> T rmin(T &a, const T &b) { return (a = min(a, b)); }
template <class T> T rmax(T &a, const T &b) { return (a = max(a, b)); }
template <class T> T reql(T &a, const T &b) { return (a = b); }

int N = 20010;
graph g(N);
veci depth(N), up(N, INF), used(N);
vec<bool> is_airpoint(N);

veci deg(N);

void dfs(int v, int p = -1) {
    used[v] = true;
    for (int u : g[v])
        if (!used[u])
            depth[u] = depth[v] + 1;    
    int cnt = 0;
    for (int u : g[v]) {
        if (u == p) continue;
        if (!used[u]) {
            dfs(u, v);
            cnt++;
            deg[v] = max(deg[v], up[u]);
            up[v] = min(up[v], up[u]);
        } else
            up[v] = min(up[v], depth[u]);
    }
    if ((p != -1 && deg[v] >= depth[v] && cnt > 0) || (p == -1 && cnt > 1))
        is_airpoint[v] = true;
}

inline void solve() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        --u; --v;
        g[v].psh(u);
        g[u].psh(v);
    }
    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs(i);

    veci res;
    for (int i = 0; i < n; i++)
        if (is_airpoint[i]) res.psh(i + 1);
    cout << len(res) << $ << res << $;
}
/*

*/
