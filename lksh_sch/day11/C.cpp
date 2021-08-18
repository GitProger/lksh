#include <bits/stdc++.h>
using namespace std;
//#define int ll
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


inline void solve();
signed main() {
//*
    freopen("kthstr.in", "r", stdin);
    freopen("kthstr.out", "w", stdout);
//*/
    solve();
    cout.flush();
    cerr << "\nTime: " << setprecision(2) <<
        int(1000 * (double)clock() / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}

inline void stress() {
}
////////////////////////////////////////////////////////////////////////////////


class Bor {
    private:
        struct vertex {
            std::map<char, vertex *> next;
            int end = 0;
            int subset_sz = 0;
        };
        vertex *root = nullptr;
    public:
        Bor() : root(new vertex()) {}
        void add(const str &a) {
            vertex *cur = root;
            for (char c : a) {
                if (!cur->next[c])
                    cur->next[c] = new vertex();
                cur->subset_sz++;
                cur = cur->next[c];
            }
            cur->subset_sz++;
            cur->end++;
        }
        bool find(const str &a) const {
            vertex *cur = root;
            for (char c : a) {
                if (!cur->next[c])
                    return false;
                cur = cur->next[c];
            }
            return cur->end;
        }
        str get(int k) {
            str res;
            vertex *cur = root;
            int total_sz = 0;
            for (char c = 'a'; c <= 'z'; c++) {
                if (cur->next[c] == nullptr) continue;
                int prev_sz = total_sz;
                total_sz += cur->next[c]->subset_sz;
                if (total_sz >= k) {
                    total_sz = 0;
                    k -= prev_sz;
                    cur = cur->next[c];
                    res += c;
                    c = 'a' - 1;
                }
                if (cur->end >= k) {
                    return res;
                }
                k -= cur->end;
            }
            return res;
        }
        
        
};

inline void solve() {
    int n; cin >> n;
    Bor b;
    for (int i = 0; i < n; i++) {
        str s; cin >> s;
        if (isalpha(s[0])) {
            b.add(s);
        } else {
            int x = atoi(s.c_str());
            cout << b.get(x) << $;
        }
    }
}
/*

7
pushkin
lermontov
tolstoy
gogol
gorkiy
5
1

*/

