#include "Munchie.h"
#include "TextureRenderer.h"
#include "Player.h"
#include "Map.h"

SoundEffect* Munchie::pickupSound;

Munchie::Munchie(TextureRenderer* renderer, Vector2* pos) : BaseObject(renderer, pos)
{
	points = 0;
	collision = TRIGGER;

	if (pickupSound == nullptr)
	{
		Munchie::pickupSound = new SoundEffect();
		Munchie::pickupSound->Load("Sounds/MunchiePickUp.wav");
		Munchie::pickupSound->SetGain(0.1f);
	}
}

Munchie::~Munchie()
{
	delete pickupSound;
}

void Munchie::Update(int elapsedTime)
{
	textureRenderer->currentFrameTime += elapsedTime;

	if (textureRenderer->currentFrameTime > textureRenderer->cFrameTime)
	{
		textureRenderer->frameCount++;

		if (textureRenderer->frameCount >= 2)
		{
			textureRenderer->frameCount = 0;
			textureRenderer->rect->X = 0;
		}
		else
		{
			textureRenderer->rect->X = 24;
		}

		textureRenderer->currentFrameTime = 0;
	}

	BaseObject::Update(elapsedTime);
}

void Munchie::Draw(int elapsedTime)
{
	BaseObject::Draw(elapsedTime);
}

void Munchie::OnCollision(Player* player)
{
	Vector2* gridLoc = player->GetGridLoc();

	if (pickupSound->IsLoaded())
	{
		Audio::Play(pickupSound);
	}
	
	player->game->GetMap()->RemoveObject(gridLoc->Y, gridLoc->X);
	player->game->AddScore(points);
	
	delete gridLoc;
}
