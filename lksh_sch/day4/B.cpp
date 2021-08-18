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


inline void solve();
signed main() {
/*
    freopen("network.in", "r", stdin);
    freopen("network.out", "w", stdout);
//*/
    int t = 1;
   // cin >> t; 
    while (t--) {
        solve();
    }
    cout.flush();
    cerr << "\nTime: " << setprecision(2) <<
        int(1000 * (double)clock() / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}

inline void stress() {
}
////////////////////////////////////////////////////////////////////////////////

template <class T> T rmin(T &a, const T &b) { return (a = min(a, b)); }
template <class T> T rmax(T &a, const T &b) { return (a = max(a, b)); }
template <class T> T reql(T &a, const T &b) { return (a = b); }



inline void solve() {
    int n; cin >> n;
    veci w(n); cin >> w;
    int s = accumulate(all(w), 0ll);
    int sl = 1 << (n / 2);
    int sr = 1 << (n - n / 2);
    
    veci wl(sl);
    veci wr(sr);
    for (int mask = 0; mask < sl; mask++)
      for (int j = 0; j < n / 2; j++)
        if (mask & (1 << j))
          wl[mask] += w[j];
    for (int mask = 0; mask < sr; mask++)
      for (int j = 0; j < n - n / 2; j++)
        if (mask & (1 << j))
          wr[mask] += w[j + n / 2];    

    sort(all(wl));
    sort(all(wr));
   
    int left = 0, right = sr - 1;
    int cur = -1e12;
    int volume = s / 2;
    while (left < sl && right >= 0) {
        if (wl[left] + wr[right] <= volume) {
            cur = max(cur, wl[left] + wr[right]);
            left++;
        } else {
            right--;
        }
    }
    cout << abs((s - cur) - cur);    
}
/*
5
46 25 62 11 45
*/
