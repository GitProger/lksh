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


inline void solve();
signed main() {
    int t = 1;
//*
    cin >> t; 
    while (t--) //*/
        solve();
    cout.flush();
    cerr << "\nTime: " << setprecision(2) <<
        int(1000 * (double)clock() / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}

inline void stress() {
}
////////////////////////////////////////////////////////////////////////////////

template <class T> T rmin(T &a, const T &b) { return (a = min(a, b)); }
template <class T> T rmax(T &a, const T &b) { return (a = max(a, b)); }
template <class T> T reql(T &a, const T &b) { return (a = b); }

#define value first
#define index second
inline void solve() {
    int n, s; cin >> n >> s;
    vec<prii> w(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        w[i] = {x, i};
    }
    sort(all(w));

    vec<prii> dp(1 << n);
    for (int i = 0; i < n; i++)
        dp[1 << i] = {0, w[i].value};
    vec<veci> ans(n + 1);
    
    for (int mask = 1; mask < (1 << n) - 1; mask++) {
        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i))) {
                int next = mask | (1 << i);
                if (dp[mask].second + w[i].value < s) {
                    reql(dp[next], {
                        dp[mask].first, 
                        dp[mask].second + w[i].value
                    });
                } else if (dp[mask].second + w[i].value > s) {
                    reql(dp[next], {
                        dp[mask].first + 1,
                        w[i].value
                    });
                } else {
                    reql(dp[next], {
                        dp[mask].first + 1,
                        0
                    });
                }
                ans[dp[next].first].psh(w[i].index + 1);
            }
        }
    }
    for (auto x : dp) cerr << "{" << x.first << ", " << x.second << "} ";
    cerr << $; 

    int res = dp[(1 << n) - 1].first + 1;
    cout << res << $;
    for (int i = 1; i <= n; i++) {
       // if (len(ans[i]) == 0) break;
        cerr << "[" << i << "]: ";
        cout << len(ans[i]) << " " << ans[i] << $;
    }
    
    cerr << $;
}
/*
3
1 10
10
2 10
10 10
4 10
5 7 5 7


*/
