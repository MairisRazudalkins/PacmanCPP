#pragma once
#include "BaseObject.h"
class BaseAi : public BaseObject
{


public:
	BaseAi(TextureRenderer* textureRenderer, Vector2* position);

	void Update(int elapsedTime) override;
	virtual ~BaseAi(){};
};

