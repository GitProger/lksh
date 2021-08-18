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

mt19937 rnd(1234);
inline void solve();
signed main() {
 //   freopen("kthmax.in", "r", stdin);
 //   freopen("kthmax.out", "w", stdout);

    solve();
    cout.flush();
    return 0;
}

inline void stress() {
}
////////////////////////////////////////////////////////////////////////////////

struct Node {
    int x, y, sz;
    Node *left, *right;
    Node(int a):
        x(a), y(rnd()), sz(1),
        left(nullptr), right(nullptr)
    {}
};
typedef Node *pNode;

int size(Node *r) {
    return r != nullptr ? r->sz : 0;
}

void upd(Node *r) {
    if (r == nullptr) return;
    r->sz = size(r->left) + 1 + size(r->right);
}

pair<Node *, Node *> split(Node *root, int x) { // <x, >=x
    if (root == nullptr) return make_pair(nullptr, nullptr);
    if (x <= root->x) {
        auto buf = split(root->left, x);
        Node *r1 = buf.first, *r2 = buf.second;
        root->left = r2;
        upd(root);
        return make_pair(r1, root);
    } else { 
        auto buf = split(root->right, x);
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
    if (exists(root, x)) return;
    auto buf = split(root, x);
    root = merge(merge(buf.first, new Node(x)), buf.second);
}

void remove(pNode &root, int x) {
/*    if (root->x == x)
        root = merge(root->left, root->right);
    else {
        root->sz--;
        remove(x < root->x ? root->left : root->right, x);
	}*/
    auto buf1 = split(root, x);
    auto buf2 = split(buf1.second, x + 1);
    root = merge(buf1.first, buf2.second);
}

int k_max(pNode root, int cnt) {
    if (root == nullptr) return -1;
    if (size(root->right) >= cnt)
        return k_max(root->right, cnt);
    else if (size(root->right) == cnt - 1)
        return root->x;
    else 
        return k_max(root->left, cnt - 1 - size(root->right)); 
}

void trip(Node *root) {
    if (root == nullptr) return;
    cout << root << " [" << size(root) << "]: "
         << root->left << " " << root->right << " | "
         << root->x << " " << root->y
         << $;
    trip(root->left);
    trip(root->right);
}

inline void solve() {
    int n; cin >> n;
    Node *tree = nullptr;
    while (n--) {
        str s; int x;
        cin >> s >> x;
        if (s == "+1") {
            insert(tree, x);
        } else if (s == "-1") {
            remove(tree, x);
        } else if (s == "0") {
            cout << k_max(tree, x) << $;
        } else if (s == "t") {
            trip(tree);
        }
    }
}
/*
11
+1 5
+1 3
+1 7
0 1
0 2
0 3
-1 5
+1 10
0 1
0 2
0 3



*/
