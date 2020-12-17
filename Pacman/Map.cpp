#include <ctime>
#include <fstream>

#include "S2D/S2D.h"
#include "TextureRenderer.h"
#include "PowerPellet.h"
#include "Player.h"
#include "Map.h"
#include "BaseAi.h"

using namespace std;

Map::Map(Pacman* game) : tileSize(24)
{
	this->game = game;
	
	munchieCount = 0;
	GenerateMap();
}

Map::~Map()
{
	std::cout << "Exiting";
	
	for (int y = 0; y < mapData->size(); ++y)
	{
		for (int x = 0; x < mapData->at(0).size(); ++x)
		{
			if ((*mapData)[y][x] != nullptr)
			{
				delete (*mapData)[y][x];
			}
		}
	}

	delete mapData;
}

void Map::GenerateMap()
{
	int mapRowCount = 0;
	vector<string>* lines = new vector<string>;
	ifstream mapFile("Data/Level_0.txt");
	string line;

	srand(time(NULL));
	
	while (getline(mapFile, line)) 
	{		
		lines->push_back(line);	
		mapRowCount++;
	}

	mapData = new vector<vector<BaseObject*>>(mapRowCount, vector<BaseObject*>(lines->size()));
	ghosts = new vector<BaseAi*>();
	
	for (int y = 0; y < mapRowCount; ++y)
	{
		for (int x = 0; x < lines->at(0).size(); ++x)
		{
			char tileType = lines->at(y)[x];
			
			if (tileType == '#')
			{
				(*mapData)[y][x] = LoadTile<BaseObject>("Textures/Tiles/Tile_0.png", new Vector2(x * tileSize, y * tileSize));
			}
			else if (tileType == '.') //pac-dot
			{
				if (rand() % 100 < 2)
				{
					(*mapData)[y][x] = LoadTile<Munchie>("Textures/CherrySpriteSheet.png", new Vector2(x * tileSize, y * tileSize), 300);
					dynamic_cast<Munchie*>(mapData->at(y)[x])->points = 150;
					munchieCount++;
				}
				else
				{
					(*mapData)[y][x] = LoadTile<Munchie>("Textures/PacDot.png", new Vector2(x * tileSize, y * tileSize));
					dynamic_cast<Munchie*>(mapData->at(y)[x])->points = 10;
					munchieCount++;
				}
			}
			else if (tileType == 'o') //power pellet
			{
				(*mapData)[y][x] = LoadTile<class PowerPellet>("Textures/MunchieSpriteSheet.png", new Vector2(x * tileSize, y * tileSize));
				dynamic_cast<Munchie*>(mapData->at(y)[x])->points = 50;
				munchieCount++;
			}
			else if (tileType == '1')
			{
				(*mapData)[y][x] = LoadTile<BaseAi>("Textures/CyanGhost.png", new Vector2(x * tileSize, y * tileSize), 250);
			}
			else if (tileType == '2')
			{
				(*mapData)[y][x] = LoadTile<BaseAi>("Textures/RedGhost.png", new Vector2(x * tileSize, y * tileSize), 250);
			}
			else if (tileType == '3')
			{
				(*mapData)[y][x] = LoadTile<BaseAi>("Textures/PinkGhost.png", new Vector2(x * tileSize, y * tileSize), 250);
			}
			else if (tileType == '4')
			{
				(*mapData)[y][x] = LoadTile<BaseAi>("Textures/OrangeGhost.png", new Vector2(x * tileSize, y * tileSize), 250);
			}
		}
	}

	mapFile.close();
	delete lines;
}

template <class childOfBaseObject>
BaseObject* Map::LoadTile(std::string name, Vector2* position, int frameTime)
{
	if (!name.empty())
	{
		const char* cName = name.c_str();
		
		return new childOfBaseObject(new TextureRenderer(cName, new Rect(0.0f, 0.0f, tileSize, tileSize), frameTime), position);
	}

	return nullptr;
}

void Map::Draw(int elapsedTime)
{
	for (int y = 0; y < mapData->size(); ++y)
	{
		for (int x = 0; x < mapData->at(0).size(); ++x)
		{
			if ((*mapData)[y][x] != nullptr)
			{
				(*mapData)[y][x]->Draw(elapsedTime);
			}
		}
	}
}

void Map::Update(int elapsedTime)
{
	for (int y = 0; y < mapData->size(); ++y)
	{
		for (int x = 0; x < mapData->at(0).size(); ++x)
		{
			if ((*mapData)[y][x] != nullptr)
			{
				(*mapData)[y][x]->Update(elapsedTime);
			}
		}
	}
}

CollisionType Map::GetCollisionType(int y, int x)
{
	if (y < 0 || x < 0 || y > GetHeight() - 1 || x > GetWidth() - 1)
	{
		return NONE;
	}
	
	BaseObject* object = mapData->at(y)[x];

	if (object != nullptr)
	{
		return object->collision;
	}
	
	return NONE;
}

BaseObject* Map::GetObjectInGrid(int y, int x)
{
	if (y < 0 || x < 0 || y > GetHeight() - 1 || x > GetWidth() - 1)
	{
		return nullptr;
	}

	BaseObject* object = mapData->at(y)[x];

	if (object != nullptr)
	{
		return object;
	}

	return nullptr;
}

void Map::RemoveObject(int y, int x)
{
	if (y < 0 || x < 0 || y > GetHeight() - 1 || x > GetWidth() - 1)
	{
		return;
	}

	mapData->at(y)[x] = nullptr;
}
