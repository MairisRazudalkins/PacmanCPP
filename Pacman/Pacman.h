#pragma once
#ifdef WIN32 
	#ifndef _DEBUG
		#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	#endif
#endif

#include "S2D/S2D.h"
#include "Map.h"

class PacmanUi;
class PacmanMainMenu;

using namespace S2D;

class Pacman : public Game
{
private:
	void CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey);
	void LoadHighScore();
	void SaveHighScore();

	Player* pacman;
	Map* map;
	PacmanUi* pacmanUi;

	int highScore;
	int score;
	
	bool started;
	bool paused;
	bool pKeyDown;

public:
	Pacman(int argc, char* argv[]);
	
	void virtual LoadContent();
	void virtual Update(int elapsedTime);
	void virtual Draw(int elapsedTime);
	virtual ~Pacman();
	
	void AddScore(int amount);
	void RestartGame(int lives);
	Map* GetMap() { return map; }
	int GetHighScore() { return highScore; }
};