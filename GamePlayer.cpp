#include "GamePlayer.h"


void Player::setVariables(){

	position_x = 400;
	position_y = 320;

	has_lock = false;
	is_dead = false;
	lock_on = NULL;

	playersprite.setRotation(0);

	int bullet_type = rand() % 2;
	if (bullet_type == 0) {
		buffer.loadFromFile("laser_shot.ogg");
		bulletprototype = new LaserBullet(lock_on);
	}
	else {
		buffer.loadFromFile("gun_shot.wav");
		bulletprototype = new NormalBullet(lock_on);
	}
	ammomagazine = new BulletCardridge(bulletprototype);
	gunshot.setBuffer(buffer);
}
void Player::initialize(){
	
	RectangleShape player_rect;
	Texture skin;
	skin.loadFromFile("player.png");
	player_rect.setSize(Vector2f(32.0f, 32.0f));
	player_rect.setPosition(0, 0);
	texture.create(32, 32);
	player_rect.setTexture(&skin);
	texture.draw(player_rect);
	texture.display();

	playersprite.setTexture(texture.getTexture());
	playersprite.setOrigin(Vector2f(16.0f, 16.0f));
	playersprite.setPosition(400, 320);

	//Iterator

	Aggregate<Bullet*> *bullet_vectorAg = new VectorAg<Bullet*>(bullets);
	bullet_it = bullet_vectorAg->createIterator();
		


	setVariables();
}

Vector2f Player::getPlayerPosition(){

	return Vector2f(position_x, position_y);

}

double Player::getRotation(){

	return rotation;
}

vector<Bullet*> Player::getMagazine(){

	 return bullets;

}

Enemy* Player::getEnemy(){
	return lock_on;
}

bool Player::getLock(){
	return has_lock;

}

bool Player::getKillStatus(){
	return is_dead;
}

void Player::setKillStatus(bool status){
	is_dead = status;
}

void Player::setLock(){
	if (!has_lock) has_lock = true;
	else has_lock = false;
}

void Player::setEnemy(Enemy* new_enemy){
	lock_on = new_enemy; 
	setLock();
	lock_on->getText()->setColor(Color::Cyan);
}

void Player::moveSight(Vector2f *enemy_pos){
	laser_sight[1] = *enemy_pos;
}

void Player::rotatePlayer(Vector2f *enemy_pos){


	Vector2f player_pos = getPlayerPosition();

	laser_sight[0] = player_pos;
	laser_sight[1] = *enemy_pos;

	laser_sight[0].color = Color::Red;
	laser_sight[1].color = Color::Yellow;


	double rotation1 = atan2(player_pos.y - enemy_pos->y, player_pos.x - enemy_pos->x);

	rotation = rotation1 * 180 / 3.14 + 90;
	
	playersprite.setRotation((float)rotation);

}

void Player::shootGun(Vector2f* enemy_pos) {


	Bullet* shot = ammomagazine->shootBullet(lock_on);

	gunshot.play();

	shot->setDestination();

	shot->setPosition(&Vector2f(400.0f, 320.0f));
	shot->setHitbox(&Vector2f(400.0f, 320.0f));

	bullets.push_back(shot);

	getEnemy()->setHit();
	if (getEnemy()->getKillStatus()) setLock();
}