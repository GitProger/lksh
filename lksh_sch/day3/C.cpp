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

template <typename T> ostream& operator << (ostream &out, const pair<T, T> &v) {
    cout << "{" << v.first << "; " << v.second << "}";
    return out;
}


inline void solve();
signed main() {
    freopen("substring-palindromes.in", "r", stdin);
    freopen("substring-palindromes.out", "w", stdout);
    solve();
    cout.flush();
    cerr << "\nTime: " << setprecision(2) <<
        int(1000 * (double)clock() / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}

inline void stress() {
}
////////////////////////////////////////////////////////////////////////////////

int sqr(int a) { 
    return a * a; 
}
str reversed(str a) {
    reverse(all(a));
    return a;
}


const int HASH_BASE = 133;
const int MOD = 1'000'000'007;
const int MAX_SIZE = 100'100;
veci power(MAX_SIZE, 1);

int hashed(const str &s) {
    int h = 0;
    for (int i = 0; i < len(s); i++) {
        h += s[i] * power[i] % MOD;
        h %= MOD;
    }
    return h;
}
int hashed(char c) {
    return hashed(str(1, c));
}

int merge(int h1, int h2, int len2) {
    return (h1 * power[len2] % MOD + h2) % MOD;
}

typedef struct Node {
    int l = -1, r = -1;
    int hash = 0, ln = 0;
    Node *left = nullptr, *right = nullptr;
    Node(int l, int r): l(l), r(r) {}
    Node(int l, int r, const str &s): 
        l(l), r(r), hash(hashed(s)), ln(len(s))
    {}
} *pNode;


int geth(pNode v) {
    if (v == nullptr) return 0;
    return v->hash;
}
int getl(pNode v) {
    if (v == nullptr) return 0;
    return v->ln;
}

void upd(pNode v) {
    v->ln = getl(v->left) + getl(v->right);
    v->hash = merge(geth(v->left), geth(v->right), getl(v->right));
}

void build(pNode &v, int l, int r, const str &a) {
    int m = (l + r) / 2;
    v = new Node(l, r);
    if (l < r) {
        build(v->left, l, m, a);
        build(v->right, m + 1, r, a);
        upd(v);
    } else {
        v->hash = hashed(a[l]);
        v->ln = 1;
    }
}
void build(pNode &v, const str &a) {
    build(v, 0, len(a) - 1, a);
}

void setv(pNode v, int pos, char val) {
    if (v == nullptr) return;
    if (pos < v->l || pos > v->r) return;
    if (v->l == v->r) {
        v->hash = hashed(val);
        return;
    }
    setv(v->left, pos, val);
    setv(v->right, pos, val);
    upd(v);
}

pair<int, int> get(pNode v, int l, int r) {
    if (v == nullptr) return {0, 0};
    if (l > r || l > v->r || v->l > r) return {0, 0};
    if (l <= v->l && v->r <= r) return {v->hash, v->ln};
    
    auto q1 = get(v->left, l, r);
    auto q2 = get(v->right, l, r);
    
    int last_len = q1.second + q2.second;
    int hash_last = merge(q1.first, q2.first, q2.second);
    return {hash_last, last_len};
}

bool check(pNode v1, pNode v2, int l, int r, int n) {
    return get(v1, l, r).first == get(v2, n - 1 - r, n - 1 - l).first;
}

void trip(pNode root) {
    if (root == nullptr) return;
    cout << root << ": "
         << root->left << " " << root->right << " | "
         << "[" << root->l << "; " << root->r << "] " 
         << root->hash << " " << root->ln << endl;
    trip(root->left);
    trip(root->right);
}

inline void solve() {
    str a; cin >> a;
    int m; cin >> m;
    int n = len(a);

    for (int i = 1; i < len(power); i++)
        power[i] = (power[i - 1] * HASH_BASE) % MOD;

    pNode tree1 = nullptr;
    pNode tree2 = nullptr;
    build(tree1, a);
    build(tree2, reversed(a));

    while (m--) {
        str s; cin >> s;
        if (s == "change") {
            int p; char c;
            cin >> p >> c; --p;
            setv(tree1, p, c);
            setv(tree2, n - 1 - p, c);
        } else if (s == "palindrome?") {
            int l, r; cin >> l >> r; --l; --r;
            cout << (check(tree1, tree2, l, r, n) ? "Yes" : "No") << $;
        } else if (s == "trip") {
            trip(tree1);
            cout << "--------------\n";
            trip(tree2);
        } else if (s == "get") {
            int l, r; cin >> l >> r; --l; --r;
            cout << "straight: " << get(tree1, l, r) << $;
            cout << "reversed: " << get(tree2, n - 1 - r, n - 1 - l) << $;
        }
    }
}
/*
abcda
5
palindrome? 1 5
palindrome? 1 1
change 4 b
palindrome? 1 5
palindrome? 2 4


abacaba
1
palindrome? 1 3

*/
