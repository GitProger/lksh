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
    int n, m; cin >> n >> m;
    g.resize(n); up.resize(n); h.resize(n);
    for (int i = 0; i < n; i++) up[i].resize(l + 1);

    for (int v = 1; v < n; v++) {
        int p; cin >> p;
        g[p].psh(v);
        h[v] = h[p] + 1;
        up[v][0] = p;
        for (int i = 1; i <= l; i++)
            up[v][i] = up[up[v][i - 1]][i - 1];
    }

    int a1, a2; cin >> a1 >> a2;
    int x, y, z; cin >> x >> y >> z;
    int ans = 0, v = 0;
    while (m--) {
        v = lca((a1 + v) % n, a2);
        ans += v;

        int a1_new = (a1 * x + a2 * y + z) % n; // ..., a1, a2, a1_new, a2_new, ...
        int a2_new = (a2 * x + a1_new * y + z) % n;
        a1 = a1_new, a2 = a2_new;
    }
    cout << ans << $;
    // 10^7 * log2(10^5) = 166 * 10^6
    // 
}
/*

3 2
0 1
2 1
1 1 0
> 2

1 2
0 0
1 1 1
> 0

*/
