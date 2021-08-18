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
    solve();
    cout.flush();
    cerr << "\nTime: " << setprecision(2) <<
        int(1000 * (double)clock() / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}

inline void stress() {
}
////////////////////////////////////////////////////////////////////////////////

int rmin(int &a, int b) { return (a = min(a, b)); }
int rmax(int &a, int b) { return (a = max(a, b)); }

void remove(veci &a, int &idx) {
    veci b;
    for (int i = 0; i < len(a); i++) {
        if (i != idx) b.psh(a[i]);
    }
    a = b;
    idx--;
}

inline void solve() {
    #define weight first
    #define cost second
/*
    freopen("dowry.in", "r", stdin);
    freopen("dowry.out", "w", stdout);
    //*/
    int n, l, r;
    veci w[2], c[2], f[2];
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        (i < n / 2 ? w[0] : w[1]).psh(a);
        (i < n / 2 ? c[0] : c[1]).psh(b);
    }
    int sz[2] = {n / 2, n - n / 2};
    
    for (int _ = 0; _ < 2; _++) {
        #define w w[_]
        #define c c[_]
        #define sz sz[_]
        #define f f[_]
        for (int mask = 0; mask < (1 << sz) - 1; mask++) {
            for (int i = 0; i < sz; i++) {
                if (mask & (1 << i) {
                    f[i].weight += w[i]
                    f[i].cost += c[i]
                }
            }
        }
        sort(all(f));
        for (int i = 0; i < min(sz, len(f)); i++) {
            for (int j = 0; j < i; j++) {
                if (f[j].w <= f[i].w && f[j].cost >= f[i].cost) {
                    remove(f, i);
                }
            }
        }
        
        #undef w
        #undef c
    }
    
    

}
/*


*/
