#include <iostream>
#include <fstream>
#include "Pacman.h"
#include "PacmanUi.h"
#include "Player.h"

Pacman::Pacman(int argc, char* argv[]) : Game(argc, argv), pKeyDown(false), started(false)
{
	paused = true;
	started = false;
	score = 0;
	highScore = 0;

	LoadHighScore();

	Audio::Initialise();
	Graphics::Initialise(argc, argv, this, 672, 764, false, (1920/2) - (672/2), 100, "Pacman", 60);
	Input::Initialise();
	Graphics::StartGameLoop();
}

Pacman::~Pacman()
{
	delete map;
	delete pacman;
	delete pacmanUi;
}

void Pacman::AddScore(int amount)
{
	score += amount;
	
	if (score > highScore)
		highScore = score;
	
	pacmanUi->UpdateScoreText(score, highScore);
	map->munchieCount--;
	
	if (map->munchieCount <= 0)
	{
		if (score >= highScore)
			SaveHighScore();

		RestartGame(pacman->lives);
	}
}

void Pacman::LoadContent()
{
	pacman = new Player(this, new TextureRenderer("Textures/Pacman.png", new Rect(0.0f, 0.0f, 24, 24), 200), new Vector2(312, 552));
	map = new Map(this);
	pacmanUi = new PacmanUi();
	
	pacmanUi->UpdateScoreText(score, highScore);
}

void Pacman::Update(int elapsedTime)
{
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();
	
	if (started)
	{
		CheckPaused(keyboardState, Input::Keys::P);
		
		if (!paused)
		{
			pacman->Update(elapsedTime);
			map->Update(elapsedTime);
		}
	}
	else if(keyboardState->IsKeyDown(Input::Keys::SPACE))
	{
		started = true;
		paused = false;
		pacmanUi->SetMainMenuVisibility(false);
	}
}

void Pacman::Draw(int elapsedTime)
{
	SpriteBatch::BeginDraw();
	
	map->Draw(elapsedTime);
	pacman->Draw(elapsedTime);
	pacmanUi->Draw(elapsedTime);
	
	SpriteBatch::EndDraw();
}

void Pacman::CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey)
{
	if (state->IsKeyDown(Input::Keys::P) && !pKeyDown)
	{
		pKeyDown = true;
		paused = !paused;
		
		pacmanUi->SetPauseMenuVisibility(paused);
	}
	if (state->IsKeyUp(Input::Keys::P))
	{
		pKeyDown = false;
	}
}

void Pacman::RestartGame(int lives)
{
	SaveHighScore();
	pacmanUi->UpdateLives(lives);
	
	if (lives <= 0)
	{
		paused = true;
		started = false;
		score = 0;

		map = new Map(this);
		pacman = new Player(this, new TextureRenderer("Textures/Pacman.png", new Rect(0.0f, 0.0f, 24, 24), 200), new Vector2(312, 552));
		pacmanUi = new PacmanUi();
	}
	else
	{
		pacman->position = new Vector2(312, 552);
		pacman->InvertPacman(0, false); // if is inverted then set inverted false;
		map = new Map(this);
	}
}

void Pacman::LoadHighScore()
{
	ifstream streamIn;
	streamIn.open("Data/HighScore.txt");

	if (!streamIn.is_open())
	{
		cout << "Failed to load save file!";
		return;
	}
	
	string scoreString;
	getline(streamIn, scoreString);
	highScore = stoi(scoreString);
	
	streamIn.close();
}

void Pacman::SaveHighScore()
{
	ofstream streamOut;
	streamOut.open("Data/HighScore.txt");

	if (!streamOut.is_open())
		return;

	streamOut.clear();
	streamOut << highScore;
	
	streamOut.close();
}


