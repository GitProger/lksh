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


inline void solve();
signed main() {
    solve();
    cout.flush();
    cerr << "\nTime: " << setprecision(2) <<
        int(1000 * (double)clock() / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}

inline void stress() {
}
////////////////////////////////////////////////////////////////////////////////

str toBinStr(int x) {
    str res;
    while (x > 0) {
        res += '0' + (x % 2);
        x /= 2;
    }
    while (len(res) < 32) res += '0';
    reverse(all(res));
    return res;
}

int binToInt(const str &a) {
    int r = 0;
    for (char c : a) r = (r << 1) + (c - '0');
    return r;
}

class Bor {
    private:
        struct vertex {
            std::map<char, vertex *> next;
            bool end = false;
            int subset_sz = 0;
        };
        vertex *root;
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
            cur->end = true;
        }
        void remove(const str &a) {
            vertex *cur = root;
            for (char c : a) {
                if (!cur->next[c]) return;
                cur->subset_sz--;
                cur = cur->next[c];
            }
            cur->subset_sz--;
            cur->end = false;
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
        int get(const str &a) {
            str optimal_ans;
            vertex *cur = root;
            for (char c : a) {
                char to_opt = '0' + '1' - c;
                if (cur->next[to_opt] == nullptr || cur->next[to_opt]->subset_sz == 0) 
                    to_opt = c;
                if (cur->next[to_opt] == nullptr) return -1;
                optimal_ans += to_opt;
                cur = cur->next[to_opt];
            }
            return binToInt(a) ^ binToInt(optimal_ans);
        }
};


inline void solve() {
    int q; cin >> q;
    Bor b; b.add(toBinStr(0));
    for (int i = 0; i < q; i++) {
        char c; cin >> c;
        int x; cin >> x;
        str s = toBinStr(x);
        if (c == '+') {
            b.add(s);
        } else if (c == '-') {
            b.remove(s);
        } else if (c == '?') {
            cout << b.get(s) << $;
        }
    }
}
/*

8
+ 8
+ 9
+ 11
+ 6
+ 1
? 3
- 8
? 3

*/

