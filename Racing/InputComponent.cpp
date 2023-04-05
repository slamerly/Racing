#include "InputComponent.h"
#include <SDL_scancode.h>

InputComponent::InputComponent(Actor* ownerP) :
	MoveComponent(ownerP),
	maxForwardSpeed(100.0f),
	maxAngularSpeed(1.0f),
	forwardKey(SDL_SCANCODE_W),
	backKey(SDL_SCANCODE_S),
	leftKey(SDL_SCANCODE_LEFT),
	rightKey(SDL_SCANCODE_RIGHT),
	upKey(SDL_SCANCODE_UP),
	downKey(SDL_SCANCODE_DOWN),
	clockwiseKey(SDL_SCANCODE_D),
	counterClockwiseKey(SDL_SCANCODE_A)
{
}

void InputComponent::processInput(const Uint8* keyState)
{
	float forwardSpeed = 0.0f;
	//if (keyState[forwardKey])
	if (keyState[rightKey])
	{
		forwardSpeed += maxForwardSpeed;
	}
	//if (keyState[backKey])
	if (keyState[leftKey])
	{
		forwardSpeed -= maxForwardSpeed;
	}
	setForwardSpeed(forwardSpeed);

	/*
	float angularSpeed = 0.0f;
	if (keyState[clockwiseKey])
	{
		angularSpeed -= maxAngularSpeed;
	}
	if (keyState[counterClockwiseKey])
	{
		angularSpeed += maxAngularSpeed;
	}
	setAngularSpeed(angularSpeed);
	*/
	/*
	float upSpeed = 0.0f;
	if (keyState[upKey])
	{
		upSpeed += maxUpSpeed;
	}
	if (keyState[downKey])
	{
		upSpeed -= maxUpSpeed;
	}
	setUpSpeed(upSpeed);
	*/
}

void InputComponent::setMaxForwardSpeed(float maxForwardSpeedP)
{
	maxForwardSpeed = maxForwardSpeedP;
}

void InputComponent::setMaxUpSpeed(float maxUpSpeedP)
{
	maxUpSpeed = maxUpSpeedP;
}

void InputComponent::setMaxAngularSpeed(float maxAngularSpeedP)
{
	maxAngularSpeed = maxAngularSpeedP;
}

void InputComponent::setForwardKey(int key)
{
	forwardKey = key;
}

void InputComponent::setBackKey(int key)
{
	backKey = key;
}

void InputComponent::setLeftKey(int key)
{
	leftKey = key;
}

void InputComponent::setRightKey(int key)
{
	rightKey = key;
}

void InputComponent::setUpKey(int key)
{
	upKey = key;
}

void InputComponent::setDownKey(int key)
{
	downKey = key;
}

void InputComponent::setClockwiseKey(int key)
{
	clockwiseKey = key;
}

void InputComponent::setCounterClockwiseKey(int key)
{
	counterClockwiseKey = key;
}