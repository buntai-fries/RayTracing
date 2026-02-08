#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
public:
    double v[3];

    vec3():v{0, 0, 0} {}
    vec3(double v0, double v1, double v2):v{v0, v1, v2} {}

    double x() const {
        return v[0];
    }
    double y() const {
        return v[1];
    }
    double z() const {
        return v[2];
    }

    vec3 operator-() const { return vec3(-v[0], -v[1], -v[2]); }
    double operator[](int i) const { return v[i]; }
    double& operator[](int i) { return v[i]; }

    vec3& operator+=(const vec3& v1) {
        v[0] += v1.v[0];
        v[1] += v1.v[1];
        v[2] += v1.v[2];
        return *this;
    }

    vec3& operator*=(double t) {
        v[0] *= t;
        v[1] *= t;
        v[2] *= t;
        return *this;
    }

    vec3& operator/=(double t) {
        return *this *= 1/t;
    }

    double length() const {
        return std::sqrt(length_squared());
    }

    double length_squared() const {
        return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
    }
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;

// Vector Utility Functions
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.v[0] << ' ' << v.v[1] << ' ' << v.v[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.v[0] + v.v[0], u.v[1] + v.v[1], u.v[2] + v.v[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.v[0] - v.v[0], u.v[1] - v.v[1], u.v[2] - v.v[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.v[0] * v.v[0], u.v[1] * v.v[1], u.v[2] * v.v[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.v[0], t*v.v[1], t*v.v[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u.v[0] * v.v[0]
         + u.v[1] * v.v[1]
         + u.v[2] * v.v[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.v[1] * v.v[2] - u.v[2] * v.v[1],
                u.v[2] * v.v[0] - u.v[0] * v.v[2],
                u.v[0] * v.v[1] - u.v[1] * v.v[0]);
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

#endif