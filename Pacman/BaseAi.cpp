#include "BaseAi.h"
#include "TextureRenderer.h"

BaseAi::BaseAi(TextureRenderer* textureRenderer, Vector2* position) : BaseObject(textureRenderer, position)
{

}

void BaseAi::Update(int elapsedTime)
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