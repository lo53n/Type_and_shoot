#ifndef Enemy_
#define Enemy_

#include <string>
#include <SFML/Graphics.hpp>

//iterator
#include "StringAggregate.h"
#include "Aggregate_.h"

//dekorator
#include "SlowEnemy.h"
#include "FastEnemy.h"
#include "HardName.h"
#include "MediumName.h"
#include "EasyName.h"

//Strategy
#include "StraightMove.h"
#include "CurveMove.h"
#include "ElipticMove.h"


using namespace sf;
using namespace std;

// Enemy class

class Enemy : public Drawable {

private:
	//Strategy
	MoveStrategy *strategy;


	//Graphics
	RenderTexture texture;
	RectangleShape enemy_hitbox;
	Text enemy_name_text;
	RectangleShape enemy_name_background;
	Font font;

	//dekorator
	Enemy_name * en;


	Vector2f enemy_pos;
	double rotation;
	string name;
	bool is_lock;
	float speed;
	bool is_dead = false;
	bool kill_texture = false;

	int enemy_type;



	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		if (!kill_texture) {
			target.draw(enemysprite);
			target.draw(enemy_name_background);
			target.draw(enemy_name_text);
		}
	}

public:
	bool first;
	//Vector2f move;
	int current_hit = 0;
	int current_hit_texture = 0;
	Sprite enemysprite;



	enum StrategyType{
		Straight, Eliptic, Curve
	};

	//iterator
	Aggregate<string> *stringAg;
	Iterator<string> *it;

	Enemy(int type): enemy_type(type){ initialize(); };
	~Enemy(){};


	void initialize();			//initialize enemy variables and textures
	void generateEnemy();



	Vector2f getEnemyPosition();//get enemy position in 2d float vector
	bool getKillStatus();		//check if enemy is dead to disable collisions
	bool getKillTextureStatus();//check if enemy texture is dead to disable drawing texture
	string getName();			//get enemy name
	char getChar();				//get actual name character
	Text* getText();			//get enemy name text to modify it
	bool isLock();				//check if enemy has player lock on
	double getRotation();		//get enemy angle towards player
	RectangleShape getHitbox();	//get hitbox data
	string getRest();			//get rest of string



	void killTexture();			//set killed status to enemy texture
	void killEnemy();			//set killed status to enemy
	void setLock();				//set player lock on
	void setHit();				//collision with bullet on enemy
	void setHitTexture();		//collision with bullet on texture
	void setName(string name);	//set enemy name
	void setStrategy();			//set enemy strategy



	void moveTo(const double time_elapsed);	//move enemy in game frame
	void spawnEnemy();			//set enemy spawn location
	void rotateEnemy();			//set enemy rotation
};

#endif // !Enemy_