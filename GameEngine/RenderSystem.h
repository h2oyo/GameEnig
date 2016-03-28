#pragma once
#include "System.h"
#include "Assets.h"

class RenderSystem : public System
{
    // sprite and transform
    bool condition(Handle<Entity> i)
    {
        return i->sprite > -1 && i->transform > -1;
    }

    // the actual draw call
    void update(Handle<Entity> i)
    {
        Matrix3 m = 
                  i->transform->getGlobalTransform()
                  * Matrix3::translate(i->sprite->offset)
                  * Matrix3::scale(i->sprite->dimension)
                  * Matrix3::rotate(i->sprite->angle);

        Asset::instance().drawTexture(i->sprite->assetName, m);
    }
};