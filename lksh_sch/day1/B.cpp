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
/*
    freopen("jam.in", "r", stdin);
    freopen("jam.out", "w", stdout);
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

int q_id = 0;
#define X first
#define Y second;
//vec<prii> sum;
int N = 10000;

veci sum_x(N), sum_y(N), sub(N), l(N), r(N), x(N), y(N), pos(N);

void update(veci &a, veci &b, veci &ans) {
    int n = len(a);
    for (int i = 0; i < q_id; i++) {
        sum_x[l[i]] += x[i];
        sum_x[r[i] + 1] -= x[i];
        sum_y[l[i] + 1] += y[i];
        sum_y[r[i] + 1] -= y[i];
        sub[r[i] + 1] += y[i] * (r[i] - l[i]);
    }
    int add = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            sum_x[i] += sum_x[i - 1];
            sum_y[i] += sum_y[i - 1];
        }
        int init = a[i] + sum_x[i];
        add += sum_y[i] - sub[i];
        a[i] += add;
        if (ans[i] == -1 && a[i] >= b[i]) {
            int val = init;
            for (int j = 0; j < q_id; j++) {
                if (l[j] > i || r[j] < i) continue;
                val += x[j] + y[j] * (i - l[j]);
                if (val >= b[i]) {
                    ans[i] = pos[j];
                    break;
                }
            }
        }
    }
    sum_x.assign(N, 0);
    sum_y.assign(N, 0);
    sub.assign(N, 0);
}

inline void solve() {
    int n; cin >> n;
    int block = (int)sqrt(n);
    veci a(n), b(n); cin >> a;
    veci ans(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        if (a[i] >= b[i]) ans[i] = 0;
        else ans[i] = -1;
    }
    
    int m; cin >> m;
    int q_id = 0;
    for (int i = 0; i < m; i++) {
        cin >> l[i] >> r[i] >> x[i] >> y[i];
        --l[i]; --r[i];
        pos[q_id] = i + 1;
        q_id++;
        if (q_id == block) {
            update(a, b, ans);
            q_id = 0;
        }
    }
    if (q_id > 0) update(a, b, ans);
    cout << ans << $;
}
/*


*/

