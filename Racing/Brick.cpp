#include "Brick.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "Game.h"
#include <iostream>

Brick::Brick() :
	Actor()
{
	level = rand() % 5 + 1;

	switch (level)
	{
	case 1:
		sc = new SpriteComponent(this, Assets::getTexture("Brick_1"));
		life = 1;
		break;
	case 2:
		sc = new SpriteComponent(this, Assets::getTexture("Brick_2"));
		life = 2;
		break;
	case 3:
		sc = new SpriteComponent(this, Assets::getTexture("Brick_3"));
		life = 3;
		break;
	case 4:
		sc = new SpriteComponent(this, Assets::getTexture("Brick_4"));
		life = 4;
		break;
	case 5:
		sc = new SpriteComponent(this, Assets::getTexture("Brick_5"));
		life = 5;
		break;
	default:
		break;
	}

	collision = new RectangleCollisionComponent(this);
	collision->setWidth(80.0f);
	collision->setHeigh(20.0f);
}

Brick::~Brick()
{
	//getGame().removeBrick(this);
}

void Brick::updateLife()
{
	life--;
	
	if (life > 0)
	{
		switch (life)
		{
		case 1:
			sc->setTexture(Assets::getTexture("Brick_1"));
			break;
		case 2:
			sc->setTexture(Assets::getTexture("Brick_2"));
			break;
		case 3:
			sc->setTexture(Assets::getTexture("Brick_3"));
			break;
		case 4:
			sc->setTexture(Assets::getTexture("Brick_4"));
			break;
		default:
			break;
		}
	}
	else
	{
		getGame().setScore(getGame().getScore() - 1);
		setState(ActorState::Dead);
		if (getGame().getScore() <= 0)
		{
			getGame().endGame();
		}
	}
}
