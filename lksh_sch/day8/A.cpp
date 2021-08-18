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

int n, l = 30;
graph g, up;
veci h;

void dfs(int v, int p) {
	up[v][0] = p;
	for (int i = 1; i <= l; i++)
        up[v][i] = up[up[v][i - 1]][i - 1];
    for (int u : g[v])
        if (u != p) {
            h[u] = h[v] + 1;
            dfs(u, v);
        }
}

int lca(int a, int b) {
    if (h[a] < h[b]) swap(a, b);
    for (int i = l; i >= 0; i--) 
        if ((1 << i) <= h[a] - h[b])
            a = up[a][i];
    if (a == b) return a;
    for (int i = l; i >= 0; i--)
        if (up[a][i] != up[b][i]) {
            a = up[a][i];
            b = up[b][i];
        }
    return up[a][0];
}

inline void solve() {
    int n; cin >> n;
    veci a(n); cin >> a;
    
    int root = 0;
    g.resize(n);
    up.resize(n);
    h.resize(n);
    for (int i = 0; i < n; i++) {
        a[i]--;
        if (a[i] == -1)
            root = i; 
        else
            g[a[i]].psh(i);
    }

    for (int i = 0; i < n; i++) up[i].resize(l + 1);
    dfs(root, root);    
    
    int m; cin >> m;
    while (m--) {
        int a, b; cin >> a >> b; --a; --b;
        cout << (lca(a, b) == a) << $;
    }
}
/*
6
0 1 1 2 3 3
5
4 1
1 4
3 6
2 6
6 5

*/
