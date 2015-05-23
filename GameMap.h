#ifndef GameMap
#define GameMap

#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace sf;
using namespace std;

class Map : public Drawable {

private:


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(sprite);
	}

public:
	int map[25][20];
	RenderTexture texture;
	Sprite sprite;

	Map(){};
	~Map(){};

	void generateMap();
	void initialize();

	void putCommonTile(RectangleShape tile);
	void putRockTile(RectangleShape tile);
	void putUncommonTile(RectangleShape tile);

	void setLayer();

};

#endif //!GameMap