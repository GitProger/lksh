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
//*
    freopen("2sat.in", "r", stdin);
    freopen("2sat.out", "w", stdout);
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

graph gs, gr;
veci used, comp, order;

void dfs1(int v) {
    used[v] = 1;
    for (int u : gs[v])
        if (!used[u])
            dfs1(u);
    order.push_back(v);
}

void dfs(int v, int c) {
    comp[v] = c;
    for (int u : gr[v])
        if (comp[u] == -1)
            dfs(u, c);
}


inline void solve() {
    int n, m;
    while (cin >> n >> m) {
        gs = graph(2 * n); // A, !A, B, !B, ...
        gr = graph(2 * n);
        for (int i = 0; i < m; i++) {
            int i1, e1, i2, e2;
            cin >> i1 >> e1 >> i2 >> e2;
            // e == 1 -> A, e == 0 -> !A
            auto add = [=] (int a, int b) {
                gs[a].psh(b);
                gr[b].psh(a);
            };
            add(2 * i1 + e1, 2 * i2 + 1 - e2);
            add(2 * i2 + e2, 2 * i1 + 1 - e1);
/*
            if (e1 && !e2) { // A || !B     ->  !a -> !b, b -> a
                add(2 * i1 + 1, 2 * i2 + 1);
                add(2 * i2, 2 * i1);
            }
            if (!e1 && e2) { // !A || B     ->  a -> b, !b -> !a
                add(2 * i1, 2 * i2);
                add(2 * i2 + 1, 2 * i1 + 1);
            }
            if (e1 && e2) { // A || B       ->  !a -> b, !b -> a
                add(2 * i1 + 1, 2 * i2);
                add(2 * i2 + 1, 2 * i1);
            }
            if (!e1 && !e2) { // !A || !B   -> a -> !b, b -> !a
                add(2 * i1, 2 * i2 + 1);
                add(2 * i2, 2 * i1 + 1);
            }
//*/
        }

        used = veci(2 * n, 0); 
        order.clear(); 
        for (int i = 0; i < 2 * n; i++)
            if (!used[i])
                dfs1(i);
        comp = veci(2 * n, -1);
        reverse(all(order));
        int col = 0;
        for (int v : order)
            if (comp[v] == -1)
                dfs(v, col++);
 
        /*
        cerr << $ << comp << $;
        for (int i = 0; i < 2 * n; i++) {
            cerr << (i % 2 ? "!" : " ") << "var[" << i / 2 << "] " << i << ": ";
            cerr << gs[i] << $;
        }//*/

/*        for (int i = 0; i < 2 * n; i += 2)
            if (comp[i] == comp[i + 1])
                cerr << "error\n"; //*/

        for (int i = 0; i < 2 * n; i += 2) {
            int ans = false;
            if (comp[i] > comp[i + 1]) ans = true;
            cout << ans;
        }
        cout << $;
    }
}
/*

1 0
2 2
0 0 1 0
0 1 1 1
3 4
0 1 1 0
0 0 2 1
1 1 2 0
0 0 0 1

*/

