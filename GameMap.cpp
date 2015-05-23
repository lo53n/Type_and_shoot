#include "GameMap.h"

using namespace sf;
using namespace std;
using namespace Style;


void Map::generateMap(){
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			map[i][j] = rand()%19;
		}
	}
}

void Map::initialize(){
	texture.create(800, 640);
	generateMap();
}

void Map::setLayer(){
	texture.display();
	sprite.setTexture(texture.getTexture());
}

void Map::putCommonTile(RectangleShape tile){
	texture.draw(tile);
}

void Map::putRockTile(RectangleShape tile){
	texture.draw(tile);
}

void Map::putUncommonTile(RectangleShape tile){
	texture.draw(tile);
}

