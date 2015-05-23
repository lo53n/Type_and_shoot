#ifndef GamePlayer
#define GamePlayer

#include <SFML\Audio.hpp>

#include "NormalBulletPrototype.h"
#include "LaserBulletPrototype.h"
//iterator
#include "VectorAggregate.h"

using namespace sf;
using namespace std;


class Player : public Drawable {

private:
	//singleton
	static Player *player;
	Player(){ initialize(); };
	Player(Player const&);
	void operator=(Player const&);

	//Iterator
	
	Iterator<Bullet*> *bullet_it;

	//Player stuff.
	float position_x, position_y;
	double rotation;
	bool is_dead = false;

	Sprite playersprite;
	RenderTexture texture;
	Vertex laser_sight[2];

	//
	Enemy* lock_on = NULL;
	bool has_lock = false;

	//bullets factory
	Bullet* bulletprototype;
	BulletCardridge* ammomagazine;

	SoundBuffer buffer;
	Sound gunshot;

	//Drawing sprites and objects
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(playersprite);
		if(has_lock) target.draw(laser_sight, 2, Lines);
		if (bullet_it->isDone())
			bullet_it->first();
		while (!bullet_it->isDone()){
			target.draw(*bullet_it->currentItem());
			bullet_it->next();
		}
	}

public:
	vector<Bullet*> bullets;

	void setVariables();
	void initialize();

	//singleton
	static Player& getPlayer(){
		static Player instance;
		return instance;
	}
	
	//Player stuff

	Vector2f getPlayerPosition();
	double getRotation();
	void rotatePlayer(Vector2f *enemy_pos);
	void moveSight(Vector2f *enemy_pos);
	bool getKillStatus();
	void setKillStatus(bool status);


	//Enemy Stuff

	Enemy* getEnemy();
	void setEnemy(Enemy* new_enemy);
	bool getLock();
	void setLock();

	//Bullets factory stuff
	void shootGun(Vector2f* enemy_pos);
	vector<Bullet*> getMagazine();
};
#endif // !GamePlayer
