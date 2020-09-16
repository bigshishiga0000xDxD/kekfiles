template <typename T>
struct Point {
    T x, y;
 
    Point() {}
    Point(T _x, T _y) : x(_x), y(_y) {}
 
    bool operator==(const Point <T>& s) {
        return x == s.x && y == s.y;
    }

    bool operator!=(const Point <T>& s) {
        return x != s.x || y != s.y;
    }

    bool operator<(const Point <T>& s) {
        if (x != s.x) {
            return x < s.x;
        }
        else {
            return y < s.y;
        }
    }
 
    bool operator>(const Point <T>& s) {
        if (x != s.x) {
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
        this->x += s.x;
        this->y += x.y;
        return *this;
    }
 
    operator string() {
        return "{" + to_string(x) + ", " + to_string(y) + "}";
    }
};
 
template <typename T>
long double distance(Point <T> a, Point <T> b) {
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
    Vector(Point <T> a, Point <T> b) : x(b.x - a.x), y(b.y - a.y) {}
    Vector(T a, T b) : x(a), y(b) {}
 
    ld len() {
        return sqrt(x * x + y * y);
    }
 
    Vector <T> operator+(Vector <T> v) {
        return { x + v.x, y + v.y };
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
T scal(Vector <T> a, Vector <T> b) {
    return a.x * b.x + a.y * b.y;
}
 
template <typename T>
T pscal(Vector <T> a, Vector <T> b) {
    return a.x * b.y - a.y * b.x;
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
    bool belongs(Point <V> p) {
        return abs(a * p.x + b * p.y + c) < eps;
    }
 
    void normalize() {
        T t = sqrt(a * a + b * b);
        a /= t, b /= t, c /= t;
    }
 
    T getY(T x) {
        if (b) {
            return (a * x + c) / (-b);
        }
        else {
            return 0;
        }
    }
    T getX(T y) {
        if (a) {
            return (b * y + c) / (-a);
        }
        else {
            return 0;
        }
    }
};
 
template <typename T>
vector <Point <T>> intersect(Line <T>& a, Line <T>& b) {
    T t = abs(a.a * b.b - b.a * a.b); 
    if (t < eps) {
        return { };
    }
    else {
        T y = (b.a * a.c - a.a * b.c) / t;
        T x = (-a.b * y - a.c) / a.a;
        return { { x, y } };
    }
}
 
template <typename T>
bool OnBeam(Point <T> P1, Point <T> P2, // beam
    Point <T> P /* point */) {
    if (pscal <T>({ P1, P }, { P1, P2 }) != 0) {
        return false;
    }
    if (scal <T>({ P1, P }, { P2, P }) <= 0 || scal <T>({ P1, P2 }, { P2, P }) >= 0) {
        return true;
    }
    return false;
}
 
template <typename T>
bool IntoAngle(Point <T> a, Point <T> o, Point <T> b, // angle
    Point <T> p /* point */) {
    if (OnBeam(o, a, p) || OnBeam(o, b, p)) {
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
vector <Point <T>> _ConvexHull(typename vector <Point <T>> :: iterator __first,
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
Point <T> RadialSort(typename vector <Point <T>> :: iterator __first, 
        typename vector <Point <T>> :: iterator __last) {
    Point m = *min_element(__first, __last);

    sort(__first, __last, [m](Point <T> x, Point <T> y) {
        Vector <T> f = { m, x }, s = { m, y };
        if (pscal<T>(f, s) == 0) {
            return f.len() < s.len();
        }
        return pscal<T>(f, s) > 0;
    });

    return m;
}

template <typename T>
vector <Point <T>> ConvexHull(typename vector <Point <T>> :: iterator __first,
        typename vector <Point <T>> :: iterator __last) {
    RadialSort<T>(__first, __last);
    return _ConvexHull<T>(__first, __last);
}

