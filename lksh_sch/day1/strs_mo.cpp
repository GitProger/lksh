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
#define MAX LONG_LONG_MAX
#define INF LONG_LONG_MAX
#define MIN LONG_LONG_MIN
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
    solve();
    cout.flush();
    return 0;
}

inline void stress() {
}
////////////////////////////////////////////////////////////////////////////////

struct query {
    ll l, r, id, s;
    query():
        l(-1), r(-1), id(-1), s(0)
    {}
    query(ll l_, ll r_, ll id_, ll s_):
        l(l_), r(r_), id(id_), s(s_) 
    {}
    bool operator < (const query &x) const {
        return make_pair(l / s, r) < make_pair(x.l / x.s, x.r);
    }
};


hash<str> hsh;

inline void solve() {
 //   freopen("corrector.in", "r", stdin);
 //   freopen("corrector.out", "w", stdout);
    str s; cin >> s;
    int n; cin >> n; 
    vec<veci> a(100010);
    int maxLen = 0;
    for (int i = 0; i < n; i++) {
        str s; cin >> s;
        a[len(s)].push_back(hsh(s));
        maxLen = max(maxLen, len(s));
    }
    int t; cin >> t;
    vec<query> q;
    for (ll i = 0; i < t; i++) {
        ll l, r; cin >> l >> r; --l; --r;
        q.push_back(query(l, r, i, s));
    }
    sort(q.begin(), q.end());
    veci ans(t);

    for 
    
}
/*


*/


