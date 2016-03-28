#pragma once
#include "Entity.h"
// Factory Method
// Constructor with a lot of meaningful defaults

struct Factory
{

    static Handle<Entity> makeBall(Vector2 pos, Vector2 vel, float radius, float mass)
    {
        auto e = Entity::make();
        e->collider  = Collider::make();
        e->rigidbody = Rigidbody::make();
        e->transform = Transform::make();

        e->collider->circle.radius = radius;
        e->collider->shape = Collider::e_CIRCLE;
        e->rigidbody->mass = mass;
        e->rigidbody->velocity = vel;
        e->transform->setPosition(pos);
        return e;
    }


    static Handle<Entity> makeWall(Vector2 pos, Vector2 normal)
    {
        auto e = Entity::make();
        e->collider = Collider::make();
        e->transform = Transform::make();

        e->collider->plane.normal = normal;
        e->collider->shape = Collider::e_PLANE;
        e->transform->setPosition(pos);

        return e;
    }


    static Handle<Entity> makePlayer(Vector2 pos)
    {
        auto e = Entity::make();
        e->collider     = Collider::make();
        e->rigidbody    = Rigidbody::make();
        e->transform    = Transform::make();
        e->controller   = PlayerController::make();
        e->sprite       = Sprite::make();

        e->sprite->assetName = "Ship";
        e->sprite->dimension = Vector2{ 72,72 };

        e->collider->shape = Collider::e_AABB;
        e->collider->aabb.halfextents = Vector2{36,36};
        e->transform->setPosition(pos);

        return e;
    }


    static Handle<Entity> makeBullet(Vector2 pos, Vector2 dir, float life = 1.6f, float speed = 100.f)
    {
        auto e = Entity::make();
        e->rigidbody = Rigidbody::make();
        e->transform = Transform::make();
        e->lifecycle = Lifecycle::make();
        
        e->transform->setPosition(pos);
        e->rigidbody->velocity = dir * speed;
        e->lifecycle->lifespan = life;

        return e;
    }
};