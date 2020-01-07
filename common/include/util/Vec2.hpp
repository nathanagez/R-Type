#ifndef VEC2_HPP
#define VEC2_HPP

template<class T>
struct Vec2
{
    T x = 0;
    T y = 0;

    Vec2(void) : x(0), y(0) {};
    Vec2(const T &_x, const T &_y) : x(_x), y(_y) {};
    Vec2(const Vec2 &v) : x(v.x), y(v.y) {};

    inline Vec2 operator+(const Vec2 &v) const {return Vec2(x + v.x, y + v.y);};
    inline Vec2 operator-(const Vec2 &v) const {return (Vec2(x - v.x, y - v.y));};
    inline Vec2 operator*(const Vec2 &v) const {return (Vec2(x * v.x, y * v.y));};
    inline Vec2 operator/(const Vec2 &v) const {return (Vec2(x / v.x, y / v.y));};
    inline Vec2 operator+(const T &t) const {return (Vec2(x + t, y + t));};
    inline Vec2 operator-(const T &t) const {return (Vec2(x - t, y - t));};
    inline Vec2 operator*(const T &t) const {return (Vec2(x * t, y * t));};
    inline Vec2 operator/(const T &t) const {return (Vec2(x / t, y / t));};
    inline Vec2 &operator+=(const Vec2 &v) {this->x += v.x; this->y += v.y; return (*this);};
    inline Vec2 &operator-=(const Vec2 &v) {this->x -= v.x; this->y -= v.y; return (*this);};
    inline Vec2 &operator*=(const Vec2 &v) {this->x *= v.x; this->y *= v.y; return (*this);};
    inline Vec2 &operator/=(const Vec2 &v) {this->x /= v.x; this->y /= v.y; return (*this);};
    inline Vec2 &operator+=(const T &t) {this->x += t; this->y += t; return (*this);};
    inline Vec2 &operator-=(const T &t) {this->x -= t; this->y -= t; return (*this);};
    inline Vec2 &operator*=(const T &t) {this->x *= t; this->y *= t; return (*this);};
    inline Vec2 &operator/=(const T &t) {this->x /= t; this->y /= t; return (*this);};
};
typedef Vec2<int> Vec2i;
typedef Vec2<unsigned int> Vec2u;
typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;

#endif /* VEC2_HPP */
