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

		// Screen wrapping
		/*
		if (newPosition.x < 0) { newPosition.x = WINDOW_WIDTH; }
		else if (newPosition.x > WINDOW_WIDTH) { newPosition.x = 0; }
		if (newPosition.y < 0) { newPosition.y = WINDOW_HEIGHT; }
		else if (newPosition.y > WINDOW_HEIGHT) { newPosition.y = 0; }
		*/

		if (typeid(owner).hash_code() == typeid(Paddle).hash_code())
		{
			if ((newPosition.x > (WINDOW_HEIGHT / 6) + 75) && (newPosition.x < ((WINDOW_HEIGHT / 6) * 5) + 125))
				owner.setPosition(newPosition);
		}
		else
			owner.setPosition(newPosition);
	}
	if (!Maths::nearZero(upSpeed))
	{
		//Vector2 newPosition = owner.getPosition() + owner.getUp() * upSpeed * dt;
		/*
		if (typeid(owner).hash_code() == typeid(Paddle).hash_code())
		{
			if(newPosition.y > 50 && newPosition.y < WINDOW_HEIGHT - 50)
				owner.setPosition(newPosition);
		}
		else
		*/
		if (typeid(owner).hash_code() == typeid(Ball).hash_code())
		{
			Vector2 newPosition = owner.getPosition() + owner.getUp() * upSpeed * dt;
			owner.setPosition(newPosition);
		}
		//owner.setPosition(newPosition);
	}
}