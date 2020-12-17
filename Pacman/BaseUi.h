#pragma once
#include <string>
#include "TextureRenderer.h"

struct StringElement
{
	string name;
	string text;
	Vector2* position;
	Color* color;
	bool isVisible;

	StringElement(string name, string text, Vector2* position, Color* color, bool isVisible = true);
	~StringElement();

	void Draw();
};

struct ImageElement
{
	string name;
	Vector2* position;
	TextureRenderer* textureRenderer;
	bool isVisible;

	ImageElement(string name, TextureRenderer* textureRenderer, Vector2* position, bool isVisible = true);
	~ImageElement();

	void Draw(int elapsedTime);
};

class BaseUi
{
	vector<ImageElement*>* visualElements;
	vector<StringElement*>* stringElements;
	
public:
	BaseUi();
	
	StringElement* GetStringElem(string name);
	ImageElement* GetImageElem(string name);

	void AddImageElem(ImageElement* elem) { visualElements->push_back(elem); }
	void AddStringElem(StringElement* elem) { stringElements->push_back(elem); }
	
	void Draw(int elapsedTime);
	virtual void Init();
	virtual ~BaseUi();
};

