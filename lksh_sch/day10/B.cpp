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

#define VAR(a) cerr<<#a<<": "<<a<<'\n'
#define VAR2(a,b) cerr<<#a<<": "<<a<<' '<<#b<<": "<<b<<'\n'
#define VAR3(a,b,c) cerr<<#a<<": "<<a<<' '<<#b<<": "<<b<<' '<<#c<<": "<<c<<'\n'
#define VAR4(a,b,c,d) cerr<<#a<<": "<<a<<' '<<#b<<": "<<b<<' '<<#c<<": "<<c<<' '<<#d<<": "<<d<<'\n'

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
/*
    freopen("2sat.in", "r", stdin);
    freopen("2sat.out", "w", stdout);
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

template <class T> struct Line;
const ld EPS = 1e-9;

template <class T> struct Vector {
    T x, y;
    static T sqr(T x) { return x * x; };
    Vector(T x, T y) : x(x), y(y) {}
    Vector() : x(0), y(0) {}
    T length() const { return sqrt(sqr(x) + sqr(y)); }
    T size() const { return sqrt(sqr(x) + sqr(y)); }
    T len2() const { return sqr(x) + sqr(y); }
    pair<T, T> toPair() const { return make_pair(y, x); }
    friend T abs(const Vector &v) { return v.length(); }

    Vector toUnit() const { 
        if (length() < EPS) return Vector();
        return Vector(x, y) * (1 / length()); 
    }
    

    bool operator == (const Vector &v) const { 
        return abs(x - v.x) < EPS && abs(y - v.y) < EPS;
    }
    Vector operator + (const Vector &x) const {
        return Vector(this->x + x.x, this->y + x.y); 
    }
    Vector operator - (const Vector &x) const { 
        return Vector(this->x - x.x, this->y - x.y); 
    }
    
    Vector operator - ()           const { return Vector(-x, -y); }
    Vector operator * (T m)        const { return Vector(x * m, y * m); } 
    T dot  (const Vector &v) const { return x * v.x + y * v.y; }
    T cross(const Vector &p) const { return x * p.y - p.x * y;  }

    T angle(const Vector &v) const { 
        return acos(this->operator*(v) / this->length() / v.length());
    }
    T dist(const Vector &r) const { 
        return sqrt(sqr(x - r.x) + sqr(y - r.y));
    }
    T dist(const Line<T> &l) const { 
        return (l.a * x + l.b * y + l.c) / sqrt(l.a, l.b);
    }
    Vector rotated(ld alpha) {
        return Vector(
            x * cos(alpha) - y * sin(alpha),
            x * sin(alpha) + y * cos(alpha)
        );
    }
    bool operator < (const Vector &v) const {
        return toPair() < v.toPair();
    }
    
    friend istream& operator >> (istream &in, Vector<T> &p) {
        in >> p.x >> p.y;
        return in;
    }
    friend ostream& operator << (ostream &out, const Vector<T> &p) {
        out << "(" << p.x << "; " << p.y << ")";
        return out;
    }
};
template<class T> using Point = Vector<T>;


template <class T> struct Line {
    T a, b, c;
    Line(T a, T b, T c) : a(a), b(b), c(c) {}
    Line(const Point<T> &p1, const Point<T> &p2) :
        a(p2.y - p1.y), b(p1.x - p2.x)
    { c = -(a * p1.x + b * p1.y); }

    bool have(const Point<T> &p) const {
        return a * p.x + b * p.y + c == 0;
//        return abs(a * p.x + b * p.y + c) < EPS;
    }
    T value(Point<T> p) const { return a * p.x + b * p.y + c; }
    ld Y(T x) const  { return (-c - a * x) / b; }
    ld X(T y) const  { return (-c - b * y) / a; }
    friend ostream& operator << (ostream &out, const Line<T> &l) {
        out << l.a << "x + " << l.b << "y + " << l.c;
        return out;
    }    
};

inline void solve() {
    int n, m, k; cin >> n >> m >> k;
    vec<Point<int>> f(n); cin >> f;
    vec<Point<int>> missile(m); cin >> missile;

    auto angle = [=] (const Point<int> &a, const Point<int> &b, const Point<int> &c) {
        return (b - a).cross(c - b);
    };

    int ans = 0;
    for (auto p : missile) {
        if (angle(f[0], f[1], p) < 0 || angle(f[0], f[n - 1], p) > 0) continue;
        int l = 0, r = n - 1;
        while (l + 1 < r) {
            int mid = (l + r) / 2;
            ((angle(f[0], f[mid], p) < 0) ? r : l) = mid;
        }
        ans += angle(f[l], f[r], p) >= 0;
    }

    cout << ((ans >= k) ? "YES" : "NO") << $;
}
/*
5 4 2
1 -1
1 2
0 4
-1 2
-1 -1
-2 -1
1 -1
0 1
2 3



*/

