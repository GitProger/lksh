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

inline void solve() {
//*
    freopen("power.in", "r", stdin);
    freopen("power.out", "w", stdout);
//*/
    ll n, t; cin >> n >> t;
    ll s = (int)sqrt(n) + 1;
    veci a(n); cin >> a;
    vec<query> q;
    veci answer(t);
    for (ll i = 0; i < t; i++) {
        ll l, r; cin >> l >> r; --l; --r;
        q.push_back(query(l, r, i, s));
    }
    sort(q.begin(), q.end());

//    map<ll, ll> jg;
    veci jg(1000010);
    
    ll lp = q[0].l, rp = q[0].r, ans = 0;
    for (ll i = lp; i <= rp; i++) {
        int s = a[i];
        ans -= s * jg[s] * jg[s];
        jg[s]++;
        ans += s * jg[s] * jg[s];
    }

    for (auto &ask : q) {
        ll l = ask.l, r = ask.r;
        for (ll i = lp; i < l; i++) {
            int s = a[i];
            ans -= s * jg[s] * jg[s];
            jg[s]--;
            ans += s * jg[s] * jg[s];
        }
        for (ll i = r + 1; i <= rp; i++) {
            int s = a[i];
            ans -= s * jg[s] * jg[s];
            jg[s]--;
            ans += s * jg[s] * jg[s];
        }
        for (ll i = l; i < lp; i++) {
            int s = a[i];
            ans -= s * jg[s] * jg[s];
            jg[s]++;
            ans += s * jg[s] * jg[s];
        }
        for (ll i = rp + 1; i <= r; i++) {
            int s = a[i];
            ans -= s * jg[s] * jg[s];
            jg[s]++;
            ans += s * jg[s] * jg[s];
        }

        answer[ask.id] = ans;
        lp = l, rp = r;
    }
    for (const ll &x : answer) cout << x << $;
}
/*


*/

