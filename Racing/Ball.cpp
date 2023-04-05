#include "Ball.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "Window.h"
#include "Game.h"
#include <iostream>

Ball::Ball() : 
	Actor()
{
	SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Ball"));

	move = new MoveComponent(this);
	move->setUpSpeed(150);

	collision = new CircleCollisionComponent(this);
	collision->setRadius(10.0f);

	life = 3;
}

void Ball::updateActor(float dt)
{
	if (ballLock)
	{
		//setPosition({ getGame().getPaddle()->getPosition().x, getGame().getPaddle()->getPosition().y - 25 });
	}
	else
	{
		if (!getGame().getPartyIsEnd())
			ballMovement();
		else
		{
			move->setForwardSpeed(0);
			move->setUpSpeed(0);
		}
	}
}

void Ball::ballMovement()
{
	//touch paddle
	/*
	if (Intersect(*collision, getGame().getPaddle()->getCollision()))
	{
		Vector2 aCenter = collision->getCenter();
		Vector2 bCenter = Vector2::zero;
		if(Intersect(*collision, getGame().getPaddle()->getCollision()))
			bCenter = getGame().getPaddle()->getCollision().getCenter();
		
		Vector2 ab = bCenter - aCenter;

		std::cout << ab.x << ", " << ab.y << std::endl;

		if (ab.y >= 10)
		{
			if (ab.x > 45)
				move->setForwardSpeed(-200);
			if (ab.x <= 45 && ab.x > 35)
				move->setForwardSpeed(-160);
			if (ab.x <= 35 && ab.x > 25)
				move->setForwardSpeed(-120);
			if (ab.x <= 25 && ab.x > 15)
				move->setForwardSpeed(-80);
			if (ab.x <= 15 && ab.x > 5)
				move->setForwardSpeed(-40);
			if (ab.x <= 5 && ab.x >= -5)
				move->setForwardSpeed(0);
			if (ab.x < -5 && ab.x >= -15)
				move->setForwardSpeed(40);
			if (ab.x < -15 && ab.x >= -25)
				move->setForwardSpeed(80);
			if (ab.x < -25 && ab.x >= -35)
				move->setForwardSpeed(120);
			if (ab.x < -35 && ab.x >= -45)
				move->setForwardSpeed(160);
			if (ab.x < -45)
				move->setForwardSpeed(200);
		}
		//Side
		if (ab.y < 10 && ab.y >= 0)
		{
			if (ab.x > 49)
				move->setForwardSpeed(-240);
			if (ab.x < -49)
				move->setForwardSpeed(240);
		}

		move->setUpSpeed(move->getUpSpeed() * -1);
	}
	*/

	// Bricks
	/*
	for (auto& brickVec : getGame().getBricks())
	{
		for (auto brick : brickVec)
		{
			if (brick != nullptr)
			{
				if (Intersect(*collision, brick->getCollision()))
				{
					Vector2 aCenter = collision->getCenter();
					Vector2 bCenter = Vector2::zero;

					if (Intersect(*collision, brick->getCollision()))
						bCenter = brick->getCollision().getCenter();

					Vector2 ab = bCenter - aCenter;

					std::cout << ab.x << ", " << ab.y << std::endl;


					if (ab.y <= 20 && ab.y >= -20)
					{
						std::cout << "relou" << std::endl;
						if (ab.x > 20)
							move->setForwardSpeed(-160);
						if (ab.x <= 20 && ab.x >= 0)
							move->setForwardSpeed(-80);
						if (ab.x <= -20 && ab.x > 0)
							move->setForwardSpeed(80);
						if (ab.x < -20)
							move->setForwardSpeed(160);

						move->setUpSpeed(move->getUpSpeed() * -1);
					}

					//Side
					if (ab.y < 20 && ab.y > 0)
					{
						if (ab.x > 49)
							move->setForwardSpeed(-240);
						if (ab.x < -49)
							move->setForwardSpeed(240);

						if (move->getUpSpeed() < 0)
							move->setUpSpeed(move->getUpSpeed() * -1);
					}
					if (ab.y <= 0 && ab.y >= -20)
					{
						if (ab.x > 49)
							move->setForwardSpeed(-240);
						if (ab.x < -49)
							move->setForwardSpeed(240);

						if (move->getUpSpeed() > 0)
							move->setUpSpeed(move->getUpSpeed() * -1);
					}

					brick->updateLife();
				}
			}
		}
	}
	*/

	//touch left & right side
	if (getPosition().x <= (WINDOW_WIDTH / 6) + 5 || getPosition().x >= (WINDOW_WIDTH / 6) * 5)
	{
		move->setForwardSpeed(move->getForwardSpeed() * -1);
	}
	//touch top & down side
	if (getPosition().y <= 10 || getPosition().y >= WINDOW_HEIGHT - 10)
	{
		if (getPosition().y >= WINDOW_HEIGHT - 10)
		{
			life--;
			if (life > 0)
			{
				move->setUpSpeed(150);
				move->setForwardSpeed(0);
				ballLock = true;
			}
			else
			{
				std::cout << "You lose" << std::endl;
				getGame().endGame();
			}
		}
		else
			move->setUpSpeed(move->getUpSpeed() * -1);
	}
}

void Ball::ballReset()
{
	ballLock = true;
}

void Ball::setBallLock(bool ballstate)
{
	ballLock = ballstate;
}

void Ball::setlife(int lifeP)
{
	life = lifeP;
}
