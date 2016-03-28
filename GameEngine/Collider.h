#pragma once
#include "GCData.h"

#include "Shapes.h"
#include "collision.h"
#include "Transform.h"

// Shapes!


struct Collider : GCData<Collider>
{

    // Can only be one of the following shapes
    enum SHAPE {e_CIRCLE = 1, e_AABB = 2, e_RAY = 4, e_PLANE = 8, e_HULL = 16} shape;
    
    union
    {
        Circle  circle;
        AABB    aabb;
        Ray     ray;
        Plane   plane;
    };

    // Could also have a convex hull though.
    // ConvexHull can't be in the union because it's a vector and not POD
    // It also takes up very little space if we're not using it.
    ConvexHull chull;


    Collider() : shape(e_CIRCLE), circle{ { 0,0 }, 1 } {}
};

CollisionData EvaluateCollision(const Transform &at, const Collider &ac,
                                const Transform &bt, const Collider &bc);