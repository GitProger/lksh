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

#define VAR(a) cerr<<#a<<": "<<a<<'\n'
#define VAR2(a,b) cerr<<#a<<": "<<a<<' '<<#b<<": "<<b<<'\n'
#define VAR3(a,b,c) cerr<<#a<<": "<<a<<a<<' '<<#b<<": "<<b<<' '<<#c<<": "<<c<<'\n'
#define VAR4(a,b,c,d) cerr<<#a<<": "<<a<<a<<' '<<#b<<": "<<b<<' '<<#c<<": "<<c<<' '<<#d<<": "<<d<<'\n'


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
/*
    freopen("inexact-matching.in", "r", stdin);
    freopen("inexact-matching.out", "w", stdout);
//*/
    solve();
    cout.flush();
    cerr << "\nTime: " << setprecision(2) <<
        int(1000 * (double)clock() / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}

inline void stress() {
}
////////////////////////////////////////////////////////////////////////////////

struct Hash {
    const int BASE = 228;
    const int MOD = 1'000'000'007;
    int n = 0;
    veci pows, hsh;
    Hash(const str &s) : n(len(s)), hsh(n + 1) {
        pows.push_back(1);
        for (int i = 0; i < n; i++) {
            pows.push_back(pows.back() * BASE % MOD);
            hsh[i + 1] = (hsh[i] * BASE + s[i]) % MOD;
        }
    }
    int sub(int l, int r) const {
        int res = (hsh[r] - hsh[l] * pows[r - l] % MOD) % MOD;
        return (res + MOD) % MOD;
    }
    int trans(int pos, char c) {
        int h1 = (sub(0, pos) * BASE + c) % MOD;
        int h2 = sub(pos + 1, n);
        int len2 = n - pos - 1;
        return (h1 * pows[len2] % MOD + h2 + MOD) % MOD;
    }
};

const str alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
inline void solve() {
    str a, b;
    cin >> a >> b;
    int n = len(b), m = len(a);
    if (m > n) {
        cout << 0 << $;
        return;
    }
    map<int, veci> mp;
    veci ans;
    Hash h1(b), h2(a);

    for (int i = 0; i <= n - m; i++) {
//        cout << i << " -> " << b.substr(i, m) << ": " << h1.sub(i, i + m) << $;
        mp[h1.sub(i, i + m)].push_back(i + 1);
    }

    for (int i : mp[h2.sub(0, m)]) ans.push_back(i);
    
    for (int pos = 0; pos < m; pos++)
        for (char c : alphabet) {
            if (c != a[pos])
                for (int i : mp[h2.trans(pos, c)])
                    ans.push_back(i);
        }
        
    // O(n * alpha * log(ans) + n * log(n)) = O(53 n log(n))
    
    sort(all(ans));
    cout << len(ans) << $ << ans << $;
//    for (auto x : mp) cerr << x.fir << " :|: " << x.sec << $;
    
}
/*

aaaa
Caaabdaaaa

aaaa
aCaabdaaaa


*/

