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
    veci arr;
    Node *left = nullptr, *right = nullptr;
    Node(int _l, int _r): l(_l), r(_r) {}
    Node(int _l, int _r, const veci &a): l(_l), r(_r), arr(a) {}
    Node(int _l, int _r, const veci &a, Node *lc, Node *rc):
        l(_l), r(_r), arr(a),
        left(lc), right(rc)
    {}
} *pNode;

void merge(const veci &a1, const veci &a2, veci &res) {
    res = veci(len(a1) + len(a2));
    int p1 = 0, p2 = 0, pr = 0;
    while (p1 < len(a1) && p2 < len(a2)) {
        if (a1[p1] < a2[p2]) {
            res[pr] = a1[p1];
            p1++;
        } else {
            res[pr] = a2[p2];
            p2++;
        }
        pr++;
    }
    if (p1 == len(a1))
        while (p2 != len(a2)) res[pr++] = a2[p2++];
    if (p2 == len(a2))
        while (p1 != len(a1)) res[pr++] = a1[p1++];
}

void upd(pNode v) {
    merge(v->left->arr, v->right->arr, v->arr);
}

void build(pNode &v, int l, int r, const veci &a) {
    int m = (l + r) / 2;
    v = new Node(l, r);
    if (l < r) {
        build(v->left, l, m, a);
        build(v->right, m + 1, r, a);
        upd(v);
    } else {
        v->arr = veci{a[l]};
    }
}
void build(pNode &v, const veci &a) {
    build(v, 0, (int)a.size() - 1, a);
}

int get(pNode v, int l, int r, int mn, int mx) {
    if (v == nullptr) return 0;
    if (l > r || l > v->r || v->l > r) return 0;
    if (l == v->l && r == v->r) {
        return 
            upper_bound(all(v->arr), mx) -
            lower_bound(all(v->arr), mn);
    }
    int vm = (v->l + v->r) / 2;
    return get(v->left , l             , min(r, vm), mn, mx)
         + get(v->right, max(l, vm + 1), r         , mn, mx);
}

inline void solve() {
//*
    freopen("permutation.in", "r", stdin);
    freopen("permutation.out", "w", stdout);
//*/    
    int n, m; cin >> n >> m;
    veci a(n); cin >> a;

    pNode tree = nullptr;
    build(tree, a);

    while (m--) {
        int x, y, k, l;
        cin >> x >> y >> k >> l;
        --x; --y;
        cout << get(tree, x, y, k, l) << $;
    }
}
/*


*/


