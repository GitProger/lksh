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
    freopen("condense2.in", "r", stdin);
    freopen("condense2.out", "w", stdout);
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
        if (comp[u] == 0)
            dfs(u, c);
}

inline void solve() {
    int n, m; cin >> n >> m;
    g.resize(n); gr.resize(n); 
    used.resize(n); comp.resize(n);
    
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
    
    int color = 1;
    for (int v : ord) {
        if (comp[v] == 0) {
            dfs(v, color);
            color++;
        }
    }

    set<prii> ans;
    for (auto e : edges) {
        if (comp[e.first] != comp[e.second])
            ans.insert({comp[e.first], comp[e.second]});
    }

    cout << len(ans) << $;
}
/*
4 4
2 1
3 2
2 3
4 3


3 4
1 2
2 3
3 2
1 3

*/

