#include "PowerPellet.h"
#include "Player.h"

PowerPellet::PowerPellet(TextureRenderer* renderer, Vector2* position) : Munchie(renderer, position)
{
	elapsedTime = 0;
}

void PowerPellet::Update(int elapsedTime)
{
	this->elapsedTime = elapsedTime;
	Munchie::Update(elapsedTime);
}

void PowerPellet::OnCollision(Player* player)
{
	player->InvertPacman(elapsedTime);
	Munchie::OnCollision(player);
}
