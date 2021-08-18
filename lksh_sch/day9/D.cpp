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


class debug final : public exception {
    const char *m = 0;
    public:
        debug(const char *m): m(m) {}
        const char *what() const noexcept { return m; }
};

inline void solve();
signed main() {
//*
    freopen("floyd.in", "r", stdin);
    freopen("floyd.out", "w", stdout);
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

vec<veci> d, p;

veci getPath(int i, int j) {
    if (p[i][j] == -1) {
        veci res;
        res.push_back(i);
        if (i != j) res.push_back(j);
        return res;
    }

    int k = p[i][j];
    veci v1 = getPath(i, k);
    veci v2 = getPath(k, j);

    for (int x : v2) {
        if (v1.empty() || v1.back() != x)
            v1.push_back(x);
    }
    return v1;
}

map<prii, int> edges;
inline void solve() {
    int n, m, k; cin >> n >> m >> k;
    d = vec<veci>(n, veci(n, INF));
    p = vec<veci>(n, veci(n, -1));
    for (int i = 0; i < m; i++) {
        int b, e, w; cin >> b >> e >> w;
        --b; --e; w *= -1;
        if (w < d[b][e]) {
            d[b][e] = w;
            edges[{b, e}] = i + 1;
        }
    }

    veci a(k); cin >> a;
    for (int &e : a) e--;

    for (int x = 0; x < n; x++)
        for (int v = 0; v < n; v++)
            for (int u = 0; u < n; u++)
                if (d[v][x] != INF && d[x][u] != INF && d[v][u] > d[v][x] + d[x][u]) {
                    d[v][u] = d[v][x] + d[x][u];
                    p[v][u] = x;
                }

    veci dists1;
    for (int i = 1; i < k; i++) dists1.push_back(d[a[i - 1]][a[i]]);

    for (int x = 0; x < n; x++)
        for (int v = 0; v < n; v++)
            for (int u = 0; u < n; u++)
                if (d[v][x] < INF && d[x][u] < INF && d[v][u] > d[v][x] + d[x][u]) {
                    d[v][u] = d[v][x] + d[x][u];
                }

    veci dists2;
    for (int i = 1; i < k; i++) dists2.push_back(d[a[i - 1]][a[i]]);


    if (dists1 != dists2) {
        cout << "infinitely kind\n";
        return;
	}

    veci ans;
    for (int i = 1; i < k; i++) {
        veci way = getPath(a[i - 1], a[i]);
        for (int j = 1; j < len(way); j++) {
            ans.push_back(edges[{way[j - 1], way[j]}]);
        }
    }
    
    cout << len(ans) << $ << ans << $;
}
/*

4 8 5
1 2 -2
2 3 3
3 4 -5
4 1 3
1 3 2
3 1 -2
3 2 -3
2 4 -10
1 3 1 2 4

*/

