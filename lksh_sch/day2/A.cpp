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


inline void solve();
signed main() {
    solve();
    cout.flush();
    return 0;
}

inline void stress() {
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
    int x, y;
    Node *left, *right;
    Node(int a):
        x(a), y((rand() << 6) + rand()), 
        left(nullptr), right(nullptr)
    {}
    //int sz;
    //int add, set;
    //bool reversed;
    friend ostream &operator << (ostream &o, Node *n) {
        o << "NODE [" << n << "] " << n->x << " " << n->y << " | ";
        return o;
    }
    
};
typedef Node *pNode;

pair<Node *, Node *> split(Node *root, int x) { // <x, >=x
    if (root == nullptr) return make_pair(nullptr, nullptr);
    if (x <= root->x) {
        auto buf = split(root->left, x);
        Node *r1 = buf.first, *r2 = buf.second;
        root->left = r2;
        return make_pair(r1, root);
    } else { 
        auto buf = split(root->right, x);
        Node *r1 = buf.first, *r2 = buf.second;
        root->right = r1;
        return make_pair(root, r2);            
    }
}
    
Node *merge(Node *r1, Node *r2) {
    if (r1 == nullptr) return r2;
    if (r2 == nullptr) return r1;
    if (r1->y <= r2->y) {
        r1->right = merge(r1->right, r2);
        return r1;
    } else {
        r2->left = merge(r1, r2->left);
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
    Node *r1 = buf.first, *r2 = buf.second;
    r1 = merge(r1, new Node(x));
    root = merge(r1, r2);
}

void insert(pNode &root, pNode nw) {
    if (exists(root, nw->x)) return;
    if (root == nullptr) root = nw;
    else if (nw->y < root->y) {
        auto buf = split(root, nw->x);
        nw->left = buf.first, nw->right = buf.second;
        root = nw;
    } else
        insert(nw->x < root->x ? root->left : root->right, nw);
}

void remove(pNode &root, int x) {
    if (root == nullptr) return;
    if (root->x == x)
        root = merge(root->left, root->right);
    else
        remove(x < root->x ? root->left : root->right, x);
}

int next(pNode &root, int x) {
    auto buf = split(root, x + 1);
    Node *r1 = buf.first, *r2 = buf.second;
    Node *min = r2;
    int ans = INF;
    if (min != nullptr) {
        while (min->left != nullptr) min = min->left;
        ans = min->x;
    }
    root = merge(r1, r2);
    return ans;
}

int prev(pNode &root, int x) {
    auto buf = split(root, x);
    Node *r1 = buf.first, *r2 = buf.second;
    Node *max = r1;
    int ans = INF;
    if (max != nullptr) {
        while (max->right != nullptr) max = max->right;
        ans = max->x;
    }
    root = merge(r1, r2);
    return ans;
}

inline void solve() {
//*
    freopen("bst.in", "r", stdin);
    freopen("bst.out", "w", stdout);
//*/    
    srand(time(NULL));
    Node *tree = nullptr;
    while (!feof(stdin)) {
        str s; int x;
        cin >> s >> x;
        if (s == "insert") {
//            insert(tree, x);
            insert(tree, new Node(x));
        } else if (s == "delete") {
            remove(tree, x);
        } else if (s == "exists") {
            cout << to_ans(exists(tree, x)) << $$;
        } else if (s == "next") {
            cout << to_ans(next(tree, x)) << $$;
        } else if (s == "prev") {
            cout << to_ans(prev(tree, x)) << $$;
        }
      //  cout << ": " << (int)tree << $$;
    }
}
/*

insert 10
insert 20
insert 15
insert 25
insert 5
insert 4
exists 10
exists 20
exists 15
exists 25
exists 5
exists 4
delete 5
exists 10
exists 20
exists 15
exists 25
exists 5
exists 4



*/


