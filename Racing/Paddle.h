#pragma once
#include "Actor.h"
#include "RectangleCollisionComponent.h"

class Paddle :
    public Actor
{
public:
    Paddle();

    RectangleCollisionComponent& getCollision() { return *collision; }

private:
    RectangleCollisionComponent* collision;
};

