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

const int MOD = 1'000'000'007;
inline void solve();
signed main() {
//* 
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
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


int N = 200010;
vec<veci> g(N);
veci depth(N), up(N, INF), used(N);
veci comps;

map<prii, int> lefts;
vec<prii> bridges;
void erase(int a, int b) {
    lefts[{a, b}]--;
    lefts[{b, a}]--;
}

void dfs(int v, int p = -1) {
    used[v] = 1;
    for (int u : g[v])
        if (!used[u])
            depth[u] = depth[v] + 1;    
    for (int u : g[v]) {
        if (u == p) continue;
        if (!used[u]) {
            dfs(u, v);
            up[v] = min(up[v], up[u]);
        } else
            up[v] = min(up[v], depth[u]);
    }
    if (up[v] >= depth[v] && p != -1) {
        erase(p, v);
        bridges.psh({p, v});
    }
}

void color(int v, int c) {
    used[v] = 1;
    comps[v] = c;
    for (int u : g[v]) {
        if (lefts[{v, u}] > 0 && !used[u])
            color(u, c);
    }
}

inline void solve() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        --u; --v;
        g[v].psh(u);
        g[u].psh(v);
        lefts[{u, v}]++;
        lefts[{v, u}]++;
    }
    for (int i = 0; i < n; i++) 
        if (!used[i])
            dfs(i);
    for (int i = 0; i < n; i++) used[i] = 0;

    int cur = 0;
    comps = veci(n);
    for (int i = 0; i < n; i++)
        if (!used[i]) {
            cur++;
            color(i, cur - 1);
        }
    veci comp_cnt(cur); // bridge count in each component
    veci comp_sz(cur);
    for (int i = 0; i < n; i++)
        comp_sz[comps[i]]++;
    for (prii e : bridges) {
        comp_cnt[comps[e.first]]++;
        comp_cnt[comps[e.second]]++;
    }
    int ans = 1;
    int k = 0;    
    for (int i = 0; i < cur; i++) {
        if (comp_cnt[i] == 1) {
            k++;
            ans *= comp_sz[i];
            ans %= MOD;
        }
    }
        
    cout << k << " " << ans << $;
}
