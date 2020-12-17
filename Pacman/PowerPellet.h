#pragma once
#include "Munchie.h"
class PowerPellet : public Munchie
{

public:
	PowerPellet(TextureRenderer* renderer, Vector2* position);
	int elapsedTime;
	
	void Update(int elapsedTime) override;
	void OnCollision(Player* player) override;
};

