#include "Rigidbody.h"
#include "Transform.h"

Rigidbody::Rigidbody() :
    acceleration({0,0}), velocity({0,0}), mass(1),
    force({ 0,0 }), drag(0), torque(0), av(0), ac(0)
{

}

void Rigidbody::addForce(const Vector2 &a) { force = force + a; }

void Rigidbody::addTorque(float a) { torque += a; }

void Rigidbody::integrate(Transform *t, float dt)
{

    jerk         = force / mass - acceleration; // Jerk is optional!
    acceleration = acceleration + jerk * dt; // acceleration = force/mass;
    velocity     = velocity + acceleration * dt;    
    t->setPosition(t->getPosition() + velocity * dt);

    velocity = velocity - velocity * drag * dt;
    force = { 0, 0 };

    ac = torque / mass;
    av += ac*dt;
    t->setAngle(t->getAngle() + av*dt);
    torque = 0;
}