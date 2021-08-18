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
    freopen("movetofront.in", "r", stdin);
    freopen("movetofront.out", "w", stdout);
    solve();
    cout.flush();
    return 0;
}

inline void stress() {
}
////////////////////////////////////////////////////////////////////////////////

struct Node {
    int x, y, sz = 1;
    Node *left, *right;
    Node(int i):
        x(i), y((rand() << 6) + rand()),
        left(nullptr), right(nullptr)
    {}
};
typedef Node *pNode;

int size(Node *r) { return r != nullptr ? r->sz : 0; }
void upd(Node *r) {
    if (r == nullptr) return;
    r->sz = size(r->left) + 1 + size(r->right);
}

pair<pNode, pNode> split(pNode root, int x) { // <x, >=x
    if (root == nullptr) return make_pair(nullptr, nullptr);
    if (x < 1 + size(root->left)) {
        auto buf = split(root->left, x);
        Node *r1 = buf.first, *r2 = buf.second;
        root->left = r2;
        upd(root);
        return make_pair(r1, root);
    } else { 
        auto buf = split(root->right, x - 1 - size(root->left));
        Node *r1 = buf.first, *r2 = buf.second;
        root->right = r1;
        upd(root);
        return make_pair(root, r2);            
    }
}
 
    
Node *merge(Node *r1, Node *r2) {
    if (r1 == nullptr) return r2;
    if (r2 == nullptr) return r1;
    if (r1->y <= r2->y) {
        r1->right = merge(r1->right, r2);
        upd(r1);
        return r1;
    } else {
        r2->left = merge(r1, r2->left);
        upd(r2);
        return r2;
    }
}

void insert(pNode &root, int x) {
    auto buf = split(root, x);
    root = merge(merge(buf.first, new Node(x)), buf.second);
}

void shift1(pNode &r) {
    auto buf = split(r, r->sz - 1);//1);
    r = merge(buf.second, buf.first);
}

void ahead(pNode root, int l, int r) {
    auto buf = split(root, l);
    pNode r2 = buf.second;
    auto buf2 = split(r2, r - l + 1);
    shift1(buf2.first); // >= l, < r + 1
    root = merge(buf.first, merge(buf2.first, buf2.second));
}

void build_ans(pNode root, veci &a) {
    for (int i = 0; i < len(a); i++) {
        auto p = split(root, 1);
        a[i] = p.first->x;
        delete p.first;
        root = p.second;
    }
}

inline void solve() {
    srand(time(NULL));
    int n, m; cin >> n >> m;
    pNode tree = nullptr;
    for (int i = 1; i <= n; i++)
        insert(tree, i);

    while (m--) {
        int l, r; cin >> l >> r;
        ahead(tree, l - 1, r - 1);
    }
    
    
    veci a(n);
    build_ans(tree, a);
    cout << a << $;
}
/*
6 3
2 4
3 5
2 2

*/


