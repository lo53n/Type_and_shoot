#include "NormalBulletPrototype.h"

using namespace std;

Bullet* NormalBullet::Clone(Enemy* enemy) const {
	return new NormalBullet(enemy);
}

void NormalBullet::initialize() const{

	destination.setSize(Vector2f(32.0f, 32.0f));
	destination.setOrigin(-16.0f, -16.0f);
	hitbox.setSize(Vector2f(8.0f, 8.0f));
	bullet_form.setRadius(3);
	bullet_form.setFillColor(Color::Red);
	bullet_form.setOutlineThickness(2.0f);
	bullet_form.setOutlineColor(Color::Color(190, 40, 20, 255));
	bullet_form.setPosition(400, 320);

}

void NormalBullet::setDestination() const {
	destination.setPosition(target->getHitbox().getGlobalBounds().left, target->getHitbox().getGlobalBounds().top);
	normalize();
}

void NormalBullet::setPosition(Vector2f* new_position) const  { 
	position = *new_position; 
}

bool NormalBullet::getHitStatus() const { 
	return didHit; 
}

Vector2f NormalBullet::getPosition() const{ 
	return position; 
}

void NormalBullet::setHitStatus() const {
	didHit = true; 
}
RectangleShape NormalBullet::getHitbox() const{
	return hitbox; 
}

void NormalBullet::setHitbox(Vector2f *_hitbox) const { 
	hitbox.setPosition(*_hitbox); bullet_form.setPosition(*_hitbox);
}

Enemy* NormalBullet::getTarget()const {
	return target; 
}

void NormalBullet::normalize() const{

	Vector2f dest = Vector2f(destination.getGlobalBounds().left, destination.getGlobalBounds().top);
	Vector2f pos(400, 320);
	Vector2f _normalized = dest - pos;

	float lenght;
	lenght = sqrt(pow(_normalized.x, 2) + pow(_normalized.y, 2));

	normalized.x = _normalized.x / lenght;
	normalized.y = _normalized.y / lenght;

}

void NormalBullet::moveTo(const double time_elapsed) const{

	float dtx = (float)(time_elapsed * speed * normalized.x);
	float dty = (float)(time_elapsed * speed * normalized.y);
	position.x += dtx;
	position.y += dty;

	hitbox.setPosition(position);
	bullet_form.setPosition(position);
}