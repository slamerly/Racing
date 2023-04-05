#include "Paddle.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "InputComponent.h"
#include "Window.h"
#include "Game.h"

Paddle::Paddle() :
	Actor()
{
	SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Paddle"));
	InputComponent* ic = new InputComponent(this);

	ic->setMaxForwardSpeed(300);

	collision = new RectangleCollisionComponent(this);
	collision->setWidth(100.0f);
	collision->setHeigh(10.0f);
}
