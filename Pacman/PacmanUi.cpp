#include "PacmanUi.h"
#include "Player.h"

PacmanUi::PacmanUi()
{
	menuMusic = new SoundEffect();
	menuMusic->Load("Sounds/IntroMusic.wav");
	menuMusic->SetGain(0.1f);
	menuMusic->SetLooping(true);
	Audio::Play(menuMusic);
	
	Init();
}

PacmanUi::~PacmanUi()
{
	delete menuLogo;
	delete backgroundImage;
	delete textSpriteSheet;
	
	delete scoreElem;
	delete livesElem;
	delete highScoreElem;

	delete pauseTextImage;
	delete pauseInfoText;
	
	delete menuMusic;
}

void PacmanUi::Init()
{
	menuLogo = new ImageElement("MenuLogo", new TextureRenderer("Textures/MainMenu/MenuLogo.png", new Rect(0, 0, Graphics::GetViewportWidth(), 150)), new Vector2(0, 100));
	backgroundImage = new ImageElement("BackgroundImage", new TextureRenderer("Textures/MainMenu/MenuBackground.png", new Rect(0, 0, Graphics::GetViewportWidth(), Graphics::GetViewportHeight())), new Vector2(0, 0));
	textSpriteSheet = new ImageElement("InfoText", new TextureRenderer("Textures/MainMenu/MenuTextSpriteSheet.png", new Rect(0, 0, 672, 50), 250), new Vector2(0, Graphics::GetViewportHeight() / 2));

	AddImageElem(backgroundImage);
	AddImageElem(menuLogo);
	AddImageElem(textSpriteSheet);
		
	livesElem = new ImageElement("LivesElement", new TextureRenderer("Textures/PacmanIcon.png", new Rect(0, 0, Player::maxLives * 24, 24)), new Vector2(24, Graphics::GetViewportHeight() - 21));
	scoreElem = new StringElement("ScoreText", "Score: 0", new Vector2(livesElem->position->X + livesElem->textureRenderer->rect->Width + 50, Graphics::GetViewportHeight() - 2), new Color(255, 255, 255));
	highScoreElem = new StringElement("ScoreText", "High Score: 0", new Vector2(scoreElem->position->X + 200, Graphics::GetViewportHeight() - 2), new Color(255, 255, 255));
	
	AddStringElem(scoreElem);
	AddStringElem(highScoreElem);
	AddImageElem(livesElem);

	pauseTextImage = new ImageElement("PauseText", new TextureRenderer("Textures/MainMenu/PauseText.png", new Rect(0, 0, 672, 50)), new Vector2(0, Graphics::GetViewportHeight() / 2), false);
	pauseInfoText = new StringElement("PauseInfoText", "Press 'p' To Unpause", new Vector2(250, pauseTextImage->position->Y + 75), new Color(255, 255, 255), false);

	AddImageElem(pauseTextImage);
	AddStringElem(pauseInfoText);
}

void PacmanUi::UpdateScoreText(int score, int highScore)
{
	scoreElem->text = "Score: " + std::to_string(score);
	highScoreElem->text = "High Score: " + std::to_string(highScore);
}

void PacmanUi::SetMainMenuVisibility(bool visible)
{
	if (visible)
		Audio::Play(menuMusic);
	else
		Audio::Stop(menuMusic);
	
	menuLogo->isVisible = visible;
	backgroundImage->isVisible = visible;
	textSpriteSheet->isVisible = visible;
}

void PacmanUi::SetPauseMenuVisibility(bool visible)
{
	if (visible)
		Audio::Play(menuMusic);
	else
		Audio::Stop(menuMusic);

	menuLogo->isVisible = visible;
	backgroundImage->isVisible = visible;
	pauseTextImage->isVisible = visible;
	pauseInfoText->isVisible = visible;
}

void PacmanUi::UpdateLives(int lives)
{
	livesElem->textureRenderer->rect = new Rect(0, 0, lives * 24, 24);
}

