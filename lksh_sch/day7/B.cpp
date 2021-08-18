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
#define pshp(a, b) push_back({(a),(b)})
#define LBL(a) cerr<<"LABEL #"<<a<<"\n"

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

const int MOD = 1'000'000'007;
inline void solve();
signed main() {
//    freopen("pairs.in", "r", stdin);
  //  freopen("pairs.out", "w", stdout);

    solve();
    cout.flush();
    cerr << "\nTime: " << setprecision(2) <<
        int(1000 * (double)clock() / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

template <class T> T rmin(T &a, const T &b) { return (a = min(a, b)); }
template <class T> T rmax(T &a, const T &b) { return (a = max(a, b)); }
template <class T> T reql(T &a, const T &b) { return (a = b); }

graph g;
veci used;
veci par;

bool dfs(int v) {
    if (used[v]) return false;
    used[v] = 1;
    for (int u : g[v])
        if (par[u] == -1 || dfs(par[u])) {
            par[u] = v;
            return true;
        }
    return false;
}

void dfs_f(const graph &gr, int v) {
    used[v] = 1;
    for (int u : gr[v])
        if (!used[u]) dfs_f(gr, u);
}

prii rev(const prii &x) { return {x.second, x.first}; }

template <class T> void remove(set<T> &s, const T &x) {
    auto it = s.find(x);
    if (it != s.end()) s.erase(it);
}

inline void solve() {
    int n, m; cin >> n >> m;
    g = graph(n + m);
    used = veci(n + m);
    par = veci(n + m, -1);
    set<prii> edges;
    
    int a, b;
    while (cin >> a >> b) {
        --a; --b;
        g[a].psh(b);
        edges.insert({a, b});
    }

    for (int v = 0; v < n; v++) {
        dfs(v);
        used.assign(n + m, 0);
    }

    graph ans(n + m);
    veci free(n + m, 1);
    for (int v = 0; v < m; v++)
        if (par[v] != -1) {
            prii c = {par[v], v};
            
            ans[c.second + n].psh(c.first);
            free[v + n] = free[par[v]] = 0;
            
            remove(edges, c); //remove(edges, rev(c));
        }

    for (prii x : edges)
        ans[x.first].psh(x.second + n);
    
    for (int v = 0; v < n; v++)
        if (free[v])
            dfs_f(ans, v);

    veci left, right;
    for (int v = 0; v < n + m; v++) {
        if (v < n && !used[v]) left.psh(v + 1); // L-
        if (v >= n && used[v]) right.psh(v - n + 1); // R+
    }

    cout << len(left) + len(right) << $ << len(left) << " " << len(right) << $;
    cout << left << $ << right << $;

}
/*
6 6
1 1
2 5
3 4
4 4
5 2
5 3
6 1
6 6


*/
