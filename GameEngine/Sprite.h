#pragma once
#include "GCData.h"
#include "VMath.h"
#include <string>

class Sprite : public GCData<Sprite>
{
public:
    Vector2 offset;
    Vector2 dimension;
    float   angle;

    std::string assetName;
    
    Sprite() : offset({0,0}),
                dimension({1,1}),
                angle(0) { }
};