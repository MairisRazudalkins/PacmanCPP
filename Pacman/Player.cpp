#include "Player.h"

#include <iostream>

#include "TextureRenderer.h"

const float Player::cPacmanSpeed = 0.1f;
const int Player::maxLives = 3;
const int Player::invertPeriod = 6000; // inverted for 6000 frames

Player::Player(Pacman* game, TextureRenderer* renderer, Vector2* pos) : BaseObject(renderer, pos)
{
	lives = maxLives;
	velocity = new Vector2(1, 0);
	direction = Direction::RIGHT;
	nextDirection = direction;
	speedMultipler = 1;

	chompSound = new SoundEffect();
	chompSound->Load("Sounds/Chomp.wav");
	chompSound->SetGain(0.1f);

	isInverted = false;
	
	this->game = game;
}

void Player::Update(int elapsedTime)
{
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();
	Input::MouseState* mouseState = Input::Mouse::GetState();

	Input(elapsedTime, keyboardState, mouseState);
	Move(elapsedTime);
	CheckViewport();

	if (isInverted)
	{
		invertedCurrentFrameCount += elapsedTime;
		
		if (invertTimeStart + invertPeriod < invertedCurrentFrameCount)
		{
			InvertPacman(elapsedTime, false);
			invertedCurrentFrameCount = 0;
		}
	}
	
	textureRenderer->currentFrameTime += elapsedTime;

	if (textureRenderer->currentFrameTime > textureRenderer->cFrameTime)
	{
		textureRenderer->frameCount++;

		if (textureRenderer->frameCount >= 2)
		{
			textureRenderer->frameCount = 0;
			Audio::Play(chompSound);
		}
		
		textureRenderer->currentFrameTime = 0;
	}
	
	Vector2* gridLoc = GetGridLoc();
	BaseObject* foundObject = game->GetMap()->GetObjectInGrid(gridLoc->Y, gridLoc->X);

	if (foundObject != nullptr)
	{
		if (foundObject->collision == CollisionType::TRIGGER)
		{
			foundObject->OnCollision(this);
		}
	}
	 
	delete gridLoc;
	//BaseObject::Update(elapsedTime);
}

void Player::Draw(int elapsedTime)
{
	textureRenderer->rect->Y = textureRenderer->rect->Height * direction;
	
	if (textureRenderer->frameCount == 0)
		textureRenderer->rect->X = 0.0f;
	else
		textureRenderer->rect->X = textureRenderer->rect->Width;
	
	BaseObject::Draw(elapsedTime);
}

void Player::Input(int elapsedTime, Input::KeyboardState* state, Input::MouseState* mouseState)
{
	speedMultipler = state->IsKeyDown(Input::Keys::LEFTSHIFT) ? 2.0f : 1.0f;

	if (state->IsKeyDown(Input::Keys::D))
	{
		nextDirection = Direction::RIGHT;
	}
	else if (state->IsKeyDown(Input::Keys::A))
	{
		nextDirection = Direction::LEFT;
	}
	else if (state->IsKeyDown(Input::Keys::S))
	{
		nextDirection = Direction::DOWN;
	}
	else if (state->IsKeyDown(Input::Keys::W))
	{
		nextDirection = Direction::UP;
	}

	if (state->IsKeyDown(Input::Keys::J))
	{
		OnDeath();
	}
}

void Player::Move(int elapsedTime)
{
	float pacmanSpeed = cPacmanSpeed * elapsedTime * speedMultipler;

	if (direction != nextDirection)
	{
		Vector2* gridLoc = GetGridLoc();

		if (position->X < 5 || position->X > Graphics::GetViewportWidth() - textureRenderer->rect->Width)
		{
			nextDirection = direction;
		}		
		else if (CanMove(nextDirection))
		{
			velocity = GetVelocityFromDir(nextDirection);
			direction = nextDirection;
		}

		delete gridLoc;
	}
	
	if (CanMove(direction))
	{
		position->X += velocity->X * pacmanSpeed;
		position->Y += velocity->Y * pacmanSpeed;
	}

	SnapLocation();
}

void Player::OnDeath()
{
	lives--;
	isInverted = false;

	game->RestartGame(lives);
}

void Player::InvertPacman(int invertTime, bool inverted)
{
	isInverted = inverted;
	
	if (inverted)
	{
		invertTimeStart = invertTime;
		textureRenderer->texture = new Texture2D();
		textureRenderer->texture->Load("Textures/PacmanInverted.png", false);
	}
	else
	{
		textureRenderer->texture = new Texture2D();
		textureRenderer->texture->Load("Textures/Pacman.png", false);
	}
}

bool Player::CanMove(Direction& dir)
{
	Vector2* gridLoc = GetGridLoc();

	if (dir == Direction::RIGHT)
	{
		gridLoc->X = ceil(position->X) / 24;
		gridLoc->X += 1;
	}
	else if (dir == Direction::LEFT)
	{
		gridLoc->X = ceil(position->X + 23) / 24;
		gridLoc->X -= 1;
	}
	else if (dir == Direction::UP)
	{
		gridLoc->Y = ceil(position->Y + 23) / 24;
		gridLoc->Y -= 1;
	}
	else if (dir == Direction::DOWN)
	{
		gridLoc->Y = ceil(position->Y) / 24;
		gridLoc->Y += 1;
	}

	if (gridLoc->X <= -1 || gridLoc->X >= game->GetMap()->GetWidth())
	{
		return true;
	}
	
	if (game->GetMap()->GetCollisionType(gridLoc->Y, gridLoc->X) == CollisionType::IMPASSABLE)
	{
		delete gridLoc;
		return false;
	}

	delete gridLoc;
	return true;
}

void Player::SnapLocation()
{
	if (direction == Direction::RIGHT || direction == Direction::LEFT)
	{
		position->Y = (int(position->Y + 12) / 24) * 24;
	}
	else if (direction == Direction::UP || direction == Direction::DOWN)
	{
		position->X = (int(position->X + 12) / 24) * 24;
	}
}

Vector2* Player::GetGridLoc()
{
	int gridLocX = int(position->X + 12) / 24;
	int gridLocY = int(position->Y + 12) / 24;
	
	int clampX = gridLocX < 0 ? 0 : gridLocX > game->GetMap()->GetWidth() - 1 ? game->GetMap()->GetWidth() - 1 : gridLocX;
	int clampY = gridLocY < 0 ? 0 : gridLocY > game->GetMap()->GetHeight() - 1? game->GetMap()->GetHeight() - 1 : gridLocY;
	
	return new Vector2(clampX, clampY);
}

Player::~Player()
{
	delete velocity;
	delete game;
}

Vector2* Player::GetVelocityFromDir(Direction& dir)
{
	if (dir == Direction::RIGHT)
	{
		return new Vector2(1, 0);
	}
	else if (dir == Direction::LEFT)
	{
		return new Vector2(-1, 0);
	}
	else if (dir == Direction::UP)
	{
		return new Vector2(0, -1);
	}
	else // down
	{
		return new Vector2(0, 1);
	}
}

void Player::CheckViewport()
{
	if (position->X > Graphics::GetViewportWidth())
		position->X = 0 - textureRenderer->rect->Width;
	else if (position->X < 0 - textureRenderer->rect->Width)
		position->X = Graphics::GetViewportWidth();

	if (position->Y > Graphics::GetViewportHeight() - textureRenderer->rect->Height)
		position->Y = 0 - textureRenderer->rect->Height;
	else if (position->Y < 0 - textureRenderer->rect->Height)
		position->Y = Graphics::GetViewportHeight() + textureRenderer->rect->Height;
}
