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
/*
    freopen("coloring.in", "r", stdin);
    freopen("coloring.out", "w", stdout);
//*/
    int t = 1;
    cin >> t; 
    while (t--) {
        solve();
    }
    cout.flush();
    cerr << "\nTime: " << setprecision(2) <<
        int(1000 * (double)clock() / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}

inline void stress() {
}
////////////////////////////////////////////////////////////////////////////////

template <class T> T rmin(T &a, const T &b) { return (a = min(a, b)); }
template <class T> T rmax(T &a, const T &b) { return (a = max(a, b)); }
template <class T> T reql(T &a, const T &b) { return (a = b); }
int sum(const veci &a) {
    int s = 0;
    for (int e : a) s += e;
    return s;
}

int n, m;
graph g;
veci used;
vec<seti> neighs;
veci colors;

void dfs(int v) {
    used[v] = 1;
    int col = 1;
    while (neighs[v].find(col) != neighs[v].end()) col++;
    colors[v] = col;
    for (int u : g[v])
        neighs[u].insert(colors[v]);
    
    for (int u : g[v]) {
        if (!used[u]) {
            dfs(u);
        }
    }
}


inline void solve() {
    int n, m; cin >> n >> m;
    g = graph(n);
    used = veci(n);
    neighs = vec<seti>(n);    
    colors = veci(n);

    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; --u; --v;
        g[v].psh(u); g[u].psh(v);
    }

    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs(i);
    seti t;
    for (int e : colors) t.insert(e);
    cout << len(t) << $ << colors << $;
    
//    for (int i = 0; i < n; i++) cout << neighs[i] << $;
}
/*
3
3 3
1 2
2 3
3 1
5 3
2 1
3 1
4 2
6 7
1 2
1 5
2 5
2 3
2 4
5 6
5 4

*/
