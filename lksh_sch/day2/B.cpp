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
template <typename T> ostream& operator << (ostream &out, const set<T> &v) {
    for (const T &t : v) out << t << ' ';
    return out;
}

mt19937 rnd(1234);
inline void solve();
signed main() {
 
    freopen("sum2.in", "r", stdin);
    freopen("sum2.out", "w", stdout);

    solve();
    cout.flush();
    cerr << "\nTime: " << setprecision(2) <<
        int(1000 * (double)clock() / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

string to_ans(bool a) {
    return a ? "true" : "false";
}

string to_ans(int x) {
    if (x == INF) return "none";
    return to_string(x);
}

struct Node {
    int x, y, sz, sum;
    Node *left, *right;
    Node(int a):
        x(a), y(rnd()), sz(1), sum(a),
        left(nullptr), right(nullptr)
    {}
};
typedef Node *pNode;

int size(Node *r) { return r != nullptr ? r->sz : 0; }
int sum(Node *r) { return r != nullptr ? r->sum : 0; }

void upd(Node *r) {
    if (r == nullptr) return;
    r->sz = size(r->left) + 1 + size(r->right);
    r->sum = sum(r->left) + r->x + sum(r->right);
}

pair<pNode, pNode> split(pNode root, int x) { // <x, >=x
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

bool exists(Node *root, int x) {
    if (root == nullptr) return false;
    if (x < root->x) {
        if (root->left != nullptr)
            return exists(root->left, x);
        else
            return false;
    } else if (x > root->x) {
        if (root->right != nullptr)
            return exists(root->right, x);
        else
            return false;
    } else
        return true;
}

void insert(pNode &root, int x) {
    if (exists(root, x)) return;
    auto buf = split(root, x);
    root = merge(merge(buf.first, new Node(x)), buf.second);
}

int sum(pNode &root, int l, int r) {
    auto buf = split(root, l);
    pNode r1 = buf.first, r2 = buf.second;

    auto buf2 = split(r2, r + 1);
    pNode r12 = buf2.first, r22 = buf2.second;
    int ans = sum(r12);
    
    r2 = merge(r12, r22);
    root = merge(r1, r2);

    return ans;
}

inline void solve() {
    int n; cin >> n;
    Node *tree = nullptr;
    int lastAns = -1, MOD = 1e9;
    while (n--) {
        str s; cin >> s;
        if (s == "+") {
            int x; cin >> x;
            if (lastAns != -1) {
                x = (x + lastAns + MOD) % MOD;
                lastAns = -1;
            }
            insert(tree, x);
        } else if (s == "?") {
            int l, r; cin >> l >> r;
            lastAns = sum(tree, l, r);
            cout << lastAns << $;
        }
    }
}
/*
6
+ 1
+ 3
+ 3
? 2 4
+ 1
? 2 4

*/


