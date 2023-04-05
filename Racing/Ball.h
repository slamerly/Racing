#pragma once
#include "Actor.h"
#include "MoveComponent.h"
#include "CircleCollisionComponent.h"

class Ball :
    public Actor
{
public:
    Ball();

    void updateActor(float dt) override;
    void ballReset();
    void setBallLock(bool ballstate);
    void setlife(int lifeP);

    CircleCollisionComponent& getCollision() { return *collision; }
    bool getBallLock() { return ballLock; }
    MoveComponent* getMove() { return move; }

private:
    MoveComponent* move;
    CircleCollisionComponent* collision;
    bool ballLock = true;
    float maxForwardSpeed = 150, maxUpSpeed = 150;
    int life;

    void ballMovement();
};

