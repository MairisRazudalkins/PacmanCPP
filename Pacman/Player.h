#pragma once
#include "BaseObject.h"
#include "Pacman.h"

class Pacman;

enum Direction
{
	UP = 3,
	DOWN = 1,
	RIGHT = 0,
	LEFT = 2
};

class Player : public BaseObject
{
	static const float cPacmanSpeed;
	float speedMultipler;

	int invertTimeStart;
	int invertedCurrentFrameCount;
	static const int invertPeriod;
	
	void SnapLocation();
	void HandleCollisions();
	Vector2* GetVelocityFromDir(Direction& dir);
	
public:
	Player(Pacman* game, TextureRenderer* renderer, Vector2* position);
	void Update(int elapsedTime) override;
	void Draw(int elapsedTime) override;

	void Input(int elapsedTime, Input::KeyboardState* state, Input::MouseState* mouseState);
	void Move(int elapsedTime);
	void OnDeath();
	void InvertPacman(int invertTime, bool inverted = true);
	bool CanMove(Direction& dir);
	bool CheckTile(Vector2* position, Rect* objectRect);
	void CheckViewport();
	Vector2* GetGridLoc();
	
	Direction direction;
	Direction nextDirection;
	Vector2* velocity;
	Pacman* game;
	SoundEffect* chompSound;

	static const int maxLives;
	int lives;

	bool isInverted;

	virtual ~Player();
};