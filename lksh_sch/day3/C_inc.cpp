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
const int MOD = 1000000007;//1000000000000000009;
veci power(100010, 1);

int hashed(const str &s) {
    int h = 0;
    for (int i = 0; i < len(s); i++) {
        h += s[i] * power[len(s) - 1 - i];
        h %= MOD;
    }
    return h;
}
int hashed(char c) {
    return hashed(str(1, c));
}

int merge(int h1, int h2, int len2) {
    return (h1 * power[len2] + h2) % MOD;
}



typedef struct Node {
    int l = -1, r = -1;
    int hash = 0, ln = 0, hashrev = 0;
    Node *left = nullptr, *right = nullptr;
    Node(int _l, int _r): l(_l), r(_r) {}
    Node(int _l, int _r, const str &s): 
        l(_l), r(_r), 
        hash(hashed(s)), ln(len(s)), hashrev(hashed(reversed(s)))
    {}
} *pNode;


void upd(pNode v) {
    v->ln = v->left->ln + v->right->ln;
    v->hash    = merge(v->left->hash , v->right->hash, v->right->ln);
    v->hashrev = merge(v->right->hashrev, v->left->hashrev , v->left->ln);
}

void build(pNode &v, int l, int r, const str &a) {
    int m = (l + r) / 2;
    v = new Node(l, r);
    if (l < r) {
        build(v->left, l, m, a);
        build(v->right, m + 1, r, a);
        upd(v);
    } else {
        v->hash = v->hashrev = hashed(a[l]);
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
        v->hash = v->hashrev = hashed(val);
        return;
    }
    setv(v->left, pos, val);
    setv(v->right, pos, val);
    upd(v);
}

prii get(pNode v, int l, int r) { // hash, hashrev
    if (v == nullptr) return {0, 0};
    if (l > r || l > v->r || v->l > r) return {0, 0};
    if (l <= v->l && v->r <= r) {
        return {v->hash, v->hashrev};
    }
    prii h1 = get(v->left , l, r);
    prii h2 = get(v->right, l, r);
    int len1 = v->left->ln;
    int len2 = v->right->ln;
    return {
        merge(h1.first, h2.first, len2),
        merge(h2.second, h1.second, len1)
    };
}

int check(pNode v, int l, int r) {
    int m = (l + r) / 2;
    if ((r - l + 1) % 2 == 0) {
        return get(v, l, m).first == get(v, m + 1, r).second;
    } else {
        return get(v, l, m - 1).first == get(v, m + 1, r).second;
    }
}

void trip(Node *root) {
    if (root == nullptr) return;
    cout << root << ": "
         << root->left << " " << root->right << " | "
         << "[" << root->l << "; " << root->r << "] " 
         << root->hash << " " << root->hashrev << " " << root->ln << endl;
    trip(root->left);
    trip(root->right);
}

inline void solve() {
    str a; cin >> a;
    int m; cin >> m;

    for (int i = 1; i < len(power); i++)
        power[i] = (power[i - 1] * HASH_BASE) % MOD;

    pNode tree = nullptr;
    build(tree, a);

    while (m--) {
        str s; cin >> s;
        if (s == "change") {
            int p; char c;
            cin >> p >> c; --p;
            setv(tree, p, c);
        } else if (s == "palindrome?") {
            int l, r; cin >> l >> r; --l; --r;
            cout << (check(tree, l, r) ? "Yes" : "No") << $;
        } else {
            trip(tree);
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


*/
