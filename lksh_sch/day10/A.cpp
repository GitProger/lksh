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
    friend T abs(const Vector &v) { return v.length(); }

    Vector toUnit() const { 
        if (length() < EPS) return Vector();
        return Vector(x, y) * (1 / length()); 
    }
    pair<T, T> toPair() const {
        return make_pair(x, y);
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
};


bool isPointIn(Point<int> p, const vector<Point<int>> &fig) {
    int ray_y = p.y;
    int n = len(fig);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        auto p1 = fig[(n + i - 1) % n];
        auto p2 = fig[i];
        Line<int> l(p1, p2);
        int y1 = min(p1.y, p2.y), y2 = max(p1.y, p2.y);
        int x1 = min(p1.x, p2.x), x2 = max(p1.x, p2.x);
        
        if (ray_y <= y1 || ray_y > y2 || y1 == y2) continue;

//        ld x = - (l.b * ray_y + l.c) / l.a;
//        if (p.x > x) continue;
//        if (x1 - EPS <= x && x <= x2 + EPS) ans++;
        int ax = - (l.b * ray_y + l.c);
        if (l.a > 0) {
            if (p.x * l.a > ax) continue;
            if (x1 * l.a <= ax && ax <= x2 * l.a) ans++;
        } else {
            if (p.x * l.a < ax) continue;
            if (x1 * l.a >= ax && ax >= x2 * l.a) ans++;
        }        
        
/*
        if (x1 - EPS <= x && x <= x2 + EPS) cerr << "!\n";        
        cerr << "line: " << l.a << "x + " << l.b << "y + " << l.c << $; 
        cerr << "x: " << x << " [" << p1.x << "; " << p2.x << "]" << $;
        cerr << p1 << " " << p2 << $;
        cerr << "ans: " << ans << $ << $;
        //*/
    }
    return ans % 2 == 1;
}


bool onBorder(Point<int> p, const vector<Point<int>> &fig) {
    int n = len(fig);
    for (int i = 0; i < n; i++) {
        auto p1 = fig[(n + i - 1) % n];
        auto p2 = fig[i];
        if (min(p1.y, p2.y) <= p.y && p.y <= max(p1.y, p2.y))
            if (min(p1.x, p2.x) <= p.x && p.x <= max(p1.x, p2.x))
                if (Line<int>(p1, p2).have(p)) return true;
    }
    return false;
}

inline void solve() {
    int n; cin >> n;
    Point<int> p; cin >> p;
    vec<Point<int>> f(n); cin >> f;
    int ans = isPointIn(p, f) || onBorder(p, f);
    cout << (ans ? "YES" : "NO") << $;
}
/*
3 2 3
1 1
10 2
2 8

11 0 0
0 3
2 0
4 3
7 0
7 -2
9 0
11 -2
11 -3
-3 -3
-3 0
-1 0

4 0 0
-1 0
0 1
1 0
0 -1

2 0 0
0 1
0 -1


4 2 1 
0 2
2 2
2 0
0 0

*/

