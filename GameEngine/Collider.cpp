
#include "Collider.h"
#include "Transform.h"


/*
    collision.h from the math library is heavily used here.
*/


CollisionData EvaluateCollision(const Transform &at, const Collider &ac,
                                const Transform &bt, const Collider &bc)
{
    Transform t_lhs = at;
    Transform t_rhs = bt;
    Collider lhs    = ac;
    Collider rhs    = bc;
    
    if (lhs.shape > rhs.shape)
    {
        std::swap(lhs, rhs);
        std::swap(t_lhs, t_rhs);
    }

    CollisionData cd;

    switch (lhs.shape | rhs.shape)
    {
    case Collider::e_CIRCLE:
        cd = iTest(t_lhs.getGlobalTransform() * lhs.circle,
                   t_rhs.getGlobalTransform() * rhs.circle);
        break;

    case Collider::e_AABB:
        cd = iTest(t_lhs.getGlobalTransform() * lhs.aabb,
                   t_rhs.getGlobalTransform() * rhs.aabb);
        break;

    case Collider::e_CIRCLE | Collider::e_AABB:
        cd = iTest(t_lhs.getGlobalTransform() * lhs.circle,
                     t_rhs.getGlobalTransform() * rhs.aabb);
        break;

    //case Collider::e_CIRCLE | Collider::e_RAY:
    //    return iTest(t_lhs.getGlobalTransform() * lhs.circle,
    //                 t_rhs.getGlobalTransform() * rhs.ray);
    //
    //case Collider::e_CIRCLE | Collider::e_PLANE:
    //    cd = iTest(t_lhs.getGlobalTransform() * lhs.circle,
    //                 t_rhs.getGlobalTransform() * rhs.plane);



    //case Collider::e_AABB | Collider::e_RAY:
    //    cd = iTest(t_lhs.getGlobalTransform() * lhs.aabb,
    //                 t_rhs.getGlobalTransform() * rhs.ray);

    //case Collider::e_AABB | Collider::e_PLANE:
    //    return iTest(t_lhs.getGlobalTransform() * lhs.aabb,
    //                 t_rhs.getGlobalTransform() * rhs.plane);

    //case Collider::e_RAY  | Collider::e_PLANE:
    //    cd = iTest(t_lhs.getGlobalTransform() * lhs.ray,
    //                 t_rhs.getGlobalTransform() * rhs.plane);
    }

    return cd;
}