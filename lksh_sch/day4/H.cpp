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
    freopen("network.in", "r", stdin);
    freopen("network.out", "w", stdout);
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

inline void stress() {
}
////////////////////////////////////////////////////////////////////////////////

template <class T> T rmin(T &a, const T &b) { return (a = min(a, b)); }
template <class T> T rmax(T &a, const T &b) { return (a = max(a, b)); }
template <class T> T reql(T &a, const T &b) { return (a = b); }
int sum(const veci &a) {
    int s = 0;
    for (int e : a) s += e;
    return s;
}

struct meeting {
    int a = 0, b = 0, c = 0;
    meeting() {}
    meeting(int a, int b, int c): a(a), b(b), c(c) {}
};

inline void solve() {
    int n; cin >> n;
    vec<str> s(n); cin >> s;

    auto can = [=] (int a, int b) -> bool {
        return s[a][b] == 'Y';
    };
    
    auto cnt = [=] (int mask) -> int {
        int r = 0;
        for (int i = 0; i < 30; i++)
            if (mask & (1 << i)) r++;
        return r;
    };

    veci possible(1 << n);
    int ans = 0;
    possible[0] = 1;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (!possible[mask]) continue;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if ((mask & (1 << i)) || (mask & (1 << j))) continue;
                if (i == j) continue;
                int m = mask | (1 << i) | (1 << j);
                if (can(i, j))
                    possible[m] = 1;
            }
        }
        if (cnt(mask) > cnt(ans))
            ans = mask;
    }
    cout << cnt(ans) << $;
}
/*

*/
