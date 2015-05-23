#include "Enemy.h"


void Enemy::initialize(){

	//iterator
	stringAg = new StringAg(name);
	it = stringAg->createIterator();

	//dekorator
	generateEnemy();

	if (!font.loadFromFile("arial.ttf")) cout << "error loading font!" << endl;;
	enemy_name_text.setFont(font);

	enemy_name_text.setCharacterSize(13);
	enemy_name_text.setColor(Color::White);
	enemy_name_text.setString(name);

	enemy_name_background.setSize(Vector2f(enemy_name_text.getGlobalBounds().width + 4, enemy_name_text.getGlobalBounds().height + 4));
	enemy_name_background.setFillColor(Color::Color(0, 0, 0, 190));



	spawnEnemy();

	RectangleShape enemy_rect;
	Texture skin;

	skin.loadFromFile("test_enemy.png");
	enemy_rect.setSize(Vector2f(32.0f, 32.0f));
	enemy_rect.setPosition(0, 0);
	texture.create(32, 32);
	enemy_rect.setTexture(&skin);
	texture.draw(enemy_rect);
	texture.display();

	enemysprite.setTexture(texture.getTexture());
	enemysprite.setPosition(enemy_pos);

	Vector2f enemy_size = Vector2f(enemysprite.getGlobalBounds().width, enemysprite.getGlobalBounds().height);
	Vector2f enemy_spriteposition = Vector2f(enemysprite.getGlobalBounds().left, enemysprite.getGlobalBounds().top);
	enemy_hitbox.setSize(enemy_size);
	
	enemy_hitbox.setPosition(enemy_spriteposition);
	enemy_hitbox.setOrigin(enemy_size.x/2, enemy_size.y/2);

	enemysprite.setOrigin(enemy_size.x / 2, enemy_size.y / 2);
	rotateEnemy();


	enemy_name_text.setPosition(enemy_pos.x - enemy_name_text.getGlobalBounds().width / 2, enemy_pos.y + 15);
	enemy_name_background.setPosition(enemy_name_text.getGlobalBounds().left, enemy_name_text.getGlobalBounds().top);

}

void Enemy::generateEnemy(){


	switch (enemy_type){
	case 0: en = new Easy_name(new Slow_enemy(name, speed));
		break;
	case 4: en = new Easy_name(new Fast_enemy(name, speed));
		break;
	case 1: en = new Medium_name(new Slow_enemy(name, speed));
		break;
	case 5: en = new Medium_name(new Fast_enemy(name, speed));
		break;
	case 2: en = new Hard_name(new Slow_enemy(name, speed));
		break;
	case 6: en = new Hard_name(new Fast_enemy(name, speed));
		break;
	case 3: en = new Hard_name(new Hard_name(new Slow_enemy(name, speed)));
		break;
	case 7: en = new Hard_name(new Hard_name(new Fast_enemy(name, speed)));
		break;


	}

	en->setName("");

}

Vector2f Enemy::getEnemyPosition(){

	return enemy_pos;

}

char Enemy::getChar(){

	return name.at(current_hit);
}

string Enemy::getName(){
	return name;
}

bool Enemy::isLock(){
	return is_lock;
}

double Enemy::getRotation(){
	return rotation;
}

RectangleShape Enemy::getHitbox(){

	return enemy_hitbox;
}

void Enemy::setLock(){
	is_lock = true;
}

Text* Enemy::getText(){
	return &enemy_name_text;
}

void Enemy::killTexture(){
	kill_texture = true;
}
void Enemy::killEnemy(){
	is_dead = true;
}
bool Enemy::getKillStatus(){
	return is_dead;
}
bool Enemy::getKillTextureStatus(){
	return kill_texture;
}
string Enemy::getRest(){
	cout << it->getRest()<<endl;
	return it->getRest();
}


void Enemy::rotateEnemy(){

	double rotation1 = atan2(enemy_pos.y - 320, enemy_pos.x - 400);

	rotation = rotation1 * 180 / 3.14 + 90;

	enemysprite.setRotation((float)rotation); 
	enemy_hitbox.setRotation((float)rotation);

}


void Enemy::moveTo(const double time_elapsed){

	Vector2f move = strategy->makeMove(time_elapsed,speed, enemy_pos);
	
	enemy_pos.x += (float)(move.x);
	enemy_pos.y += (float)(move.y);


	enemysprite.setPosition(enemy_pos);
	enemy_hitbox.setPosition(enemy_pos);

	rotateEnemy();


	enemy_name_text.setPosition(enemy_pos.x - enemy_name_text.getGlobalBounds().width/2, enemy_pos.y + 15);
	enemy_name_background.setPosition(enemy_name_text.getGlobalBounds().left - 2, enemy_name_text.getGlobalBounds().top - 2);

}

void Enemy::setHit(){

	current_hit++;
	if(!it->isDone()){
		it->next();
		enemy_name_text.setString(it->getRest());
		enemy_name_background.setSize(Vector2f(enemy_name_text.getGlobalBounds().width, enemy_name_text.getGlobalBounds().height) + Vector2f(4.0f ,4.0f));
		if (it->getRest().length() == 1)
			it->next();
	}
	else
		is_dead = true;
}

void Enemy::setHitTexture(){
	current_hit_texture++;
	 if (current_hit_texture == name.length())	kill_texture = true;

}

void Enemy::setStrategy(){
	int tmp = rand() % 4;
	int type = rand() % 3;
	delete strategy;
	switch (type){
	case 1:  //Curve
		switch (tmp){
		case 1:
			enemy_pos = Vector2f(820 + rand()%40, 320);
			break;
		case 2:
			enemy_pos = Vector2f(-20 - rand() % 40, 320);
			break;
		case 3:
			enemy_pos = Vector2f(400, 640 + rand() % 40);
			break;
		default:
			enemy_pos = Vector2f(400, -20 - rand() % 40);
			break;
		}
		strategy = new CurveMove(enemy_pos);
		break;
	case 2:  //Eliptic
		strategy = new ElipticMove(enemy_pos, speed);
		break;
	default:  //Straight
		strategy = new StraightMove(enemy_pos);
		break;
	}
}


void Enemy::spawnEnemy(){

	switch (rand() % 4){
	case 0: enemy_pos = Vector2f(rand() % 800, 0);
	case 1: enemy_pos = Vector2f(rand() % 800, 650);
	case 2: enemy_pos = Vector2f(-10, rand() % 640);
	case 3: enemy_pos = Vector2f(810, rand() % 640);
	}

	setStrategy();
}