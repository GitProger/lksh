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
//*
    freopen("lumber.in", "r", stdin);
    freopen("lumber.out", "w", stdout);
//*/
    int t = 1;
   // cin >> t; 
    while (t--) {
        solve();
    }
    cout.flush();
    cerr << "\nTime: " << setprecision(2) <<
        int(1000 * (double)clock() / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

template <class T> T rmin(T &a, const T &b) { return (a = min(a, b)); }
template <class T> T rmax(T &a, const T &b) { return (a = max(a, b)); }
template <class T> T reql(T &a, const T &b) { return (a = b); }

struct line {
    int k = 0, b = 0;
    line() {}
    line(int k, int b): k(k), b(b) {}
    ld intersec(const line &l) const {
        return (l.b - b) / ld(k - l.k);
    }
    int val(int x) const {
        return k * x + b;
    }
};

inline void solve() {
    int n; cin >> n;
    veci a(n), b(n); 
    cin >> a >> b;
    // cut down first tree, than go to b_n, to get free petrol    
    veci dp(n, INF);
    dp[0] = 0;
/*    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            dp[i] = min(dp[i], dp[j] + a[i] * b[j]);
        }
    }*/
    vec<line> lines;
    vec<ld> start;
    lines.psh(line(b[0], 0));
    start.psh(-1e15);
    int sz = 1;
    for (int i = 1; i < n; i++) {
        int j = lower_bound(all(start), (ld)a[i]) - start.begin() - 1;

        dp[i] = lines[j].k * a[i] + lines[j].b;

        if (i == n) continue; 
        line cur(b[i], dp[i]);
        while (sz > 1 && lines[sz - 2].intersec(cur) < start[sz - 1]) {
            lines.pop_back();
            start.pop_back();
            sz--;
        }

        lines.psh(cur);
        start.psh(lines[sz - 1].intersec(cur));
        sz++;
    }
    cout << dp[n - 1] << $;
}
/*

5
1 2 3 4 5
5 4 3 2 0

6
1 2 3 10 20 30
6 5 4 3 2 0

*/
