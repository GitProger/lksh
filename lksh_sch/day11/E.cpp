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
//*
    freopen("period.in", "r", stdin);
    freopen("period.out", "w", stdout);
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

veci pref_func(const str &s) {
    int n = len(s);
    veci p(n);
    for (int i = 1, j; i < n; i++) {
        j = p[i - 1];
        while (j > 0 && s[i] != s[j])
            j = p[j - 1];
        if (s[i] == s[j])
            j++;
        p[i] = j;
    }
    return p;
}

veci z_func(const str &s) {
    int n = len(s);
    veci z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) 
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            z[i]++;
        if (i + z[i] - 1 > r) {
            l = i;
            r= i + z[i] - 1;
        }
    }
    z[0] = n;
    return z;
}

inline void solve() {
/*    str s; cin >> s;
    int pos = -1;    
    for (int i = len(s) - 1; i > 0; i--)
        if (s[i] != s[i - 1]) {
            pos = i;
            break;
        }
    if (pos != -1)
        s = s.substr(pos) + s.substr(0, pos);
        
    str a;
    a += s[0];
    int rep = 0;
    for (int i = 1; i < len(s); i++) {
        if (s[i] != s[i - 1])
            a += s[i];
        else
            rep++;
    }    

    veci p = pref_func(a);
    int last_zero = 1;
    for (int i = 0; i < len(p); i++)
        if (p[i] == 0) last_zero = i + 1;            
    int ans = last_zero + rep / (len(a) / last_zero);
    cout << ans << $;

    VAR(s); VAR(a); VAR(p); VAR2(rep, last_zero);
    */
    str s; cin >> s;
    veci z = z_func(s);
    int n = len(s), ans = n;
    for (int i = 1; i < n; i++)
        if (i + z[i] == n && n % i == 0) {
            ans = i;
            break;
        }
    cout << ans << $;
}
/*

aaaaaaaaaaaaaaa
1
abaabaabaabaaba
3
abcdabcdabcd
4

aaabaaaabaaaaba
^    ^    ^    
5

aaaaaaabcdaaaaaaaabcda
^          ^
11
*/

