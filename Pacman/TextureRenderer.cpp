#include "TextureRenderer.h"

TextureRenderer::TextureRenderer(const char* textureFileName, Rect* sourceRect, int frameTime) : cFrameTime(frameTime)
{
	texture = new Texture2D();
	texture->Load(textureFileName, false);
	this->rect = sourceRect;
}

TextureRenderer::~TextureRenderer()
{
	delete texture;
	delete rect;
}
