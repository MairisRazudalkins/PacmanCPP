#pragma once
#include "BaseUi.h"
class PacmanUi : public BaseUi
{
	void Init() override;

	StringElement* scoreElem;
	StringElement* highScoreElem;
	ImageElement* livesElem;

	ImageElement* menuLogo;
	ImageElement* textSpriteSheet;
	ImageElement* backgroundImage;

	ImageElement* pauseTextImage;
	StringElement* pauseInfoText;

	SoundEffect* menuMusic;
	
public:
	PacmanUi();
	virtual ~PacmanUi();

	void UpdateScoreText(int score, int highScore);
	void SetMainMenuVisibility(bool visible);
	void SetPauseMenuVisibility(bool visible);
	void UpdateLives(int lives);
};

