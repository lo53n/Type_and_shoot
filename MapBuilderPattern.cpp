#include "LandBuilderPattern.h"

void MapBuilder::buildMap(){
	

	landbuilder->initializeMap();
	landbuilder->initializeTiles();
	for (int i = 0; i < 25; i++){
		for (int j = 0; j < 20; j++){
			int maptile = landbuilder->getMap().map[i][j];
			if (maptile < 8) landbuilder->putCommon(&i, &j, &maptile);
			if (maptile >= 8 && maptile < 11) landbuilder->putRock(&i, &j, &maptile);
			if (maptile >= 11) landbuilder->putSpecial(&i, &j, &maptile);
		}
	}

	landbuilder->endBuilding();

}