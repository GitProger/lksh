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
    int index = 0;
    static T sqr(T x) { return x * x; };
    Vector(T x, T y) : x(x), y(y) {}
    Vector(T x, T y, int i) : x(x), y(y), index(i) {}
    Vector() : x(0), y(0) {}
    ld length() const { return sqrt(sqr(x) + sqr(y)); }
    ld size() const { return sqrt(sqr(x) + sqr(y)); }
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
    Vector operator += (const Vector &x) {
        this->x += x.x, this->y += x.y;
        return *this;
    }
    Vector operator -= (const Vector &x) { 
        this->x -= x.x, this->y -= x.y;
        return *this;
    }
    
    Vector operator - ()           const { return Vector(-x, -y); }
    Vector operator * (T m)        const { return Vector(x * m, y * m); } 
    T dot  (const Vector &v) const { return x * v.x + y * v.y; }
    T cross(const Vector &p) const { return x * p.y - p.x * y;  }

    ld angle(const Vector &v) const { 
        return acos(this->operator*(v) / this->length() / v.length());
    }
    ld dist(const Vector &r) const { 
        return sqrt(sqr(x - r.x) + sqr(y - r.y));
    }
    ld dist(const Line<T> &l) const { 
        return abs((l.a * x + l.b * y + l.c) / sqrt(l.a, l.b));
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

int trianAreaX2(const Point<int> &a, const Point<int> &b, const Point<int> &c) {
    auto v1 = a - b;
    auto v2 = c - b;
    return v1.cross(v2);
}

ld square(const vector<Point<int>> &fig) {
    int n = len(fig);
    int s = 0;
    for (int i = 0; i < n; ++i) {
        auto p1 = fig[i];
        auto p2 = fig[(i + 1) % n];
        s += trianAreaX2({0, 0}, p1, p2);
    }
    return ld(abs(s)) / 2.0;
}

ld perimeter(const vector<Point<int>> &fig) {
    int n = len(fig);
    ld p = 0.0;
    for (int i = 0; i < n; i++) {
        auto p1 = fig[(n + i - 1) % n];
        auto p2 = fig[i];
        p += p1.dist(p2);
    }
    return p;
}


vector<Point<int>> convexHull(const vec<Point<int>> &points) {
    Point<int> mn = *min_element(all(points));

    vector<Point<int>> ps;
    for (auto p : points) {
        if (p.x != mn.x || p.y != mn.y) {
            ps.emplace_back(p.x - mn.x, p.y - mn.y);
            ps.back().index = p.index;
        }
    }

    auto cmp = [=] (const Point<int> &a, const Point<int> &b) -> bool {
        int c = a.cross(b);
        return c > 0 || (c == 0 && a.len2() < b.len2());
    };

    stable_sort(all(ps), cmp);
    vec<Point<int>> convex;
    convex.emplace_back(0, 0, mn.index);

    for (auto p : ps) {
        while (len(convex) > 1 && ((
                convex[len(convex) - 1] - convex[len(convex) - 2]
            ).cross(
                p - convex[len(convex) - 1]
            )
        ) <= 0)
            convex.pop_back();
        convex.push_back(p);
    }


    for (auto &e : convex) e += mn;
    return convex;    
}

inline void solve() {
    int n; cin >> n;
    vec<Point<int>> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i];
        points[i].index = i + 1;
    }

    vec<Point<int>> convex = convexHull(points);

    vector<int> convex_ind;
    for (auto e : convex)
        convex_ind.push_back(e.index);
    
    cout << setprecision(48)
         << len(convex) << $
         << convex_ind << $
         << perimeter(convex) << $
         << square(convex) << $;
}
/*
5
0 0
1 1
2 2
1 0
0 1

*/

