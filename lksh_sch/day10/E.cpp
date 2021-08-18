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

template <class T> struct Vector {
    T x, y;
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
        return acos(this->dot(v) / (ld)this->length() / (ld)v.length());
    }
    T dist(const Vector &r) const { 
        return sqrt(sqr(x - r.x) + sqr(y - r.y));
    }
    T dist(const Line<T> &l) const { 
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
};


template <class T> Line<T> getInterLine(Point<T> c1, T r1, Point<T> c2, T r2) {
    int a = 2 * (c2.x - c1.x);
    int b = 2 * (c2.y - c1.y);
    int c = sqr(c1.x) - sqrt(c2.x) + sqr(c1.y) - sqr(c2.y) + sqr(r2) - sqr(r1);
    return Line<T>(a, b, c);
}

const ld pi = acos(-1.0);
inline void solve() {
    cout.precision(100);
    Point<ld> c1, c2;
    int r1, r2;
    cin >> c1 >> r1;
    cin >> c2 >> r2;

    ld a = c1.dist(c2), b = abs(ld(r1)), c = abs(ld(r2));

    if (c1 == c2 && r1 == r2) {
        cout << 3 << $;
        return;
    }

    if (a > b + c || b > a + c || c > a + b) {
        cout << 0 << $;
        return;
    }
    
    ld alpha = atan2((c2 - c1).y, (c2 - c1).x);

    auto shift = c1;    

    c1 -= shift;
    c2 -= shift;    
    c1 = c1.rotated(alpha);    
    c2 = c2.rotated(alpha);    

    ld p = (a + b + c) / 2.0;
    ld h = 2.0 * sqrt(p * (p - a) * (p - b) * (p - c)) / a;
    ld x = c1.x + sqrt(sqr(r1) - sqr(h));
    Point<ld> ans1(x, h);
    Point<ld> ans2(x, -h);

    
    ans1 = ans1.rotated(-alpha);    
    ans2 = ans2.rotated(-alpha);    
    ans1 += shift;
    ans2 += shift;

    if (ans1 == ans2) {
        cout << 1 << $;
        cout << ans1 << $;
    } else {
        cout << 2 << $;
        cout << min(ans1, ans2) << $;
        cout << max(ans1, ans2) << $;
    }

}
/*
3 4 5
9 4 2


*/

