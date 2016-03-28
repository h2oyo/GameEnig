#pragma once
#include "GCData.h"

/*
    Turn left and right
    Move forward
*/

class PlayerController : public GCData<PlayerController>
{
public:
    char LEFT, RIGHT,
                FORWARD;

    float speed, turnSpeed;
    
    PlayerController() : LEFT('A'), RIGHT('D'),
            FORWARD('W'),
        speed(60), turnSpeed(1) {}
};