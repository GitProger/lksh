#include <bits/stdc++.h>
using namespace std;
//#pragma comment(linker, "/stack:200000000")
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune,native")
/*
  ifstream in_str_io("sum.in");
  ofstream out_str_io("sum.out");
  #define cout out_str_io
  #define cin in_str_io
//*/
//#define int long long
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

inline void solve();
signed main() {
    solve();
    return 0;
}

inline void stress() {
}
////////////////////////////////////////////////////////////////////////////////

struct stree {
    struct segment {
        ll l = 0, r = 0, sum = 0;
        segment(ll a, ll b, ll c): l(a), r(b), sum(c) {}
        segment(): l(0), r(0), sum(0) {}
        friend ostream &operator << (ostream &o, const segment &x) {
            o << "[" << x.l << "; " << x.r << "] " << x.sum << " | ";
            return o;
        }
    };
    ll cnt = 0, n = 0;
    vector<ll> arr;
    vector<segment> segs;
    stree(ll N) {
        n = N;
        arr = vector<ll>(n, 0);
        cnt = (ll)sqrt(n) + 1;
        for (ll s = 0; s < n; s += cnt) {
            ll l = s, sum = 0, r = min(n - 1, s + cnt);
            for (ll i = 0; i < cnt && s + i < n; i++) {
                sum += arr[s + i];
            }
            segs.push_back(segment(l, r - 1, sum));
        }
    }
    ll sum(ll l, ll r) {
        ll outer = 0, inner = 0;
        ll start = 0, end = 0;
        start = (l + cnt - 1) / cnt;
        end = (r + 1) / cnt;
        for (ll i = start; i < end; i++) inner += segs[i].sum;
        for (ll i = l;
             i < start * cnt && i <= r;
             i++) outer += arr[i];
        if (start <= end)
            for (ll i = end * cnt; i <= r; i++) outer += arr[i];
        return inner + outer;
    }
    void set(ll i, ll x) {
        segs[i / cnt].sum += x - arr[i];
        arr[i] = x;
    }
};

inline void solve() {
	freopen("sum.in", "r", stdin);
	freopen("sum.out", "w", stdout);
    ll n, k; cin >> n >> k;
    stree s(n);
    while (k--) {
        char c; cin >> c;
        if (c == 'A') {
            ll i, x;
            cin >> i >> x;
            i--;
            s.set(i, x);
        } else {
            ll l, r;
            cin >> l >> r;
            l--; r--;
            cout << s.sum(l, r) << '\n';
        }
    }
    cout.flush();
}
/*


*/

