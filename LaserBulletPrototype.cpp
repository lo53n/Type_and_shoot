#include"LaserBulletPrototype.h"

using namespace std;

void LaserBullet::initialize() const{

	destination.setSize(Vector2f(32.0f, 32.0f));
	destination.setOrigin(-16.0f, -16.0f);
	hitbox.setSize(Vector2f(11.0f, 5.0f));
	bullet_form.setSize(Vector2f(7.0f, 2.0f));
	bullet_form.setFillColor(Color::Green);
	bullet_form.setOutlineThickness(2.0f);
	bullet_form.setOutlineColor(Color::Color(0, 140, 40, 255));
	bullet_form.setPosition(400, 320);

}

Bullet* LaserBullet::Clone(Enemy* enemy) const{
	return new LaserBullet(enemy);
}

RectangleShape LaserBullet::getDestination() const{
	return destination; 
}

void LaserBullet::setDestination() const {
	destination.setPosition(target->getHitbox().getGlobalBounds().left, target->getHitbox().getGlobalBounds().top);
	normalize();
}

void LaserBullet::setPosition(Vector2f* new_position) const  {
	position = *new_position;
}

bool LaserBullet::getHitStatus() const {
	return didHit;
}

Vector2f LaserBullet::getPosition() const{
	return position; 
}

void LaserBullet::setHitStatus() const {
	didHit = true; 
}

RectangleShape LaserBullet::getHitbox() const{
	return hitbox; 

}
void LaserBullet::setHitbox(Vector2f *_hitbox) const {
	hitbox.setPosition(*_hitbox); 
	bullet_form.setPosition(*_hitbox);
}
Enemy* LaserBullet::getTarget() const{
	return target; 
}

void LaserBullet::normalize() const{

	double rotation1 = atan2(320 - target->getEnemyPosition().y, 400 - target->getEnemyPosition().x);
	bullet_form.setRotation(rotation1 * 180 / 3.14);

	Vector2f dest = Vector2f(destination.getGlobalBounds().left, destination.getGlobalBounds().top);
	Vector2f pos(400, 320);
	Vector2f _normalized = dest - pos;

	float lenght;
	lenght = sqrt(pow(_normalized.x, 2) + pow(_normalized.y, 2));

	normalized.x = _normalized.x / lenght;
	normalized.y = _normalized.y / lenght;


}

void LaserBullet::moveTo(const double time_elapsed) const{

	float dtx = (float)(time_elapsed * speed * normalized.x);
	float dty = (float)(time_elapsed * speed * normalized.y);
	position.x += dtx;
	position.y += dty;

	hitbox.setPosition(position);
	bullet_form.setPosition(position);
}