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

class error final : public exception {
    const char *m = 0;
    public:
        error(const char *m): m(m) {}
        const char *what() const noexcept { return m; }
};

template <typename T> istream& operator >> (istream &in, vector<T> &v) { 
    for (T &t : v) in >> t;
    return in;
}
template <typename T> ostream& operator << (ostream &out, const vector<T> &v) {
    for (const T &t : v) out << t << ' ';
    return out;
}
template <typename T> ostream& operator << (ostream &out, const pair<T, T> &v) {
    out << "{" << v.first << "; " << v.second << "}";
    return out;
}


inline void solve();
signed main() {
/*
    freopen("piglet.in", "r", stdin);
    freopen("piglet.out", "w", stdout);
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
template <class T> T sqr(T x) { return x * x; };
const ld EPS = 1e-9;
const ld pi = acos(-1.0);

template <class T> struct Vector {
    T x, y;
    Vector(T x, T y) : x(x), y(y) {}
    Vector() : x(0), y(0) {}
    ld length() const { return sqrt(sqr(x) + sqr(y)); }
    ld size() const { return sqrt(sqr(x) + sqr(y)); }
    T len2() const { return sqr(x) + sqr(y); }
    friend T abs(const Vector &v) { return v.length(); }

    Vector<ld> toUnit() const { 
        if (length() < EPS) return Vector<ld>();
        return Vector<ld>(x, y) * (1 / length()); 
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
    
    Vector operator - ()     const { return Vector(-x, -y); }
    Vector operator * (T m)  const { return Vector(x * m, y * m); } 
    T dot  (const Vector &v) const { return x * v.x + y * v.y; }
    T cross(const Vector &p) const { return x * p.y - p.x * y;  }

    ld angle(const Vector &v) const {
        return atan2(cross(v), dot(v));
    }
    ld dist(const Vector &r) const { 
        return sqrt(sqr(x - r.x) + sqr(y - r.y));
    }
    ld dist(const Line<T> &l) const { 
        return (l.a * x + l.b * y + l.c) / sqrt(sqr(l.a) + sqr(l.b));
    }
    Vector rotated(ld alpha) {
        return Vector(
            x * cos(alpha) + y * sin(alpha),
            y * cos(alpha) - x * sin(alpha)
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
//        out << "(" << p.x << "; " << p.y << ")";
        out << p.x << " " << p.y;
        return out;
    }
    
    bool valid() const {
        return !isnan(x) && !isnan(y);
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
    friend ostream& operator << (ostream &out, const Line<T> &l) {
        out << l.a << "x + " << l.b << "y + " << l.c;
        return out;
    }
};

ld getArc(Point<ld> a, Point<ld> b, Point<ld> c, int r) {
    // c - center
    ld alpha = (a - c).angle(b - c);
    return abs(alpha) * r;
}

pair<Point<ld>, Point<ld>> getTangent(Point<ld> p, Point<ld> c, int r) {
    ld d = p.dist(c);
/*
    ld alpha = asin(r / d);
    auto m1 = p + (c - p).rotated(+alpha) * cos(alpha);
    auto m2 = p + (c - p).rotated(-alpha) * cos(alpha);
    //*/
    ld cos_a = r / d;
    ld alpha = acos(cos_a);
    auto m1 = c + (p - c).rotated(+alpha) * cos_a;
    auto m2 = c + (p - c).rotated(-alpha) * cos_a;
    
    return {m1, m2};
}

bool check(Point<ld> p1, Point<ld> p2, Point<ld> c, int r) {
//    VAR(Line<ld>(p1, p2));
//    VAR(c.dist(Line<ld>(p1, p2)));
    if (abs(c.dist(Line<ld>(p1, p2))) >= r) return false;
/*
    ld a2 = (p1 - p2).len2();
    ld b2 = (p1 - c).len2();
    ld c2 = (p2 - c).len2();
    if (a2 >= b2 + c2) {
        return true;
    } else {
        return b2 < a2 + c2 && c2 < a2 + b2;
    }//*/
    c -= p1;
    p2 -= p1;
    p1 -= p1;
    
    ld alpha = atan2(p2.y, p2.x);
    
    p2 = p2.rotated(alpha);    
    c = c.rotated(alpha);
    ld h = abs(c.y);
    ld l = sqrt(r * r - h * h);    

    ld x1 = c.x - l, x2 = c.x + l;
    if (max(p1.x, p2.x) <= x1 || min(p1.x, p2.x) >= x2)
        return false;
    return true;
}

inline void solve() {
    cout << setprecision(50);
    Point<ld> w, r, c; cin >> w >> r >> c;
    int R; cin >> R;
    
    if (!check(w, r, c, R)) {
        cout << w.dist(r) << $;
        return;
    }

    auto getRange = [=] (Point<ld> t1, Point<ld> t2) {        
        return w.dist(t1) + getArc(t1, t2, c, R) + t2.dist(r);
    };

    auto wp = getTangent(w, c, R);
    auto rp = getTangent(r, c, R);
    /*
    VAR(wp); VAR(rp);
    VAR(getRange(wp.fir, rp.fir));
    VAR(getRange(wp.fir, rp.sec));
    VAR(getRange(wp.sec, rp.fir));
    VAR(getRange(wp.sec, rp.sec));
//*/


    ld ans = min({
        getRange(wp.fir, rp.fir),
        getRange(wp.fir, rp.sec),
        getRange(wp.sec, rp.fir),
        getRange(wp.sec, rp.sec)
    });
    cout << ans << $;

}
/*
0 0
32000 32000
16000 16000
1


0 0 0 1
10 10 1


5 0 0 5
0 0 5


-5 0 5 0
0 0 3


0 0 10 0
5 5 1
*/

