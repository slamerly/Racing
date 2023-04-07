#pragma once
#include "Actor.h"
#include "RectangleCollisionComponent.h"

class Moto :
    public Actor
{
public:
    Moto();

    void updateActor(float dt) override;

    RectangleCollisionComponent& getCollision() { return *collision; }

private:
    RectangleCollisionComponent* collision;
};

