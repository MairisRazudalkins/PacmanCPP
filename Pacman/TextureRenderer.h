#pragma once
#include <string>
#include "S2D/S2D.h"

using namespace S2D;

class TextureRenderer
{
public:
	Texture2D* texture;
	Rect* rect;

	int frameCount;
	int currentFrameTime;
	const int cFrameTime;
	
	TextureRenderer(const char* textureFileName, Rect* sourceRect, int frameTime = 0);
	virtual ~TextureRenderer();
};
