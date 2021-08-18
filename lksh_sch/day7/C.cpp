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

int strToTime(const str &a) {
    int h = atoi(a.substr(0, 2).c_str());
    int m = atoi(a.substr(3, 2).c_str());
    return h * 60 + m;
}
int get(int a, int b, int c, int d) {
    return abs(a - c) + abs(b - d);
}

struct order {
    int t = 0, a = 0, b = 0, c = 0, d = 0, end = 0;
    order() {}
    order(int t, int a, int b, int c, int d): t(t), a(a), b(b), c(c), d(d) {
        end = t + get(a, b, c, d);
    }
    bool hurry(const order &x) const {
        return (end + get(c, d, x.a, x.b) < x.t);
    }
};

graph g;
veci used, par;
bool dfs(int v) {
    if (used[v]) return false;
    used[v] = 1;
    for (int u : g[v]) 
        if (par[u] == -1 || dfs(par[u])) {
            par[u] = v;
            return true;
        }
    return false;
}


inline void solve() {
    int n; cin >> n;
    g.resize(n); used.resize(n); par.resize(n, -1);
    vec<order> tab;
    for (int i = 0; i < n; i++) {
        str tt; int t, a, b, c, d;
        cin >> tt >> a >> b >> c >> d;
        t = strToTime(tt);
        tab.psh(order(t, a, b, c, d));
    }    

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (tab[i].hurry(tab[j]))
                g[i].psh(j);
//            cerr << i << " - " << j << " -> " << tab[i].hurry(tab[j]) << $;
        }
/*
    for (auto x : tab)
        cout << x.t / 60 << ":" << x.t % 60 << " " << x.end / 60 << ":" << x.end % 60 << $;     
    for (int i = 0; i < n; i++)
        cout << i << ": " << g[i] << $;
//*/
    for (int v = 0; v < n; v++) {
        used.assign(n, 0);
        dfs(v);
    }
    int ans = count_if(all(par), [=] (int x) { return x != -1; });    
    cout << n - ans << $;

}
/*

2
08:00 10 11 9 16
08:07 9 16 10 11

2
08:00 10 11 9 16
08:06 9 16 10 11

*/
