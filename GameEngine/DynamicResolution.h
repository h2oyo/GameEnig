#pragma once

#include "CollisionDetection.h"

class DynamicResolution : public CollisionSystem
{
    bool condition(Collision c)
    {
        return c.first->rigidbody > -1 && c.second->rigidbody > -1;
    }

    void update(Collision c)
    {
        Vector2 MTV = c.collision.normal * c.collision.depth;

        Vector2 p1 = c.first ->transform->getPosition() - MTV/2;
        Vector2 p2 = c.second->transform->getPosition() + MTV/2;

        c.first ->transform->setPosition(p1);
        c.second->transform->setPosition(p2);

        std::swap(c.first->rigidbody->velocity, c.second->rigidbody->velocity);
    }
};











//class DynamicResolution : public CollisionSystem
//{
//
//    bool condition(Collision c)
//        { return c.first->rigidbody > -1 && c.second->rigidbody > -1; }
//
//
//    void update(Collision c)
//    {        
//        c.first->transform->setPosition(c.first->transform->getPosition() - c.collision.normal * c.collision.depth);        
//        c.second->transform->setPosition(c.second->transform->getPosition() + c.collision.normal * c.collision.depth);
//
//
//        std::swap(c.first->rigidbody->velocity,c.second->rigidbody->velocity);
//    }
//};