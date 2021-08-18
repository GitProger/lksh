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
    freopen("negcycle.in", "r", stdin);
    freopen("negcycle.out", "w", stdout);
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

graph g;
struct edge {
    int a = 0, b = 0, w = 0;
    edge(int a, int b, int c): a(a), b(b), w(c) {}
};


const int EMPTY_EDGE_ID = 100'000;

inline void solve() {
    int n; cin >> n;
    g.resize(n);
    vec<edge> edges;
    for (int i = 0; i < n; i++) {
        g[i].resize(n);
        cin >> g[i];
        for (int j = 0; j < len(g[i]); j++) {
            if (g[i][j] != EMPTY_EDGE_ID)
                edges.push_back(edge(i, j, g[i][j]));
        }
    }
    veci d(n), p(n, -1);
    int lst = -1;
    for (int _ = 0; _ < n; _++) {
        lst = -1;
        for (edge e : edges)
            if (d[e.b] > d[e.a] + e.w) {
                d[e.b] = max(d[e.a] + e.w, -INF);
                p[e.b]= e.a;
                lst = e.b;
            }
    }
    
    for (edge e : edges) {
        cerr << e.a << " <-> " << e.b << " | " << e.w << $;
    }
    cerr << lst << $ << "--------\n";
    
    if (lst == -1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        int cur = lst;
        for (int i = 0; i < n; i++)
            cur = p[cur];
        
        veci path;
        for (int v = cur; !(v == cur && len(path) > 1); v = p[v]) {
            path.push_back(v + 1);
        }
        
        reverse(all(path));        
        cout << len(path) << $ << path << $;
        
    }

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

