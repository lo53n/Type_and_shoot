#ifndef LaserBulletPrototype
#define LaserBulletPrototype

#include "BulletPrototype.h"

using namespace std;


class LaserBullet : public Bullet {

private:
	mutable RectangleShape destination;
	mutable Vector2f position, normalized;
	mutable bool didHit = false;
	mutable int quadrant;
	mutable RectangleShape hitbox;
	float speed = 1200;
	mutable Vector2f angle;

	mutable RectangleShape bullet_form;
	mutable Sprite bullet_sprite;
	Texture texture;

	Enemy* target;


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		if (!didHit) target.draw(bullet_form);
	};

	virtual void initialize() const;
public:

	LaserBullet(Enemy* enemy) : target(enemy){ initialize(); }

	virtual Bullet* Clone(Enemy* enemy) const;

	virtual RectangleShape getDestination() const;
	virtual void setDestination() const;
	virtual void setPosition(Vector2f* new_position) const;
	virtual bool getHitStatus() const;
	virtual Vector2f getPosition() const;
	virtual void setHitStatus() const;
	virtual RectangleShape getHitbox() const;
	virtual void setHitbox(Vector2f *_hitbox) const;
	virtual Enemy* getTarget() const;
	virtual void normalize() const;

	virtual void moveTo(const double time_elapsed) const;

};

#endif //!LaserBulletPrototype
