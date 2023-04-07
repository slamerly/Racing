#include "Game.h"
#include "Timer.h"
#include "Assets.h"
#include "AnimSpriteComponent.h"
#include "BackgroundSpriteComponent.h"
#include <iostream>
#include "Maths.h"

bool Game::initialize()
{
    bool isWindowInit = window.initialize();
    bool isRenderInit = renderer.initialize(window);
    return isWindowInit && isRenderInit;
}

void Game::load()
{
    // Load textures
    Assets::loadTexture(renderer, "Res\\building.png", "Building");
    Assets::loadTexture(renderer, "Res\\tree.png", "Tree");
    Assets::loadTexture(renderer, "Res\\border.png", "Border");
    Assets::loadTexture(renderer, "Res\\moto2.png", "Moto");

    srand(time(nullptr));

    vector<vector<int>> circuit
    {   { 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
        { 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
        { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 1, 1, 1, 1, 2, 2, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1 },
        { 1, 0, 0, 1, 1, 0, 0, 1, 1, 3, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1 },
        { 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1 },
        { 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1 },
        { 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 },
        { 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 },
        { 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1 },
        { 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 1, 2, 1, 1, 1, 1, 1, 3, 1, 0, 0, 0, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 3, 3, 2, 3, 2, 2, 2, 1, 1, 1, 1, 1, 3 }
    };

    //grid = new Grid();
    grid = new Grid(&circuit);

    moto = new Moto();
    moto->setPosition({ 80, 400 });
    moto->setRotation(Maths::toRadians(90));
    //moto->setRotation(1.57f);    
    
    score = 8 * 6;
}

void Game::loop()
{
    Timer timer;
    float dt = 0;
    while (isRunning)
    {
        float dt = timer.computeDeltaTime() / 1000.0f;
        processInput();
        update(dt);
        render();
        timer.delayTime();
    }
}

void Game::unload()
{
    // Delete actors
    // Because ~Actor calls RemoveActor, have to use a different style loop
    while (!actors.empty())
    {
        delete actors.back();
    }

    // Resources
    Assets::clear();
}

void Game::close()
{
    renderer.close();
    window.close();
    SDL_Quit();
}

void Game::addActor(Actor* actor)
{
    if (isUpdatingActors)
    {
        pendingActors.emplace_back(actor);
    }
    else
    {
        actors.emplace_back(actor);
    }
}

void Game::removeActor(Actor* actor)
{
    // Erase actor from the two vectors
    auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
    if (iter != end(pendingActors))
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, end(pendingActors) - 1);
        pendingActors.pop_back();
    }
    iter = std::find(begin(actors), end(actors), actor);
    if (iter != end(actors))
    {
        std::iter_swap(iter, end(actors) - 1);
        actors.pop_back();
    }
}

void Game::setScore(int scoreP)
{
    score = scoreP;
}

void Game::endGame()
{
    partyIsEnd = true;
    //ball->setBallLock(true);
    std::cout << "Press ENTER to reset" << std::endl << std::endl;
}

void Game::processInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        }
    }

    // Keyboard status
    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

    if (keyboardState[SDL_SCANCODE_ESCAPE])
    {
        isRunning = false;
    }

    if (keyboardState[SDL_SCANCODE_RETURN] && partyIsEnd)
    {
        std::cout << "rest" << std::endl;
        newParty();
    }

    // Game newParty
    /*
    if (keyboardState[SDL_SCANCODE_SPACE] && getBall()->getBallLock())
    {
        std::cout << "space" << std::endl;
        getBall()->setBallLock(false);
    }
    */

    // Actor input
    isUpdatingActors = true;
    for (auto actor : actors)
    {
        if(!partyIsEnd)
            actor->processInput(keyboardState);
    }
    isUpdatingActors = false;
}

void Game::update(float dt)
{
    // Update actors 
    isUpdatingActors = true;
    for (auto actor : actors)
    {
        actor->update(dt);
    }
    isUpdatingActors = false;

    // Move pending actors to actors
    for (auto pendingActor : pendingActors)
    {
        actors.emplace_back(pendingActor);
    }
    pendingActors.clear();

    // Delete dead actors
    vector<Actor*> deadActors;
    for (auto actor : actors)
    {
        if (actor->getState() == Actor::ActorState::Dead)
        {
            deadActors.emplace_back(actor);
        }
    }
    for (auto deadActor : deadActors)
    {
        delete deadActor;
    }
}

void Game::render()
{
    renderer.beginDraw();
    renderer.draw();
    renderer.endDraw();
}

void Game::newParty()
{
    /*
    score = 6 * 8;
    partyIsEnd = false;

    for (auto vectBrick : bricks)
    {
        for (auto brick : vectBrick)
        {
            if (brick)
            {
                brick->~Brick();
            }
        }
        vectBrick.clear();
    }
    bricks.clear();

    ball->getMove()->setUpSpeed(ball->getMove()->getUpSpeed() * -1);
    ball->setlife(3);

    loadBricks();

    paddle->setPosition({ WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50 });
    */
}
