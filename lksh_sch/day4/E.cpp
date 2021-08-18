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
    freopen("meetings.in", "r", stdin);
    freopen("meetings.out", "w", stdout);
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
    int n, k; cin >> n >> k;
    vec<meeting> ms(n);
    for (int i = 0; i < n; i++) {
        int a, b, c; cin >> a >> b >> c;
        ms[i] = meeting(a, b, c);
    }
    
    auto change = [=] (int mask) {
        int c = 0;
        for (int i = 0; i < 30; i++)
            if (mask & (1 << i)) c += ms[i].c;
        return c;
    };
    auto cnt = [=] (int mask) {
        int r = 0;
        for (int i = 0; i < 30; i++)
            if (mask & (1 << i)) r++;
        return r;
    };

    int lastCnt = 1 << n;
    veci possible(lastCnt), prev(lastCnt);
    int ans = 0;
    possible[0] = 1;
    // we have mask, and we a adding i
    for (int mask = 0; mask < lastCnt; mask++) {
        if (!possible[mask]) continue;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) continue; // there is already i
            if (k + change(mask) < ms[i].a) continue;
            if (k + change(mask) > ms[i].b) continue;
            possible[mask | (1 << i)] = 1;
            prev[mask | (1 << i)] = i;
        }
        if (cnt(mask) > cnt(ans))
            ans = mask;
    }
    veci res(cnt(ans), 0);
    int m = ans;
    for (int i = cnt(m) - 1; i >= 0; i--) {
        res[i] = prev[m] + 1;
        m ^= (1 << prev[m]);
    }
    cout << cnt(ans) << $ << res << $;

}
/*

*/
