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
template <typename T> istream& operator >> (istream &in, vector<T> &v) { 
    for (T &t : v) in >> t;
    return in;
}
template <typename T> ostream& operator << (ostream &out, const vector<T> &v) {
    for (const T &t : v) out << t << ' ';
    return out;
}


inline void solve();
signed main() {
//*
    freopen("firesafe.in", "r", stdin);
    freopen("firesafe.out", "w", stdout);
//*/
    solve();
    cout.flush();
    cerr << "\nTime: " << setprecision(2) <<
        int(1000 * (double)clock() / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}

inline void stress() {
}
////////////////////////////////////////////////////////////////////////////////

graph g, gr;
veci used, comp, ord;
int gtime;

void dfs_r(int v) {
    used[v] = 1;
    for (int u : g[v])
        if (!used[u])
            dfs_r(u);
    ord.push_back(v);
}

void dfs(int v, int c) {
    comp[v] = c;
    for (int u : gr[v])
        if (comp[u] == -1)
            dfs(u, c);
}

inline void solve() {
    int n, m; cin >> n >> m;
    g.resize(n); gr.resize(n); 
    used.resize(n); comp.resize(n, -1);
    
    vec<prii> edges;
    for (int i = 0; i < m; i++) {
        int b, e; cin >> b >> e; --b; --e;
        g[b].push_back(e);
        gr[e].push_back(b);
        edges.push_back({b, e});
    }
    for (int i = 0; i < n; i++)
        if (!used[i]) 
            dfs_r(i);
    reverse(all(ord));
    
    int color = 0; // component count
    for (int v : ord) {
        if (comp[v] == -1) {
            dfs(v, color);
            color++;
        }
    }

    veci house(color);
    for (int i = 0; i < n; i++)
        house[comp[i]] = i;

    veci edges_out(color);
    for (auto e : edges) {
        if (comp[e.first] != comp[e.second]) {
            edges_out[comp[e.first]]++;
        }
    }

    veci ans;
    for (int c = 0; c < color; c++) {
        if (edges_out[c] == 0) {
            ans.push_back(house[c] + 1);
        }
    }
    cout << len(ans) << $ << ans << $;

/*    cerr << comp << $;
    cerr << edges_out << $;
    cerr << house << $;*/

}
/*

5
7
1 2
2 3
3 1
2 1
2 3
3 4
2 5

*/

