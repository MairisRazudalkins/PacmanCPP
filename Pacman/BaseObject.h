#pragma once
#include <iostream>

#include "S2D/S2D.h"

class TextureRenderer;
class Player;

using namespace S2D;

#ifndef BASEOBJECT_H
#define BASEOBJECT_H

enum CollisionType
{
	TRIGGER,
	IMPASSABLE,
	NONE
};

class BaseObject
{
	
public:
	BaseObject(TextureRenderer* textureRenderer, Vector2* position);

	TextureRenderer* textureRenderer;
	Vector2* position;
	CollisionType collision;
	bool shouldUpdate = true;

	virtual void Update(int elapsedTime){}
	virtual void Draw(int elapsedTime);
	virtual void OnCollision(Player* player) {}
	
	virtual ~BaseObject();
};

#endif