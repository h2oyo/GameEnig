#pragma once
#include "VMath.h"
#include <vector>

struct Ray        { Vector2 position, direction; float length;   };
struct Plane      { Vector2 position, normal;                    };
struct Circle     { Vector2 position; float radius;              };
struct AABB       { Vector2 position, halfextents;
                    Vector2 min() const, max() const;            };

inline Vector2 AABB::min() const { return position - halfextents; }
inline Vector2 AABB::max() const { return position + halfextents; }


struct ConvexHull { std::vector<Vector2> verts; };

inline AABB         operator*(const Matrix3 &m, const AABB &a)
{
    Vector2 omin = a.min();
    Vector2 omax = a.max();

    Vector2 rmin = m[2].xy;
    Vector2 rmax = m[2].xy;

    float p, q;

    for (unsigned j = 0; j < 2; ++j)
        for (unsigned i = 0; i < 2; ++i)
        {
            p = omin[i] * m[i][j];
            q = omax[i] * m[i][j];

            if (p < q) std::swap(p, q);
            rmin[j] += p;
            rmax[j] += q;
        }
    return{ (rmin + rmax) / 2, (rmin - rmax) / 2 };
}
inline Circle       operator*(const Matrix3 &m, const Circle &a)
{
    Circle ret;
    ret.position = (m * Vector3(a.position.x, a.position.y, 1)).xy;

    Vector3 xrad(a.radius, 0, 0);
    Vector3 yrad(0, a.radius, 0);

    ret.radius = fmaxf((m*xrad).magnitude(), (m*yrad).magnitude());

    return ret;
}
inline Ray          operator*(const Matrix3 &m, const Ray &a)
{
    Vector3 dir = Vector3(a.direction.x, a.direction.y, 0) * a.length;
    Vector3 pos(a.position.x, a.position.y, 1);

    return{ (m * pos).xy, normal((m * dir).xy), dir.magnitude() };
}
inline Plane        operator*(const Matrix3 &m, const Plane &a)
{
    Vector3 nor(a.normal.x, a.normal.y, 0);
    Vector3 pos(a.position.x, a.position.y, 1);

    return{ (m * pos).xy,(m * nor).xy };
}
inline ConvexHull   operator*(const Matrix3 &m, const ConvexHull &a)
{
    ConvexHull ret;
    for each(Vector2 p in ret.verts)
        ret.verts.push_back((m * Vector3{ p.x, p.y, 1 }).xy);

    return ret;
}



