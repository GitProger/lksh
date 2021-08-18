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
  //  freopen("pairs.in", "r", stdin);
    //freopen("pairs.out", "w", stdout);

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
int gtime = 1;

bool dfs(int v) {
    used[v] = gtime;
    for (int u : g[v]) 
        if (par[u] == -1) {
            par[u] = v;
            return true;
        }
    for (int u : g[v])
        if (used[par[u]] < gtime && dfs(par[u])) {
            par[u] = v;
            return true;
        }
    return false;
}

inline void solve() {
    int n, m; cin >> n >> m;
    g = graph(n + m);
    used = veci(n + m);
    par = veci(n + m, -1);
    for (int i = 0; i < n; i++) {
        for (;;) {
            int x; cin >> x; x--;
            if (x == -1) break;
            
            g[i].psh(n + x);
            g[n + x].psh(i);
        }
    }

    int ans = 0, pa = -1;
    while (pa != ans) {
        pa = ans;
        for (int v = 0; v < n; v++) {
            if (par[v] == -1 && dfs(v)) {
                ans++;
            }
        }
        gtime++;
    }

    cout << ans << $;
    for (int v = n; v < n + m; v++) {
        if (par[v] != -1) {
            cout << par[v] % n + 1 << " " << v % n + 1 << $;
        }
    }

}
/*
2 2
1 2 0
2 0

*/
