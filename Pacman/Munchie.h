#pragma once
#include "BaseObject.h"

enum MunchieType
{
	PacDot,
	PowerPellet,
	Cherry,
	Strawberry
};

class Munchie : public BaseObject
{

public:
	Munchie(TextureRenderer* renderer, Vector2* position);

	static SoundEffect* pickupSound;
	
	int points;
	
	void Update(int elapsedTime) override;
	void Draw(int elapsedTime) override;
	void OnCollision(Player* player) override;
	virtual ~Munchie();
};

