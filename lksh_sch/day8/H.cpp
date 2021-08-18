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
#define pshp(a, b) push_back({(a),(b)})
#define LBL(a) cerr<<"LABEL #"<<a<<"\n"

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

const int MOD = 1'000'000'007;
inline void solve();
signed main() {
//    freopen("pairs.in", "r", stdin);
  //  freopen("pairs.out", "w", stdout);

    solve();
    cout.flush();
    cerr << "\nTime: " << setprecision(2) <<
        int(1000 * (double)clock() / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

template <class T> T rmin(T &a, const T &b) { return (a = min(a, b)); }
template <class T> T rmax(T &a, const T &b) { return (a = max(a, b)); }
template <class T> T reql(T &a, const T &b) { return (a = b); }

int getLeft(int l, int ans, int i, int n) {
    return ((17 * l + 751 + ans + 2 * i) % n) + 1;
}
int getRight(int r, int ans, int i, int n) {
    return ((13 * r + 593 + ans + 5 * i) % n) + 1;
}
int getNext(int x) {
    return (x * 23 + 21563) % 16714589;
}

inline void solve() {
    int n, m, a1; 
    cin >> n >> m >> a1;
    int l, r; cin >> l >> r; // u1 - l, v1 - r

    veci a(n, a1);
    for (int i = 1; i < n; i++)
        a[i] = getNext(a[i - 1]);

    const int SIZE = 18;
    vector<veci> sparse(n, veci(SIZE));
    for (int i = 0; i < n; ++i) sparse[i][0] = a[i];
    for (int p = 1; p < SIZE; ++p)
        for (int i = 0; i + (1 << (p - 1)) < n; ++i) {
            sparse[i][p] = min(
                sparse[i][p - 1], 
                sparse[i + (1 << (p - 1))][p - 1]
            );
        }

    int ans = 0;
    for (int i = 1; i <= m; i++) {
        int x = log2(abs(r - l));
        int l_a = min(l, r) - 1, r_a = max(l, r) - 1;
        ans = min(sparse[l_a][x], sparse[r_a - (1 << x) + 1][x]);

//        cerr << i << ": " << l << " " << r << " -> " << ans << $;

        if (i != m) {
            l = getLeft(l, ans, i, n);
            r = getRight(r, ans, i, n);
        }
    }
    cout << l << " " << r << " " << ans << $;
}
/*

10 8 12345
3 9
*/
