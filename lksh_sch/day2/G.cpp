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

int sqr(int x) { return x * x; }

struct Node {
    int index, y, sz = 1;
    bool rev = false;
    int val = 0, sum = 0, sum2 = 0;
    Node *left = nullptr, *right = nullptr;
    Node(int i, int m = 0):
        index(i), y(rnd()), val(m), sum(m), sum2(m * m)
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
         " sum: " << root->sum << " val: " << root->val << " sum2: " << root->sum2 << endl;
//    push(root);
    trip(root->left);
    trip(root->right);
}


int size(Node *r) { return r != nullptr ? r->sz : 0; }
int sum(Node *r) { return r != nullptr ? r->sum : 0; }
int sqsum(Node *r) { return r != nullptr ? r->sum2 : 0; }

void upd(Node *r) {
    if (r == nullptr) return;
    r->sz = size(r->left) + 1 + size(r->right);
    r->sum = r->val + sum(r->left) + sum(r->right);
    r->sum2 = sqr(r->val) + sqsum(r->left) + sqsum(r->right);
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

void add(pNode &root, int id, int ch) {
    auto buf1 = split(root, id);
    auto r_left = buf1.first, rx = buf1.second;

    auto buf2 = split(rx, 1);
    auto el = buf2.first, r_right = buf2.second;
    int old_val = el->val;

    auto changed = new Node(id, old_val + ch);    
    root = merge(r_left, merge(changed, r_right));
    delete el;
}

void insert(pNode &root, int index, int v = 0) {
    auto buf = split(root, index);
    root = merge(merge(buf.first, new Node(index, v)), buf.second);
}

void remove(pNode &root, int x) {
    auto buf1 = split(root, x);
    auto buf2 = split(buf1.second, x + 1);
    root = merge(buf1.first, buf2.second);
    delete buf2.first;
}

void die(pNode &root, int id, int n) {
    auto buf1 = split(root, id);
    auto r_left = buf1.first, rx = buf1.second;

    auto buf2 = split(rx, 1);
    auto el = buf2.first, r_right = buf2.second;
    root = merge(r_left, r_right);
    int val = el->val;

    if (id != 0 && id != n - 1) {
        int v1 = val / 2, v2 = val - val / 2;
        add(root, id - 1, v1);
        add(root, id, v2);
    } else if (id == 0 && n > 1) {
        add(root, 0, val);
    } else if (id == n - 1 && n > 1) {
        add(root, n - 2, val);
    }
    delete el;
}

void div(pNode &root, int id) {
    auto buf1 = split(root, id);
    auto r_left = buf1.first, rx = buf1.second;

    auto buf2 = split(rx, 1);
    auto el = buf2.first, r_right = buf2.second;
    int val = el->val;
    int v1 = val / 2, v2 = val - val / 2;

    auto comp1 = new Node(id, v1);
    auto comp2 = new Node(id, v2);
    root = merge(merge(r_left, comp1), merge(comp2, r_right));
    delete el;
}


inline void solve() {
    int n, p; cin >> n >> p;
    pNode tree = nullptr;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        insert(tree, i, x);
    }

    int k; cin >> k;
    cout << sqsum(tree) << $;
    while (k--) {
        int t, id; cin >> t >> id; id--;
        if (t == 1) {
            die(tree, id, n);
            n--;
        } else if (t == 2) {
            div(tree, id);
            n++;
        } else {
            trip(tree);
        }
        //int i, v; cin >> i >> v;
        //add(tree, i - 1, v);
        cout << sqsum(tree) << $;
    }
}
/*
4 0
3 5 5 4
5
1 1
2 1
1 3
2 2
1 3

*/



