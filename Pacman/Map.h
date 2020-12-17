#pragma once
#include <string>
#include <vector>

#include "BaseAi.h"
#include "BaseObject.h"

namespace S2D {
	class Rect;
	class Vector2;
}

class Munchie;
class Pacman;
class Player;

class Map
{
	void GenerateMap();
	string GetTileName(char tileType);
	
	template <class childOfBaseObject>
	BaseObject* LoadTile(string name, S2D::Vector2* position, int frameTime = 500);
	
public:
	Map(Pacman* game);
	void Draw(int elapsedTime);
	void Update(int elapsedTime);
	void RemoveObject(int y, int x);
	CollisionType GetCollisionType(int y, int x);
	BaseObject* GetObjectInGrid(int y, int x);

	int GetHeight() { return mapData->size(); }
	int GetWidth() { return mapData->at(0).size(); }

	Player* pacman;
	Pacman* game;
	
	string baseLevel;
	vector<std::vector<BaseObject*>>* mapData;
	vector<BaseAi*>* ghosts;

	const int tileSize;
	int munchieCount;
	
	virtual ~Map();
};