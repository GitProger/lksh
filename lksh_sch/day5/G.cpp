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
/*
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
const int MOD = 1'000'000'007;

vec<veci> dp(200, veci(20));

bool is_inc(const str &a) {
    for (int i = 1; i < len(a); i++)
        if (a[i - 1] > a[i]) return false;
    return true;
}

int vs(int ap, int d) {
    return dp[ap + d - 1][d - 1];
}

int get(veci x) {
    int n = len(x);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int p = 0; 
        if (i > 0) p = x[i - 1];
        if (x[i] < p) return ans;
        for (int j = p; j < x[i]; j++) {
            ans += vs(n - i - 1, 10 - j);
            ans %= MOD;
        }
    }
    return ans;
}

inline void solve() {
    str l, r; cin >> l >> r;
    veci la, ra;
    for (char e : l) la.psh(e - '0');
    for (char e : r) ra.psh(e - '0');

    dp[0][0] = 1;

    for (int i = 1; i < 200; i++) {
        dp[i][0] = 1;
        for (int j = 1; j < 20; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
            dp[i][j] %= MOD;
        }
    }



    int ans = get(ra) - get(la);
    if (is_inc(r)) ans++;
    ans = (ans % MOD + MOD) % MOD;
    cout << ans << $;
}
/*
5
46 25 62 11 45
*/

