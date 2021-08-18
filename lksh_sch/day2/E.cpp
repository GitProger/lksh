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

mt19937 rnd(1234);
inline void solve();
signed main() {
    solve();
    cout.flush();
    return 0;
}

inline void stress() {
}
////////////////////////////////////////////////////////////////////////////////

struct Node {
    int index, y, sz = 1;
    bool rev = false;
    int val = INF, min = INF;
    Node *left, *right;
    Node(int i, int m = INF):
        index(i), y(rnd()), val(m), min(m),
        left(nullptr), right(nullptr)
    {}
};
typedef Node *pNode;

int id(Node *x) {
    if (x == nullptr) return -1;
    return x->index;
}
void trip(Node *root) {
    if (root == nullptr) return;
    cout << root->index << ": "
         << id(root->left) << " " << id(root->right) << " | "
         " min: " << root->min << " val: " << root->val << " rev: " << root->rev << endl;
//    push(root);
    trip(root->left);
    trip(root->right);
}


int size(Node *r) { return r != nullptr ? r->sz : 0; }
int minv(Node *r) { return r != nullptr ? r->min : INF; }

void upd(Node *r) {
    if (r == nullptr) return;
    r->sz = size(r->left) + 1 + size(r->right);
    r->min = min({r->val, minv(r->left), minv(r->right)});
}

void push(Node *r) {
    if (r->rev) {
        swap(r->left, r->right);
        if (r->left) r->left->rev ^= 1;
        if (r->right) r->right->rev ^= 1;
    }
    r->rev = 0;
}

pair<pNode, pNode> split(pNode root, int x) {
    if (root == nullptr) return make_pair(nullptr, nullptr);
    push(root);
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
        push(r1);
        r1->right = merge(r1->right, r2);
        upd(r1);
        return r1;
    } else {
        push(r2);
        r2->left = merge(r1, r2->left);
        upd(r2);
        return r2;
    }
}

void insert(pNode &root, int x, int mn = INF) {
    auto buf = split(root, x);
    root = merge(merge(buf.first, new Node(x, mn)), buf.second);
}

void reverse(pNode &root, int l, int r) {
    auto b1 = split(root, r + 1);
    auto b2 = split(b1.first, l);
    b2.second->rev ^= 1;

    root = merge(b2.first, merge(b2.second, b1.second));
}

int get_min(pNode &root, int l, int r) {
    auto buf1 = split(root, l);
    pNode r2 = buf1.second;
    auto buf2 = split(r2, r - l + 1);
    int ans = minv(buf2.first);
    root = merge(buf1.first, merge(buf2.first, buf2.second));
    return ans;
}

inline void solve() {
    int n, m; cin >> n >> m;
    pNode tree = nullptr;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        insert(tree, i, x);
     //   cout << get_min(tree, 0, i) << " " << tree->min << " " << $;
    }
//    trip(tree);

    while (m--) {
        int t, l, r; cin >> t >> l >> r; --l; --r;
        if (t == 1) {
            reverse(tree, l, r);
        } else if (t == 2) {
            cout << get_min(tree, l, r) << endl;
        } else {
            trip(tree);
        }
    }
}
/*
10 7
5 3 2 3 12 6 7 5 10 12
2 4 9
1 4 6
2 1 8
1 1 8
1 8 9
2 1 7
2 3 6

*/



