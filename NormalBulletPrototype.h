#ifndef NormalBulletPrototype
#define NormalBulletPrototype

#include "BulletPrototype.h"

using namespace std;


class NormalBullet : public Bullet {

private:
	mutable RectangleShape destination;
	mutable Vector2f position, normalized;
	mutable bool didHit;
	mutable RectangleShape hitbox;
	mutable int quadrant;
	mutable Vector2f angle;

	mutable CircleShape bullet_form;
	mutable Sprite bullet_sprite;
	Texture texture;

	Enemy* target;

	float speed = 1700;



	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		if(!didHit) target.draw(bullet_form);
	};


	virtual void initialize() const;
public:

	NormalBullet(Enemy* enemy) : target(enemy) {initialize(); }

	virtual Bullet* Clone(Enemy* enemy) const;
	
	virtual RectangleShape getDestination() const{ return destination; }
	virtual void setDestination() const;
	virtual void setPosition(Vector2f* new_position) const;
	virtual bool getHitStatus() const;
	virtual Vector2f getPosition() const;
	virtual void setHitStatus() const;
	virtual RectangleShape getHitbox() const;
	virtual void setHitbox(Vector2f *_hitbox) const;

	virtual void normalize() const;
	virtual void moveTo(const double time_elapsed) const;

	virtual Enemy* getTarget()const;
};

#endif //!NormalBulletPrototype
