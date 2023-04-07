#include "MoveComponent.h"
#include "Maths.h"
#include "Actor.h"
#include "Window.h"
#include "Paddle.h"
#include <typeinfo>
#include "Ball.h"

MoveComponent::MoveComponent(Actor* ownerP, int updateOrderP): 
	Component(ownerP, updateOrderP), forwardSpeed(0.0f), angularSpeed(0.0f)
{
}

void MoveComponent::setForwardSpeed(float forwardSpeedP)
{
	forwardSpeed = forwardSpeedP;
}

void MoveComponent::setUpSpeed(float upSpeedP)
{
	upSpeed = upSpeedP;
}

void MoveComponent::setAngularSpeed(float angularSpeedP)
{
	angularSpeed = angularSpeedP;
}

void MoveComponent::update(float dt)
{
	if (!Maths::nearZero(angularSpeed))
	{
		float newRotation = owner.getRotation() + angularSpeed * dt;
		owner.setRotation(newRotation);
	}
	if (!Maths::nearZero(forwardSpeed))
	{
		Vector2 newPosition = owner.getPosition() + owner.getForward() * forwardSpeed * dt;
		owner.setPosition(newPosition);
	}
	/*
	if (!Maths::nearZero(upSpeed))
	{
		Vector2 newPosition = owner.getPosition() + owner.getUp() * upSpeed * dt;
		owner.setPosition(newPosition);
	}
	*/
}