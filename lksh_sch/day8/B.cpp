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
graph g, up, mn;
veci h;

int lca(int a, int b) {
    int ans = INF;
    if (h[a] < h[b]) swap(a, b);
    for (int i = l; i >= 0; i--) 
        if ((1 << i) <= h[a] - h[b]) {
        //    cerr << ans << " <- " << mn[a][i] << " | " << a << " - " << a + (1 << i) << " !" << $;
            rmin(ans, mn[a][i]);
            a = up[a][i];
        }
    if (a == b) return ans;
    for (int i = l; i >= 0; i--)
        if (up[a][i] != up[b][i]) {
      //      cerr << ans << " <- " << mn[a][i] << " | " << a << " - " << a + (1 << i) << $;
        //    cerr << ans << " <- " << mn[b][i] << " | " << b << " - " << b + (1 << i) << $;
            rmin(ans, mn[a][i]);
            rmin(ans, mn[b][i]);
            a = up[a][i];
            b = up[b][i];
        }
    rmin(ans, mn[a][0]);
    rmin(ans, mn[b][0]);
 //   return up[a][0];
    return ans;
}

inline void solve() {
    int n; cin >> n;
    
    g.resize(n); up.resize(n); h.resize(n); mn.resize(n);
    for (int i = 0; i < n; i++) {
        up[i].resize(l + 1);
        mn[i].resize(l + 1);
    }

    for (int v = 1; v < n; v++) {
        int x, y; cin >> x >> y; --x;
        h[v] = h[x] + 1;
        up[v][0] = x;
        mn[v][0] = y;
    }

    
    for (int v = 0; v < n; v++)
        for (int i = 1; i <= l; i++) {
            up[v][i] = up[up[v][i - 1]][i - 1];
            mn[v][i] = min(
                mn[   v        ][i - 1],
                mn[up[v][i - 1]][i - 1]
            );
        }

   /* for (int v = 0; v < n; v++) {
        for (int i = 0; i < 3; i++) {
            cerr << mn[v][i] << " ";
        }
        cerr << $;
    }
    cerr << $;*/
    
    int m; cin >> m;
    while (m--) {
        int a, b; cin >> a >> b; --a; --b;
        cout << lca(a, b) << $;
    }
}
/*

5
1 2
1 3
2 5
3 2
2
2 3
4 5

*/
