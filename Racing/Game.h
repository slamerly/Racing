#pragma once
#include <vector>
#include "Window.h"
#include "Renderer.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "Grid.h"
#include "Moto.h"

using std::vector;

class Game
{
//Begin singleton
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator = (const Game&) = delete;
	Game(const Game&&) = delete;
	Game& operator = (const Game&&) = delete;

private:
	//Game() = default;
	Game() : isRunning(true), isUpdatingActors(false){}

//End singleton

public:
	bool initialize();
	void load();
	void loop();
	void unload();
	void close();

	void addActor(Actor* actor);
	void removeActor(Actor* actor);

	Renderer& getRenderer() { return renderer; }

	// Game specific
	Moto* getMoto() { return moto; }
	int getScore() { return score; }
	bool getPartyIsEnd() { return partyIsEnd; }

	void setScore(int scoreP);
	void endGame();

private:
	void processInput();
	void update(float dt);
	void render();

	// Game specific
	void newParty();

	Window window {};
	Renderer renderer;
	bool isRunning { true };

	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;

	// Game specific
	Grid* grid;
	Moto* moto;
	int score;
	bool partyIsEnd = false;
};

