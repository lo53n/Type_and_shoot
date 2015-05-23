#ifndef SnowlandBuilder
#define SnowlandBuilder
#include "LandBuilderPattern.h"


class SnowLandBuilder : public LandBuilder{

private:
	RectangleShape box1;
	Texture tile[14];
	RectangleShape rect;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(map);
	}

public:

	SnowLandBuilder(){}
	~SnowLandBuilder(){}

	void initializeTiles();
	void putCommon(int *i, int *j, int *maptile);
	void putRock(int *i, int *j, int *maptile);
	void putSpecial(int *i, int *j, int *maptile);



};

#endif // !SnowlandBuilder