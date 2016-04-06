#pragma once
#include "Shapes.h"
#include "VMath.h"

struct CollisionData // Wrapper for Minimum Translation Vector
{
    bool     result;         // Did we collide?
    float    depth;
    Vector2  normal;   // CollisionNormal * PenetrationDepth = Minimum Translation Vector, also called the impulse vector, very important! 
};


inline CollisionData DSAT(float amin, float amax, float bmin, float bmax, Vector2 axis)
{
    float pDr = amax - bmin;
    float pDl = bmax - amin;

    float pD  = std::fminf(pDr, pDl);

    float H   = std::copysignf(1, pDr - pDl);


    return {pD > 0, pD, axis*H};
}


inline CollisionData iTest(const Circle &a, const Circle &b)
{
    CollisionData cd;
    auto diff = b.position - a.position;

    cd.normal = normal(diff);
    cd.depth  = (b.radius + a.radius) - diff.magnitude();
    cd.result = cd.depth > 0;

    return cd;    
}


inline CollisionData iTest(const AABB &a, const AABB &b)
{
 
    auto cdx = DSAT(a.min().x, a.max().x, b.min().x, b.max().x, { 1, 0 });
    auto cdy = DSAT(a.min().y, a.max().y, b.min().y, b.max().y, { 0, 1 });

    return cdx.depth < cdy.depth ? cdx : cdy;
}



inline CollisionData iTest(Circle a, const AABB &b)
{    
    // Snap is just a clamp that includes interior spaces
    // We can create a circle to represent the clamping point
    // and just use the circle vs circle test.
    Circle cp = { snap(a.position, b.min(), b.max()), 0 };

  
    if (b.min() < a.position && a.position < b.max())
        std::swap(a, cp);

    // circle circle test
    return iTest(a, cp);
}
inline CollisionData iTest(const Circle &a, const Circle &b)
{
	CollisionData cd;
	if ((b.position.x - a.position.x)*(b.position.x - a.position.x)
		+ (b.position.y - a.position.y)*(b.position.y - a.position.y)
		<= (a.radius + b.radius)*(a.radius + b.radius));
	return cd;
};

// Some distance formula
//float point_plane_dist  (const Vector2 &a, const Plane &b);
//float ray_plane_dist    (const Ray     &a, const Plane &b);
//
//

//CollisionData iTest(const AABB   &a, const Circle &b);
//CollisionData iTest(const AABB   &a, const Ray    &b);
//CollisionData iTest(const AABB   &a, const Plane  &b);
//

//CollisionData iTest(const Circle &a, const Plane  &b);
//CollisionData iTest(const Circle &a, const Ray    &b);
//
//CollisionData iTest(const Ray    &a, const Plane  &b);
//
// 
//// Convex Hull vs remaining shapes
//CollisionData iTest(const ConvexHull &A, const ConvexHull &B);
//CollisionData iTest(const ConvexHull &A, const Circle     &b);
//CollisionData iTest(const ConvexHull &A, const Ray        &b);
//CollisionData iTest(const ConvexHull &A, const Plane      &b);
//CollisionData iTest(const ConvexHull &A, const AABB       &b);
//
//
//
//// flip overloads for lhs/rhs
//inline CollisionData iTest(const Circle &b, const AABB   &a) { return iTest(a, b); }
//inline CollisionData iTest(const Plane  &b, const AABB   &a) { return iTest(a, b); }
//inline CollisionData iTest(const Ray    &b, const AABB   &a) { return iTest(a, b); }
//
//inline CollisionData iTest(const Plane  &b, const Circle &a) { return iTest(a, b); }
//inline CollisionData iTest(const Ray    &b, const Circle &a) { return iTest(a, b); }
//
//inline CollisionData iTest(const Plane  &b, const Ray    &a) { return iTest(a, b); }
//
//inline CollisionData iTest(const Circle &b, const ConvexHull &A) { return iTest(A, b); }
//inline CollisionData iTest(const Ray    &b, const ConvexHull &A) { return iTest(A, b); }
//inline CollisionData iTest(const Plane  &b, const ConvexHull &A) { return iTest(A, b); }
//inline CollisionData iTest(const AABB   &b, const ConvexHull &A) { return iTest(A, b); }