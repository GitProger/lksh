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

template<class T> void fromPair(T &a, T &b, const pair<T, T> &c) {
    a = c.first;
    b = c.second;
}

struct Node {
    int index, y, sz = 1;
    int val = 0, sum = 0;
    Node *left = nullptr, *right = nullptr;
    Node(int i, int m = 0):
        index(i), y(rnd()), val(m), sum(m)
    {}
};
typedef Node *pNode;

int size(Node *r) { return r != nullptr ? r->sz : 0; }
int sum(Node *r) { return r != nullptr ? r->sum : 0; }
void upd(Node *r) {
    if (r == nullptr) return;
    r->sz = size(r->left) + 1 + size(r->right);
    r->sum = r->val + sum(r->left) + sum(r->right);
}
void push(Node *r) {
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

void insert(pNode &root, int i, int v = 0) {
    auto buf = split(root, i);
    root = merge(merge(buf.first, new Node(i, v)), buf.second);
}
///////////////////////////////////////////////////////////////////////////////

int get_sum(pNode &root1, pNode &root2, int l, int r) {
    if (l > r) return 0;
    int l1 = (l + 1) / 2, r1 = r / 2;
    int l2 = l / 2, r2 = (r + 1) / 2 - 1;
    pNode a1, b1, c1, a2, b2, c2;
    // root_i => [a_i, b_i, c_i] => root_i

    fromPair(a1, b1, split(root1, l1));
    fromPair(b1, c1, split(b1, r1 - l1 + 1));

    fromPair(a2, b2, split(root2, l2));
    fromPair(b2, c2, split(b2, r2 - l2 + 1));

    int res = sum(b1) + sum(b2); 
    root1 = merge(merge(a1, b1), c1);
    root2 = merge(merge(a2, b2), c2);
    return res;
}

void swap(pNode &root1, pNode &root2, int l, int r) {
    int l1 = (l + 1) / 2, r1 = r / 2;
    int l2 = l / 2, r2 = (r + 1) / 2 - 1;
    pNode a1, b1, c1, a2, b2, c2;
    // root_i => [a_i, b_i, c_i] => root_i

    fromPair(a1, b1, split(root1, l1));
    fromPair(b1, c1, split(b1, r1 - l1 + 1));

    fromPair(a2, b2, split(root2, l2));
    fromPair(b2, c2, split(b2, r2 - l2 + 1));

    root1 = merge(merge(a1, b2), c1);
    root2 = merge(merge(a2, b1), c2);    
}


inline void solve() {
    // 1 - четные 0, 2, 4, ...
    // 2 - нечетные
    for (int test = 1;; test++) {
        int n, m; cin >> n >> m;
        if (n == 0 && m == 0) return;
        pNode tree1 = nullptr, tree2 = nullptr;
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            insert(i % 2 == 0 ? tree1 : tree2, i, x);
        }

        cout << "Swapper " << test << ":\n";

        while (m--) {
            int t, l, r; cin >> t >> l >> r; --l; --r;
            if (t == 1) {
                swap(tree1, tree2, l, r);
            } else if (t == 2) {
                cout << get_sum(tree1, tree2, l, r) << endl;
            }
        }
        cout << $;
    }
}
/*
5 5
1 2 3 4 5
1 2 5
2 2 4
1 1 4
2 1 3
2 4 4
0 0

*/



