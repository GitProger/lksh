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
    freopen("knapsack-1.in", "r", stdin);
    freopen("knapsack-1.out", "w", stdout);
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

veci w, c;
vec<veci> t;
veci ans;
void get(int i, int m) {
    if (t[i][m] == 0) return;
    if (t[i][m] == t[i - 1][m]) 
        get(i - 1, m);
    else {
        get(i - 1, m - w[i]);
        ans.psh(i);
    }
}


inline void solve() {
    int n, s; cin >> n >> s;
    w = veci(n + 1), c = veci(n + 1);
    for (int i = 1; i <= n; i++) cin >> w[i] >> c[i];
   
    t = vec<veci>(n + 1, veci(s + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= s; j++) {
            t[i][j] = t[i - 1][j];
            if (w[i] <= j) {
                t[i][j] = max(t[i][j], t[i - 1][j - w[i]] + c[i]);
            }
        }

/*    for (int i = 0; i <= s; i++) cout << (i < 10 ? " " : "") << i << " ";
    cout << $;
    for (int i = 0; i <= n; i++) {
        for (int e : t[i])
            cout << (e < 10 ? " " : "") << e << " ";
        cout << $;
    }*/

    get(n, s);
    cout << t[n][s] << $
         << len(ans) << $
         << ans << $;
}
/*

3 10
1 2
4 3
8 9

*/
