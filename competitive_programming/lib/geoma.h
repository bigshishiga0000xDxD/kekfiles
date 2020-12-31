#include <iostream>
#include <cmath>
#include <ostream>
#include <string>
#include <vector>

using std::string;
using std::istream;
using std::ostream;
using std::vector;

const long double eps = 5e-8;
const long double pi = acos(-1);

template <typename T>
inline int sign(T x) {
    if (abs(x) < eps) {
        return 0;
    }
    else if (x > 0) {
        return 1;
    }
    else {
        return -1;
    }
}

template <typename T>
struct Point {
    T x, y;
 
    Point() {}
    Point(T _x, T _y) : x(_x), y(_y) {}

    template <typename V>
    operator Point<V>() {
        return Point <V> (static_cast <V> (x), static_cast <V> (y));
    }
 
    bool operator==(const Point <T>& s) {
        return abs(x - s.x) < eps && abs(y - s.y) < eps;
    }

    bool operator!=(const Point <T>& s) {
        return abs(x - s.x) > eps || abs(y - s.y) > eps;
    }

    bool operator<(const Point <T>& s) {
        if (abs(x - s.x) < eps) {
            return x < s.x;
        }
        else {
            return y < s.y;
        }
    }
 
    bool operator>(const Point <T>& s) {
        if (abs(x - s.x) < eps) {
            return x > s.x;
        }
        else {
            return y > s.x;
        }
    }
 
    Point operator+(const Point <T>& s) {
        return { x + s.x, y + s.y };
    }
 
    Point& operator+=(const Point <T>& s) {
        x += s.x;
        y += s.y;
        return *this;
    }
 
    operator string() {
        return "{" + to_string(x) + ", " + to_string(y) + "}";
    }
};

template <typename T>
inline bool areSame(Point <T> a, Point <T> b) {
    return abs(a.x - b.x) < eps && abs(a.y - b.y) < eps;
}

