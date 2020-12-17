#include "BaseUi.h"

BaseUi::BaseUi()
{
	Init();
}

void BaseUi::Draw(int elapsedTime)
{
	if (!visualElements->empty())
	{
		for (int i = 0; i < visualElements->size(); i++)
		{
			visualElements->at(i)->Draw(elapsedTime);
		}
	}
	
	if (!stringElements->empty())
	{
		for (int i = 0; i < stringElements->size(); i++)
		{
			stringElements->at(i)->Draw();
		}
	}
}

void BaseUi::Init()
{
	visualElements = new vector<ImageElement*>;
	stringElements = new vector<StringElement*>;
}

BaseUi::~BaseUi()
{
	for (int i = 0; i < visualElements->size(); i++)
	{
		delete visualElements[i].at(i);
	}

	for (int i = 0; i < stringElements->size(); i++)
	{
		delete stringElements[i].at(i);
	}

	delete visualElements;
	delete stringElements;
}

ImageElement::ImageElement(string name, TextureRenderer* textureRenderer, Vector2* position, bool isVisible)
{
	this->name = name;
	this->textureRenderer = textureRenderer;
	this->position = position;
	this->isVisible = isVisible;
}

ImageElement::~ImageElement()
{
	delete position;
	delete textureRenderer;
}

void ImageElement::Draw(int elapsedTime)
{
	if (!isVisible)
	{
		return;
	}
	
	if (textureRenderer->cFrameTime > 0)
	{
		textureRenderer->currentFrameTime += elapsedTime;

		if (textureRenderer->currentFrameTime > textureRenderer->cFrameTime)
		{
			textureRenderer->frameCount++;

			if (textureRenderer->frameCount >= 2)
			{
				textureRenderer->frameCount = 0;
				textureRenderer->rect->Y = 0;
			}
			else
			{
				textureRenderer->rect->Y = textureRenderer->rect->Height;
			}

			textureRenderer->currentFrameTime = 0;
		}
	}

	SpriteBatch::Draw(textureRenderer->texture, position, textureRenderer->rect, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);
}

StringElement::StringElement(string name, const string text, Vector2* position, Color* color, bool isVisible)
{
	this->name = name;
	this->text = text;
	this->position = position;
	this->color = color;
	this->isVisible = isVisible;
}

StringElement::~StringElement()
{
	delete position;
	delete color;
}

void StringElement::Draw()
{
	if (isVisible)
	{
		SpriteBatch::DrawString(text.c_str(), position, color);
	}
}
