#include "BaseObject.h"
#include "TextureRenderer.h"

BaseObject::BaseObject(TextureRenderer* textureRenderer, Vector2* position)
{
	this->textureRenderer = textureRenderer; this->position = position;
	collision = CollisionType::IMPASSABLE;
}

BaseObject::~BaseObject()
{
	delete position;
	delete textureRenderer;
}

void BaseObject::Draw(int elapsedTime)
{
	SpriteBatch::Draw(textureRenderer->texture, position, textureRenderer->rect, Vector2::Zero, 1.0f, 0.0f, Color::White, SpriteEffect::NONE);
}
