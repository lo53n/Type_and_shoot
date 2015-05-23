#ifndef LandBuilderPattern
#define LandBuilderPattern



#include "GameMap.h"


//Abstract Builder


class LandBuilder{

protected:
	Map map;

public:
	LandBuilder(){}
	~LandBuilder(){}

	const Map& getMap() { return map; }

	virtual void initializeMap(){ map.initialize(); }
	virtual void initializeTiles() = 0;
	virtual void putCommon(int *i, int *j, int *maptile) = 0;
	virtual void putRock(int *i, int *j, int *maptile) = 0;
	virtual void putSpecial(int *i, int *j, int *maptile) = 0;
	virtual void endBuilding(){ map.setLayer(); }

};



//Director


class MapBuilder{

private:
	LandBuilder *landbuilder;


public:
	MapBuilder() : landbuilder(NULL) {}
	~MapBuilder() {}

	void setLandBuilder(LandBuilder* lb) { landbuilder = lb; }
	LandBuilder* getLandBuilder(){ return landbuilder; };

	const Map& getMap() { return landbuilder->getMap(); }

	void buildMap();


};
#endif // !LandBuilderPattern