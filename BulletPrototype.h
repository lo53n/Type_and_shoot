#ifndef BulletPrototype
#define BulletPrototype

#include <SFML/Graphics.hpp>
/*
#include <cstdlib>
#include <iostream>
*/
#include "Enemy.h"

using namespace sf;
using namespace std;


//prototype
class Bullet : public Drawable{
private:
	RectangleShape destination;
	Vector2f position, normalized;
	mutable bool didHit;
	mutable int quadrant;
	mutable Vector2f angle;
	mutable RectangleShape hitbox;
	Enemy *target;

	Sprite bullet_sprite;
	Texture texture;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	virtual void initialize() const = 0;

public:

	virtual ~Bullet(){};

	virtual Bullet* Clone(Enemy*) const = 0;

	virtual RectangleShape getDestination() const = 0;
	virtual void setDestination() const = 0;
	virtual Vector2f getPosition() const = 0;
	virtual void setPosition(Vector2f*) const = 0;
	virtual void normalize() const = 0;
	virtual void setHitStatus() const = 0;
	virtual bool getHitStatus() const = 0;
	virtual RectangleShape getHitbox() const = 0;
	virtual void setHitbox(Vector2f*) const = 0;
	virtual Enemy* getTarget() const = 0;
	virtual void moveTo(const double) const = 0;

};

//prototype factory
class BulletCardridge{

private:
	Bullet* prototype;


public:
	BulletCardridge(Bullet* proto) : prototype(proto){};


	Bullet* shootBullet(Enemy* enemy){
		return prototype->Clone(enemy);
	}
};


#endif //!BulletPrototype