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

const int N = 10100;
int n, m; 
vec<str> margin;
graph g(N);
veci used(N), par(N, -1);

bool ok(int x, int y) {
    return (0 <= x && x < n) && (0 <= y && y < m);
}

int get_id(int x, int y) {
    return x + n * y;
}
// x - down, y - right

void process(int x, int y) {
    vec<prii> move = {
        {0, 1}, 
        {1, 0}, 
      //  {-1, 0}, 
       // {0, -1}
    };
    for (auto m : move) {
        int dx = m.fir, dy = m.sec;
        if (ok(x + dx, y + dy)) {
            if (margin[x + dx][y + dy] == '*') {
                int v = get_id(x, y);
                int u = get_id(x + dx, y + dy);
                
                if ((x + y) % 2 != 0)
                    g[u].push_back(v);
                else
                    g[v].push_back(u);
            }
        }
    }
}

bool dfs(int v) {
    if (used[v]) return false;
    used[v] = 1;
    for (int u : g[v]) 
        if (par[u] == -1 || dfs(par[u])) {
            par[u] = v;
            return true;
        }
    return false;
}

inline void solve() {
    int a, b; 
    cin >> n >> m >> a >> b;
    margin = vec<str>(n);
    cin >> margin;
    
    int free = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            free += (margin[i][j] == '*');
    if (a >= 2 * b) {
        cout << free * b << $;
        return;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (margin[i][j] == '*')
                process(i, j);
        }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((i + j) % 2 == 0) {
                used.assign(n * m, 0);
                dfs(get_id(i, j));
            }  
        }
    } 
/* почему это не работает?    
    for (int v = 0; v < n * m; v++) {
        used.assign(n * m, 0);
        dfs(get_id(i, j));
	}
*/

    int res = count_if(all(par), [=] (int x) { return x != -1; });
    int ans = (free - 2 * res) * b + res * a;
    cout << ans << $;
}
/*
2 3 3 2
.**
.*.


*/
