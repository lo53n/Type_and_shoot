#include "GrasslandBuilder.h"

void GrassLandBuilder::initializeTiles(){

	for (int i = 0; i < 14; i++){
		tile[i].loadFromFile("tiles.png", IntRect(i * 32, 0, 32, 32));
	}

}
void GrassLandBuilder::putCommon(int *i, int *j, int *maptile){

	rect.setPosition(32.0f * *i, 32.0f * *j);
	rect.setSize(Vector2f(32, 32));

	switch (*maptile){
	case 0:
	case 1:
	case 2: rect.setTexture(&tile[0]);
		break;
	case 3:
	case 4: rect.setTexture(&tile[1]);
		break;
	case 5: rect.setTexture(&tile[2]);
		break;
	case 6: rect.setTexture(&tile[3]);
		break;
	case 7: rect.setTexture(&tile[4]);
		break;
	}
	map.putCommonTile(rect);


}

void GrassLandBuilder::putRock(int *i, int *j, int *maptile){

	rect.setPosition(32.0f * *i, 32.0f * *j);
	rect.setSize(Vector2f(32, 32));

	switch (*maptile){
	case 8: rect.setTexture(&tile[5]);
		break;
	case 9: rect.setTexture(&tile[6]);
		break;
	case 10: rect.setTexture(&tile[7]);
		break;
	}
	map.putRockTile(rect);
}

void GrassLandBuilder::putSpecial(int *i, int *j, int *maptile){

	rect.setPosition(32.0f * *i, 32.0f * *j);
	rect.setSize(Vector2f(32, 32));

	switch (*maptile){
	case 11: rect.setTexture(&tile[8]);
		break;
	case 12: rect.setTexture(&tile[9]);
		break;
	case 13: rect.setTexture(&tile[10]);
		break;
	case 14: rect.setTexture(&tile[11]);
		break;
	case 15:
	case 16: rect.setTexture(&tile[12]);
		break;
	case 17:
	case 18: rect.setTexture(&tile[13]);
		break;
	default: break;
	}
	map.putUncommonTile(rect);


}