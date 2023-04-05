#pragma once
#include "Actor.h"
#include "RectangleCollisionComponent.h"
#include "SpriteComponent.h"

class Brick :
    public Actor
{
public:
    Brick();
    ~Brick();

    void updateLife();
    RectangleCollisionComponent& getCollision() { return *collision; }

private:
    RectangleCollisionComponent* collision;
    SpriteComponent* sc;
    int level, life;
};

