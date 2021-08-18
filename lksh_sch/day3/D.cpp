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
    freopen("joseph.in", "r", stdin);
    freopen("joseph.out", "w", stdout);
    solve();
    cout.flush();
    cerr << "\nTime: " << setprecision(2) <<
        int(1000 * (double)clock() / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}

inline void stress() {
}
////////////////////////////////////////////////////////////////////////////////

typedef struct Node {
    int l = -1, r = -1;
    int sum = 0;
    Node *left = nullptr, *right = nullptr;
    Node(int l, int r, int v = 0): l(l), r(r), sum(v) {}
    Node() {}
} *pNode;

int sum(pNode v) {
    if (v == nullptr) return 0;
    return v->sum;
}

void upd(pNode v) {
    v->sum = sum(v->left) + sum(v->right);
}

void build(pNode &v, int l, int r, const veci &a) {
    int m = (l + r) / 2;
    v = new Node(l, r);
    if (l < r) {
        build(v->left, l, m, a);
        build(v->right, m + 1, r, a);
        upd(v);
    } else {
        v->sum = a[l];
    }
}
void build(pNode &v, const veci &a) {
    build(v, 0, len(a) - 1, a);
}

void setv(pNode v, int pos, int val) {
    if (v == nullptr) return;
    if (pos < v->l || pos > v->r) return;
    if (v->l == v->r) {
        v->sum = val;
        return;
    }
    setv(v->left, pos, val);
    setv(v->right, pos, val);
    upd(v);
}

int get(pNode v, int l, int r) {
    if (v == nullptr || l > r || l > v->r || v->l > r) return 0;
    if (l <= v->l && v->r <= r) return v->sum;
    return get(v->left, l, r) + get(v->right, l, r);
}

int query(pNode v, int l, int r,int need_alive) {
    if (l == r) return l;
    
    int m = (l + r) / 2;
    int alive_left = m - l + 1 - sum(v->left);
    if (alive_left >= need_alive)
        return query(v->left, l, m, need_alive);
    else 
        return query(v->right, m + 1, r, need_alive - alive_left);
}

void out(pNode v, int n) {
    for (int i = 0; i < n; i++) cerr << get(v, i, i) << " ";
    cerr << $;
}

int getans(int n, int p) {
    int res = 0;
    for (int i = 1; i <= n; i++) res = (res + p) % i;
    return res + 1;
}

inline void solve() {
    int n, p; cin >> n >> p;
    veci a(2 * n);
    pNode tree = nullptr;
    build(tree, a);
    int left = n;
    int cur = 0;

//    p_act = p % (n - dead) == p % left
    
    while (left > 1) {
        int p_real = (p - 1) % left + 1; 
        
        int alive_left = 0;
        if(cur > 0)alive_left = cur - get(tree, 0, cur - 1);
        int r = query(tree, 0, 2 * n - 1, alive_left + p_real);
        

        cur = r % n;  
        setv(tree, cur, 1);
        setv(tree, cur + n, 1);


        alive_left = cur + 1 - get(tree, 0, cur);
        r = query(tree, 0, 2 * n - 1, alive_left + 1);
        cur = r % n;  
        left--;
    }
    cout << cur + 1 << $; 
    cerr << getans(n, p) << $;
}
/*


*/

