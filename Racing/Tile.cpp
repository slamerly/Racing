#include "Tile.h"
#include "Assets.h"

Tile::Tile() :
	Actor(), sprite(nullptr), tileState(TileState::Default), isSelected(false)
{
	sprite = nullptr;
}

void Tile::setTileState(TileState tileStateP)
{
	tileState = tileStateP;
	updateTexture();
}

void Tile::toggleSelect()
{
	isSelected = !isSelected;
	updateTexture();
}

void Tile::updateTexture()
{
	switch (tileState)
	{
	case Tile::TileState::Border:
		if (sprite == nullptr)
			sprite = new SpriteComponent(this, Assets::getTexture("Border"));
		else
			sprite->setTexture(Assets::getTexture("Border"));
		break;
	case Tile::TileState::Building:
		if (sprite == nullptr)
			sprite = new SpriteComponent(this, Assets::getTexture("Building"));
		else
			sprite->setTexture(Assets::getTexture("Building"));
		break;
	case Tile::TileState::Tree:
		if (sprite == nullptr)
			sprite = new SpriteComponent(this, Assets::getTexture("Tree"));
		else
			sprite->setTexture(Assets::getTexture("Tree"));
		break;
	case Tile::TileState::Default:
	default:
		sprite = nullptr;
		break;
	}
}
