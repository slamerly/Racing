#include "Moto.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "InputComponent.h"
#include "Window.h"
#include "Game.h"
#include "Maths.h"
#include <iostream>

Moto::Moto() :
	Actor()
{
	SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Moto"));
	InputComponent* ic = new InputComponent(this);

	ic->setMaxForwardSpeed(150);
	//ic->setMaxAngularSpeed(Maths::twoPi);
	ic->setMaxAngularSpeed(Maths::toRadians(45.0f));

	collision = new RectangleCollisionComponent(this);
	collision->setWidth(40.0f);
	collision->setHeigh(20.0f);
}

void Moto::updateActor(float dt)
{
}
