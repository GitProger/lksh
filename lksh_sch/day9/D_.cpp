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
/*
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
struct edge {
    int a = 0, b = 0, w = 0, i = 0;
    edge(int a, int b, int w, int i): a(a), b(b), w(w), i(i) {}
};

veci getPath(int i, int j) {
//    assert(0 <= i && 0 <= j && i != j && j != p[i][j]);
    if (p[i][j] == -1) {
        veci res;
        res.push_back(i);
        if (i != j) res.push_back(j);
        return res;
    }

    cerr << i << " " << j << $;

    int k = p[i][j];
    veci v1 = getPath(i, k);
    veci v2 = getPath(k, j);

    for (int x : v2) {
        if (v1.empty() || v1.back() != x)
            v1.push_back(x);
    }
    return v1;
}

inline void solve() {
    int n, m, k; cin >> n >> m >> k;
    d = vec<veci>(n, veci(n));
    p = vec<veci>(n, veci(n, -1));
    vec<edge> edges;
    for (int i = 0; i < m; i++) {
        int b, e, w; cin >> b >> e >> w;
        --b; --e; w *= -1;
        edges.push_back(edge(b, e, w, i));
        d[b][e] = w;
    }
    veci a(k); cin >> a;

    for (int x = 0; x < n; x++)
        for (int v = 0; v < n; v++)
            for (int u = 0; u < n; u++)
                if (d[v][u] > d[v][x] + d[x][u]) {
                    d[v][u] = d[v][x] + d[x][u];
                    p[v][u] = x;
                }

    for (auto e : d) cerr << e << $;
    cerr << $;
    for (auto e : p) cerr << e << $;
    
    for (;;) {
        int a, b; cin >> a >> b; --a; --b;
        cout << getPath(a, b) << $;
    }


    auto toInd = [=] (veci x) {
        veci ans;
        for (int i = 1; i < len(x); i++) {
            for (auto e : edges)
                if (e.a == x[i - 1] && e.b == x[i])
                    ans.psh(e.i);
        }
        return ans;
    };

    int neg = false;
    for (int i = 0; i < n; i++)
	    for (int j = 0; j < n; j++)
		    for (int t = 0; t < n; t++)
			    if (d[i][t] < INF && d[t][j] < INF && d[t][t] < 0) {
				    neg = true;
                    goto lbl;
                }
                        
    lbl: if (neg) {
        cout << "infinitely kind\n";
      //  return;
    }

    veci ans;
    for (int i = 1; i < k; i++) {
        int b = a[i - 1], e = a[i];
        for (int idx : toInd(getPath(b, e)))
            ans.psh(idx);
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

