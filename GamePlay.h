#ifndef GamePlay
#define GamePlay

#include <SFML\Audio.hpp>
#include <sstream>
 //builder
#include "GrasslandBuilder.h"
#include "SnowlandBuilder.h"
#include "DesertlandBuilder.h"

//iterator
#include "VectorAggregate.h"

//singleton + prototyp
#include "GamePlayer.h"

//dekorator
//#include "Enemy.h"


using namespace sf;
using namespace std;

class Gameplay : public Drawable{

private:
	//Generating map
	MapBuilder mapbuilder;
	SnowLandBuilder snowbuilder;
	GrassLandBuilder grassbuilder;
	DesertLandBuilder desertbuilder;
	Sprite mapsprite;
	int terrain_type;

	//Simple UI
	Text wave_counter_text, score_counter_text, enemies_left_text, actual_enemy;
	Font font;
	Text enemy_name;
	RectangleShape text_background, enemy_name_background;

	//Ambient music for gameplay
	Music music;

	//Iterator
	Iterator<Bullet*> *bullet_it;
	Iterator<Enemy*> *enemy_it;

	//Player related stuff
	Player *p = &Player::getPlayer();



	//Enemy related stuff
	vector<Enemy*> enemies;
	Enemy* en;


	//Gameplay related stuff
	Clock clock;
	double timer_for_score;
	int easy[2], normal[2], hard[2], brutal[2];							//number of monsters
	int wave, killcount, wave_killcount, wave_monsters, monstercount;	//should be 0
	int hitcount;														//player score

	bool is_active = false;
	bool lost_game = false;
	bool lost_screen_initialized = false;

	//Lost screen
	RectangleShape popup, button;
	Text you_lost, scores, ok_text;


	//Drawing sprites and objects
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(mapsprite);
		target.draw(*p);
		if (enemy_it->isDone())
			enemy_it->first();
		while (!enemy_it->isDone()){
			target.draw(*enemy_it->currentItem());
			enemy_it->next();
		}
		target.draw(text_background);
		target.draw(wave_counter_text);
		target.draw(score_counter_text);
		target.draw(enemies_left_text);
		if (p->getLock()){
			target.draw(enemy_name_background);
			target.draw(enemy_name);
		}
		if (lost_game){
			target.draw(popup);
			target.draw(button);
			target.draw(ok_text);
			target.draw(you_lost);
			target.draw(scores);

		}
	}


public:
	Gameplay(){ font.loadFromFile("arial.ttf"); initialize(); };
	~Gameplay(){};

	bool losingPopup(Event event);
	void restart();
	void setVariables();
	void setText();

	//Map stuff
	void initialize();

	//Enemy stuff
	void enemyMove(const double time_elapsed);
	vector<Enemy*> getWave();


	//Player stuff
	void playerSeekTarget(Event event);
	void bulletsMove(const double time_elapsed);


	//Gameplay stuff
	void createWave();
	void sendWave();
	void endWave();

	bool getActive();
	void setActive(bool status);
	bool hasLost();

	void playerAction(Event event);
	void stuffHappens(const double time);

	//Collisions stuff

	void bulletCollision();
	void enemyCollision();


};


#endif // !GamePlay