template <typename T>
inline long double distance(Point <T> a, Point <T> b) {
    return sqrt(static_cast <long double> 
        ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}
 
template <typename T>
istream& operator>> (istream& in, Point <T>& p) {
    in >> p.x >> p.y;
    return in;
}
 
template <typename T>
ostream& operator<< (ostream& out, Point <T>& p) {
    out << p.x << " " << p.y;
    return out;
}
 
template <typename T>
struct Vector {
    T x, y;
 
    Vector() {};

    template <typename V>
    Vector(Point <V> a, Point <V> b) : x(b.x - a.x), y(b.y - a.y) {}

    Vector(T a, T b) : x(a), y(b) {}
 
    inline long double len() const {
        return sqrt(x * x + y * y);
    }

    inline void normalize() {
        auto l = len();
        x /= l, y /= l;
    }

    Vector <T> operator-() {
        return { -x, -y };
    }

    Vector <T> operator+(Vector <T> v) {
        return { x + v.x, y + v.y };
    }

    Vector <T>& operator+=(Vector <T> v) {
        x += v.x, y += v.y;
        return *this;
    }

    Vector <T> operator-(Vector <T> v) {
        return { x - v.x, y - v.y };
    }

    Vector <T>& operator-=(Vector <T> v) {
        x -= v.x, y -= v.y;
        return *this;
    }

    template <typename V>
    Vector <T> operator*(V e) {
        return { x * e, y * e };
    }

    template <typename V>
    Vector <T>& operator*=(V e) {
        x *= e, y *= e;
        return *this;
    }
 
    operator string() {
        return "{" + to_string(x) + ", " + to_string(y) + "}";
    }
};


template <typename T>
Point <T> operator+(const Point <T>& p, const Vector <T>& v) {
    return { p.x + v.x, p.y + v.y };
}
 
template <typename T>
Point <T> operator-(const Point <T>& p, const Vector <T>& v) {
    return { p.x - v.x, p.y - v.y };
}
 
template <typename T>
istream& operator>> (istream& in, Vector <T>& v) {
    in >> v.x >> v.y;
    return in;
}
 
template <typename T>
ostream& operator<< (ostream& out, Vector <T>& v) {
    out << v.x << " " << v.y;
    return out;
}
 
 
template <typename T>
inline T scal(Vector <T> a, Vector <T> b) {
    return a.x * b.x + a.y * b.y;
}
 
template <typename T>
inline T pscal(Vector <T> a, Vector <T> b) {
    return a.x * b.y - a.y * b.x;
}

template <typename T>
inline long double degree(Vector <T> a, Vector <T> b) {
    return atan2(pscal <T>(a, b), scal <T>(a, b));
}

template <typename T>
struct Line {
    T a, b, c;
 
    Line() {}
    Line(T a, T b, T c) : a(a), b(b), c(c) {}
 
    template <typename V>
    Line(Point <V> a, Point <V> b) : a(a.y - b.y), b(b.x - a.x), c(a.x * b.y - b.x * a.y) {}
 
    template <typename V>
    Line(Point <V> p, Vector <V> v) {
        Point <V> e = { p.x + v.x, p.y + v.y };
        a = p.y - e.y;
        b = e.x - p.x;
        c = p.x * e.y - e.x * p.y;
    }

    template <typename V>
    inline T eval(const Point <V>& p) const {
        return a * p.x + b * p.y + c;
    }

    template <typename V>
    inline bool belongs(const Point <V>& p) const {
        return abs(a * p.x + b * p.y + c) < eps;
    }
 
    inline void normalize() {
        T t = sqrt(a * a + b * b);
        a /= t, b /= t, c /= t;
    }
 
    inline T getY(const T x) const {
        if (b) {
            return (a * x + c) / (-b);
        }
        else {
            return 0;
        }
    }
    inline T getX(const T y) const {
        if (a) {
            return (b * y + c) / (-a);
        }
        else {
            return 0;
        }
    }

    inline Point <T> getPoint() const {
        return {
            - a * c / (a * a + b * b),
            - b * c / (a * a + b * b)
        };
    }
};
 
template <typename T>
vector <Point <T>> intersect(Line <T>& a, Line <T>& b) {
    T t = a.a * b.b - b.a * a.b; 
    if (abs(t) < eps) {
        return { };
    }
    else {
        return {{
            (b.c * a.b - a.c * b.b) / t,
            (b.a * a.c - a.a * b.c) / t
        }};
    }
}

template <typename T>
Point <T> findProjection(Point <T> p, Line <T> l) {
    T dist = l.eval(p) / sqrt(l.a * l.a + l.b * l.b);

    Vector <T> v = { l.a, l.b };
    v.normalize();
    v *= dist;

    if (l.belongs(p + v)) {
        return p + v;
    }
    else {
        return p - v;
    }
}
 
template <typename T>
bool onBeam(Point <T> P1, Point <T> P2, Point <T> P) {
    if (abs(pscal <T>({ P1, P }, { P1, P2 })) > eps) {
        return false;
    }
    if (scal <T>({ P1, P }, { P2, P }) - eps <= 0 ||
        scal <T>({ P1, P2 }, { P2, P }) + eps >= 0) {
        return true;
    }
    return false;
}
 
template <typename T>
bool insideAngle(Point <T> a, Point <T> o, Point <T> b, Point <T> p) {
    // fix for real numbers
    if (onBeam(o, a, p) || onBeam(o, b, p)) {
        return true;
    }
 
    if (pscal <T>({ o, a }, { o, b }) < 0) {
        swap(a, b);
    }
 
    if (pscal <T>({ o, a }, { o, p }) > 0 && pscal <T>({ o, p }, { o, b }) > 0) {
        return true;
    }
    return false;
}


template <typename T>
vector <Point <T>> _convexHull(typename vector <Point <T>> :: iterator __first,
       typename vector <Point <T>> :: iterator __last) {
    vector <Point <T>> res;

    for (; __first < __last; __first++) {
        while (res.size() >= 2) {
            Point <T> q = res.back();
            Point <T> w = res[res.size() - 2];
            Point <T> e = *__first;
            if (pscal<T>({ q, w }, { q, e }) >= 0) {
                res.pop_back();
            }
            else {
                break;
            }
        }
        res.push_back(*__first);
    }
    return res;
}

template <typename T>
Point <T> radialSort(typename vector <Point <T>> :: iterator __first, 
        typename vector <Point <T>> :: iterator __last) {
    Point <T> m = *min_element(__first, __last);

    sort(__first, __last, [m](Point <T> x, Point <T> y) {
        Vector <T> f = { m, x }, s = { m, y };
        if (abs(pscal<T>(f, s)) < eps) {
            return f.len() < s.len();
        }
        return pscal<T>(f, s) > 0;
    });

    return m;
}

template <typename T>
vector <Point <T>> convexHull(typename vector <Point <T>> :: iterator __first,
        typename vector <Point <T>> :: iterator __last) {
    radialSort<T>(__first, __last);
    return _convexHull<T>(__first, __last);
}

template <typename T>
struct Circle {
    Point <T> cent;
    long double r;

    Circle <T>() {}
    Circle <T>(Point <T>& _cent, long double _r) : cent(_cent), r(_r) {}
    Circle <T>(T x, T y, long double _r) : cent(x, y), r(_r) {}

    template <typename V>
    inline bool belongs(Point <V> p) const {
        return abs((p.x - cent.x) * (p.x - cent.x) +
               (p.y - cent.y) * (p.y - cent.y) - r * r) < eps;
    }

    inline long double length() const {
        return 2 * pi * r;
    }

    inline long double area() const {
        return pi * r * r;
    }
};

template <typename T>
vector <Point <T>> intersect(Circle <T> c, Line <T> l) {
    Point <T> p = findProjection(c.cent, l);
    long double dist = distance(c.cent, p);

    if (abs(dist - c.r) < eps) {
        return { p };
    }
    else if (dist > c.r) {
        return { };
    }
    else {
        Vector <T> v = { -l.b, l.a };
        v.normalize();
        v *= sqrt(c.r * c.r - dist * dist);

        return { p - v, p + v };
    }
}

template <typename T>
vector <Point <T>> intersect(Circle <T> x, Circle <T> y) {
    if (areSame(x.cent, y.cent)) {
        return { };
    }
    else {
        auto a = x.cent, b = y.cent;

        Line <T> l;
        l.a = 2 * (a.x - b.x);
        l.b = 2 * (a.y - b.y);
        l.c = b.x * b.x + b.y * b.y - y.r * y.r - a.x * a.x - a.y * a.y + x.r * x.r;

        return intersect(x, l);
    } 
}

template <typename T>
vector <Point <T>> tangent(Circle <T> c, Point <T> p) {
    if (distance(c.cent, p) < c.r) {
        return { };
    }
    else if (c.belongs(p)) {
        return { p };
    }
    else {
        long double dist = distance(p, c.cent);
        Circle <T> d(p, sqrt(dist * dist - c.r * c.r));
        return intersect(c, d);
    }
}

template <typename T>
bool onSegment(Point <T> s, Point <T> f, Point <T> p) {
    return (Line <long double>(s, f).belongs(p) &&
        p.x + eps >= min(s.x, f.x) && p.x - eps <= max(s.x, f.x) &&
        p.y + eps >= min(s.y, f.y) && p.y - eps <= max(s.y, f.y)) ||
        areSame(s, p) || areSame(f, p);
}

template <typename T>
bool insideTriangle(Point <T> p, Point <T> a, Point <T> b, Point <T> c) {
    T s = 0;
    s += abs(pscal <T>({ p, a }, { p, b }));
    s += abs(pscal <T>({ p, b }, { p, c }));
    s += abs(pscal <T>({ p, a }, { p, c }));

    T x = abs(pscal <T>({ a, b }, { a, c }));

    return abs(s - x) < eps;
}

template <typename T>
void precalc(vector <Point <T>>& a) {
    rotate(a.begin(), min_element(a.begin(), a.end()), a.end());
}

/**
 * logn, precalc needed
*/
template <typename T>
bool insidePolygon(vector <Point <T>>& a, Point <T> p) {
    if (p < a.front()) {
        return false;
    }

    int l = 1, r = sz(a) - 1, m;
    while (r - l > 1) {
        m = (l + r) / 2;

        if (pscal <T>({ a.front(), a[m] }, { a.front(), p }) > 0) {
            l = m;
        }
        else {
            r = m;
        }
    }

    return insideTriangle(p, a.front(), a[l], a[r]);
}

template <typename T>
bool onCircle(Point <T> a, Point <T> b, Point <T> c, Point <T> d) {
    auto degreeEq = [=] (Point <T> a, Point <T> b, Point <T> c,
            Point <T> x, Point <T> y, Point <T> z) {

        return abs(pscal<T> ({ b, a }, { b, c }) * scal<T> ({ y, x }, { y, z }) -
                scal<T> ({ b, a }, { b, c }) * pscal<T> ({ y, x }, { y, z })) < eps;
    };

    return abs(pscal<T> ({ a, b }, { b, c })) > eps &&
           abs(pscal<T> ({ a, c }, { c, d })) > eps &&
           abs(pscal<T> ({ b, c }, { c, d })) > eps &&
           (degreeEq(a, b, d, a, c, d) || degreeEq(a, b, c, a, d, c));
}

template <typename T>
long double pointToSegment(Point <T> p, Point <T> a, Point <T> b) {
    long double ans = min(distance(p, a), distance(p, b));
    long double s = abs(pscal <T> ({ p, a }, { p, b }));
    if (scal <T>({ a, b }, { b, p }) <= 0 && scal <T>({ b, a }, { a, p }) <= 0) {
        ans = min(ans, s / distance(a, b));
    }
    return ans;
}

template <typename T>
long double pointToBeam(Point <T> p, Point <T> a, Point <T> b) {
    long double ans = distance(p, a);
    long double s = abs(pscal <T> ({ p, a }, { p, b }));
    if (scal <T>({ b, a }, { a, p }) <= 0) {
        ans = min(ans, s / distance(a, b));
    }
    return ans;
}

template <typename T, typename V>
long double pointToLine(Point <T> p, Line <V> l) {
    return abs(l.eval(p) / sqrt(l.a * l.a + l.b * l.b));
}

template <typename T>
long double segmentToSegment(Point <T> a, Point <T> b, Point <T> c, Point <T> d) {
    Line <long double> x(a, b), y(c, d);
    auto p = intersect(x, y);

    if (!p.empty() &&
        onSegment(static_cast<Point<long double>>(a),
                  static_cast<Point<long double>>(b),
                  p.front()) &&
        onSegment(static_cast<Point<long double>>(c),
                  static_cast<Point<long double>>(d),
                  p.front())) {
        return 0;
    }
    else {
        return min({ pointToSegment(a, c, d), pointToSegment(b, c, d),
            pointToSegment(c, a, b), pointToSegment(d, a, b) });
    }
}

template <typename T>
long double segmentToBeam(Point <T> a, Point <T> b, Point <T> c, Point <T> d) {
    Line <long double> x(a, b), y(c, d);
    auto p = intersect(x, y);

    if (!p.empty() &&
        onSegment(static_cast<Point<long double>>(a),
                  static_cast<Point<long double>>(b),
                  p.front()) &&
        onBeam(static_cast<Point<long double>>(c),
               static_cast<Point<long double>>(d),
               p.front())) {
        return 0;
    }
    else {
        return min({ pointToBeam(a, c, d), pointToBeam(b, c, d), pointToSegment(c, a, b) });
    }
}

template <typename T, typename V>
long double segmentToLine(Point <T> a, Point <T> b, Line <V> l) {
    Line <long double> x(a, b);
    auto p = intersect(x, l);

    if (!p.empty() &&
        onSegment(static_cast<Point<long double>>(a),
                  static_cast<Point<long double>>(b),
                  p.front())) {
        return 0;
    }

    return min({ pointToLine(a, l), pointToLine(b, l) });
}

template <typename T>
long double beamToBeam(Point <T> a, Point <T> b, Point <T> c, Point <T> d) {
    Line <long double> l1(a, b), l2(c, d);
    auto v = intersect(l1, l2);

    auto A = static_cast<Point<long double>>(a);
    auto B = static_cast<Point<long double>>(b);
    auto C = static_cast<Point<long double>>(c);
    auto D = static_cast<Point<long double>>(d);

    if (!v.empty() && onBeam(A, B, v.front()) && onBeam(C, D, v.front())) {
        return 0;
    }
    else {
        return min(pointToBeam(a, c, d), pointToBeam(c, a, b));
    }
}

template <typename T, typename V>
long double beamToLine(Point <T> a, Point <T> b, Line <V> l) {
    Line <V> l2(a, b);
    auto v = intersect(l, l2);

    auto A = static_cast<Point<long double>>(a);
    auto B = static_cast<Point<long double>>(b);

    if (!v.empty() && onBeam(A, B, v.front())) {
        return 0;
    }
    else {
        return pointToLine(a, l);
    }
}

template <typename T>
long double lineToLine(Line <T> a, Line <T> b) {
    auto v = intersect(a, b);

    if (v.empty()) {
        return pointToLine(a.getPoint(), b);        
    }
    else {
        return 0;
    }
}


