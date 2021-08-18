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
    freopen("prefix.in", "r", stdin);
    freopen("prefix.out", "w", stdout);
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

#define value first
#define index second

inline void solve() {
    str s, v; cin >> s >> v;
    int n = len(s), m = len(v);
    str t = s + "$" + v;
    veci z = z_func(t);
    vec<prii> ans;
    for (int i = n + 1; i <= n + m; i++)
        if (z[i] != 0) ans.emplace_back(z[i], i - n - 1);
/*
    for (int i = 0; i <= n; i++) cerr << " 0 ";
    for (int i = 0; i < m; i++) cerr << (i < 10 ? " " : "") << i << " ";
    cerr << $;
    for (int i = 0; i <= n + m; i++) cerr << (i < 10 ? " " : "") << i << " ";
    cerr << $;
    for (int x : z) cerr << x << "  ";
    cerr << $ << ' ';
    for (char c : t) cerr << c << "  ";
    cerr << $;
    for (auto x : ans) cerr << "{" << x.value << "; " << x.index << "} ";
    cerr << $;
//*/
    vec<str> result;
    int lastIndex = 0;
    for (int i = 1; i < len(ans); i++) {
        auto getLastChar = [=] (int j) {
            return ans[j].index + ans[j].value - 1; // value - substring length, index - substr begin
        };
        
        lastIndex = max(lastIndex, getLastChar(i - 1));
        if (lastIndex >= ans[i].index && lastIndex < getLastChar(i))
            ans[i - 1].value = ans[i].index - ans[i - 1].index;
        else if (lastIndex + 1 < ans[i].index) {
            cout << "Yes\n";
            return;
        } else if (getLastChar(i) <= lastIndex)
            ans[i].index = -1;
	}

//    for (auto x : ans) cerr << "{" << x.value << "; " << x.index << "} ";
//    cerr << $;
	
	for (auto e : ans) {
        if (e.index != -1)
            result.push_back(v.substr(e.index, e.value));
	}

//*/
    
    if (len(result) == 0)
        cout << "Yes\n";
    else {
        cout << "No\n";
        cout << result << $;
    }
}
/*
abracadabra
abrabracada
> No
> abr abracada

abracadabra
arbadacarba
> Yes



*/

