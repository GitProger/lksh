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
    int l = -1, r = -1, sum = 0;
    Node *left = nullptr, *right = nullptr;
    Node(int _l, int _r, int s = 0):
        l(_l), r(_r), sum(s)
    {}
    Node(int _l, int _r, int s, Node *lc, Node *rc):
        l(_l), r(_r), sum(s),
        left(lc), right(rc)
    {}
} *pNode;

void upd(pNode v) {
    v->sum = v->left->sum + v->right->sum;
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
    build(v, 0, (int)a.size() - 1, a);
}


int sum(pNode v, int l, int r) { // vl, vr are v->l, v->r
    if (v == nullptr) return 0;
    if (l > r || l > v->r || v->l > r) return 0;
    if (l == v->l && r == v->r) return v->sum;
    int vm = (v->l + v->r) / 2;
    return sum(v->left , l             , min(r, vm))
         + sum(v->right, max(l, vm + 1), r         );
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

int find_kth(pNode v, int k) {
    if (v == nullptr) return -1;
    if (k > v->sum) return -1;
    if (v->l == v->r) return v->l;
	if (k <= v->left->sum)
        return find_kth(v->left, k);
    else
        return find_kth(v->right, k - v->left->sum);
}

int find_kth(pNode v, int k, int l, int r) {
    if (v == nullptr) return -1;
    if (k > v->sum) return -1;
    if (v->l == v->r) return v->l;
    int m = (v->l + v->r) / 2;
	if (k <= v->left->sum - sum(v, 0, l - 1))
        return find_kth(v->left, k, l, m);
    else
        return find_kth(v->right, k - v->left->sum, m + 1, r);
}


void trip(Node *root) {
    if (root == nullptr) return;
    cout << root << ": "
         << root->left << " " << root->right << " | "
         << "[" << root->l << "; " << root->r << "] " 
         << root->sum << endl;
    trip(root->left);
    trip(root->right);
}


inline void solve() {
//*
    freopen("kthzero.in", "r", stdin);
    freopen("kthzero.out", "w", stdout);
//*/    
    int n; cin >> n;
    veci a(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x; x = !x; // 1 - is sero, 0 - not zero
        a[i] = x;
    }
    int m; cin >> m;

    pNode tree = nullptr;
    build(tree, a);

    int cur = 0;
    while (m--) {
        str s; cin >> s;
        if (s == "u") {
            int p, v; cin >> p >> v;
            setv(tree, p - 1, !v);
            cur++;
        } else if (s == "s") {
			int l, r, k; cin >> l >> r >> k;
			--l; --r;
            int ans = find_kth(tree, k + sum(tree, 0, l - 1));
            if (sum(tree, 0, ans) > sum(tree, 0, r)) ans = -1;
            if (ans != -1) {
                ans += 1; // l + 1
            }
            cout << ans << $;
        } else {
            trip(tree);
        }
    }
}
/*
5
0 0 3 0 2
3
u 1 5
u 1 0
s 1 5 3


*/



