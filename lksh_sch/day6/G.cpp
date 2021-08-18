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
    freopen("bicone.in", "r", stdin);
    freopen("bicone.out", "w", stdout);
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


int MD = 100; // 62

int c_to_id(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    if ('a' <= c && c <= 'z') return c - 'a' + 10;
    if ('A' <= c && c <= 'Z') return c - 'A' + 10 + 26;
    return -1;
}

char id_to_c(int id) {
    if (0 <= id && id <= 9) return id + '0';
    if (10 <= id && id <= 35) return id + 'a' - 10;
    if (36 <= id) return id + 'A' - 10 - 26;    
    return ' ';
}


str from_id(int id) {
    return str(1, id_to_c(id / MD)) + str(1, id_to_c(id % MD));
}

int to_id(const str &s) { return c_to_id(s[0]) * MD + c_to_id(s[1]); }


inline void solve() {
    int n; cin >> n;
    int SZ = MD * MD + MD + 1;
    graph g(SZ);
    veci inout(SZ);
    for (int i = 0; i < n; i++) {
        str s; cin >> s;
        int v = to_id(s.substr(0, 2));
        int u = to_id(s.substr(1, 2));
        g[v].psh(u);
        inout[u]++;
        inout[v]--;
    }
    
    int cnt_in = count_if(all(inout), [=] (int d) { return d > 0; });
    int cnt_out = count_if(all(inout), [=] (int d) { return d < 0; });
    if (cnt_in + cnt_out > 2) {
        cout << "NO\n";
        return;
    }
    if (cnt_in + cnt_out == 2)
        if (cnt_in != cnt_out) {
            cout << "NO\n";
            return;
        }


    int start = 0;

    if (cnt_out == 1) {
        for (int i = 0; i < SZ; i++)
            if (inout[i] == -1) {
                start = i;
                break;
            }
    } else {
        for (int i = 0; i < SZ; i++)
            if (!g[i].empty()) {
                start = i;
                break;
            }
    }


    veci euler;
    function<void(int)> dfs_e = [&] (int v) {
         while (!g[v].empty()) {
             int u = g[v].back();
             g[v].pop_back();
             dfs_e(u);
         }
         euler.psh(v);
    };
    dfs_e(start);


    reverse(all(euler));
    
    bool ok = true;
    for (int i = 0; i < SZ; i++)
        if (!g[i].empty()) {
            ok = false;
            break;
        }
    if (!ok) {
        cout << "NO\n";
        return;
    }
;

    
    cout << "YES" << $;
    cout << from_id(euler[0])[0];
    for (int i = 0; i < len(euler); i++) cout << from_id(euler[i])[1];
    cout << $;
}
