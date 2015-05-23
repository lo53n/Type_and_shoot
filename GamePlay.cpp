#include "GamePlay.h"

////////////////////////////
//gameplay starting values//
////////////////////////////
void Gameplay::setVariables(){

	monstercount = 0;

	//slow enemies
	easy[0] = 0;
	normal[0] = 0;
	hard[0] = 0;
	brutal[0] = 0;

	//fast enemies
	easy[1] = 0;
	normal[1] = 0;
	hard[1] = 0;
	brutal[1] = 0;
	
	enemies.clear();
	p->getMagazine().clear();

}
void Gameplay::initialize(){

	setVariables();
	music.openFromFile("game_ambient.ogg");
	music.setLoop(true);
	////////////
	//Iterator//
	////////////
	Aggregate<Enemy*> *enemy_vectorAg = new VectorAg<Enemy*>(enemies);
	enemy_it = enemy_vectorAg->createIterator();
	Aggregate<Bullet*> *bullet_vectorAg = new VectorAg<Bullet*>(p->bullets);
	bullet_it = bullet_vectorAg->createIterator();

	///////////
	//Builder//
	///////////
	terrain_type = rand() % 3;
	switch (terrain_type){
	case 0: mapbuilder.setLandBuilder(&grassbuilder);
		break;
	case 1: mapbuilder.setLandBuilder(&snowbuilder);
		break;
	case 2: mapbuilder.setLandBuilder(&desertbuilder);
		break;
	}
	mapbuilder.buildMap();
	mapsprite = mapbuilder.getMap().sprite;

	//text initializing

	text_background.setSize(Vector2f(800.0f, 30.0f));
	text_background.setFillColor(Color::Color(0, 0, 0, 140));
	text_background.setPosition(Vector2f(0, 0));

	enemy_name_background.setFillColor(Color::Color(0, 0, 0, 180));
	
	wave_counter_text.setFont(font);
	wave_counter_text.setCharacterSize(20);
	wave_counter_text.setColor(Color::Yellow);
	wave_counter_text.setPosition(60.0f, 3.0f);

	score_counter_text.setFont(font);
	score_counter_text.setCharacterSize(20);
	score_counter_text.setColor(Color::Yellow);
	score_counter_text.setPosition(600.0f, 3.0f);

	enemy_name.setFont(font);
	enemy_name.setCharacterSize(14);
	enemy_name.setColor(Color::Color(255,255,255, 190));

	enemies_left_text.setFont(font);
	enemies_left_text.setCharacterSize(20);
	enemies_left_text.setColor(Color::Yellow);
	enemies_left_text.setPosition(300.0f, 3.0f);


	sendWave();

	setText();
	//resetting timer
	timer_for_score = 0;

}

void Gameplay::setText(){


	string wave_text = "Wave: ";
	stringstream ss;
	ss << wave;
	wave_counter_text.setString(wave_text + ss.str());
	ss.clear();

	stringstream ss1;
	ss1 << hitcount;
	string score_text = "Score: ";
	score_counter_text.setString(score_text + ss1.str());
	ss1.clear();

	stringstream ss2;
	ss2 << (monstercount - wave_killcount);
	string enemies_left = "Enemies left: ";
	enemies_left_text.setString(enemies_left + ss2.str());
	ss2.clear();

	if (p->getLock()){
		enemy_name.setString(en->getName().substr(en->current_hit));
		enemy_name.setPosition(400.0f - enemy_name.getGlobalBounds().width / 2, 320 + 13);
		enemy_name_background.setPosition(enemy_name.getGlobalBounds().left - 2, enemy_name.getGlobalBounds().top - 2);
		enemy_name_background.setSize(Vector2f(enemy_name.getGlobalBounds().width + 4, enemy_name.getGlobalBounds().height + 4));
	}
}

void Gameplay::restart(){

	p->getMagazine().clear();
	p->setVariables();
	wave_monsters = 0;
	hitcount = 0;
	wave = 0;
	killcount = 0;
	enemies.clear();
	initialize();

}
////////////
//movement//
////////////

void Gameplay::enemyMove(const double time_elapsed){

	if (enemy_it->isDone())
		enemy_it->first();
	while (!enemy_it->isDone()){
		if (!enemy_it->currentItem()->getKillTextureStatus()) enemy_it->currentItem()->moveTo(time_elapsed);
		enemy_it->next();
	}
	
	if (p->getLock()) {
		p->rotatePlayer(&(p->getEnemy()->getEnemyPosition()));
		p->moveSight(&p->getEnemy()->getEnemyPosition());
	}
	
}

void Gameplay::bulletsMove(const double time_elapsed){
	if (bullet_it->isDone())
		bullet_it->first();
	while (!bullet_it->isDone()){
		if (!bullet_it->currentItem()->getHitStatus()) bullet_it->currentItem()->moveTo(time_elapsed);
		bullet_it->next();
	}
}

void Gameplay::playerSeekTarget(Event event){

	for (int i = 0, len = getWave().size(); i < len; i++){
		if (!getWave()[i]->getKillStatus() && getWave()[i]->getChar() == static_cast<char>(event.text.unicode)){
			p->setEnemy(getWave()[i]);
			break;
		}
	}
}


//////////////////
//gameplay stuff//
//////////////////

bool Gameplay::losingPopup(Event event){
	if (!lost_screen_initialized){
		button.setSize(Vector2f(100.0f, 50.0f));
		button.setFillColor(Color::Color(90, 60, 60, 220));
		button.setOutlineThickness(2.0f);
		button.setOutlineColor(Color::Color(70, 70, 70, 255));
		button.setPosition(Vector2f(350.0f, 400.0f));

		popup.setSize(Vector2f(400.0f, 350.0f));
		popup.setFillColor(Color::Color(110, 100, 100, 240));
		popup.setOutlineThickness(4.0f);
		popup.setOutlineColor(Color::Color(50, 50, 50, 255));
		popup.setPosition(Vector2f(200.0f, 150.0f));

		ok_text.setFont(font);
		ok_text.setCharacterSize(40);
		ok_text.setColor(Color::White);
		ok_text.setPosition(365.0f, 400.0f);
		ok_text.setString("OK!");

		you_lost.setFont(font);
		you_lost.setCharacterSize(25);
		you_lost.setColor(Color::White);
		you_lost.setPosition(210.0f, 170.0f);
		you_lost.setString("Enemies killed: \n\nWaves beaten: \n\nCharacters typed:\n\nTyping speed:");

		stringstream ss;


		float speedtype = (hitcount / (timer_for_score))*60 ;
		
		ss << killcount << endl << endl << wave - 1 << endl << endl << hitcount << endl << endl << roundf(speedtype*100)/100<< " char/min";

		scores.setFont(font);
		scores.setCharacterSize(25);
		scores.setColor(Color::White);
		scores.setPosition(415.0f, 170.0f);
		scores.setString(ss.str());
		ss.clear();

		lost_screen_initialized = true;
	}

	Vector2f local_click;

	local_click.x = event.mouseButton.x;
	local_click.y = event.mouseButton.y;

	if (button.getGlobalBounds().contains(local_click)) {
		lost_game = false;
		lost_screen_initialized = false;
		return true;
	}
	return false;
}

bool Gameplay::getActive(){
	return is_active;
}

void Gameplay::setActive(bool status){
	is_active = status;
	if (status) music.play();
	else music.stop();
}
bool Gameplay::hasLost(){
	return lost_game;
}
void Gameplay::playerAction(Event event){


	if (event.type == Event::TextEntered){

		if (!p->getLock()) {
			playerSeekTarget(event);
			en = p->getEnemy();
		}
		if (p->getLock() && static_cast<char>(event.text.unicode) == p->getEnemy()->getChar()){
			p->shootGun(&Vector2f(event.mouseButton.x, event.mouseButton.y));
			hitcount++;
			setText();
		}
	}


}

void Gameplay::stuffHappens(const double dt){

	bulletsMove(dt);
	enemyMove(dt);
	enemyCollision();
	bulletCollision();

	timer_for_score += clock.restart().asSeconds();
	if (wave_killcount == wave_monsters){
		endWave();
		sendWave();
		setText();
	}

}

///////////////////////
//Wave oriented stuff//
///////////////////////

vector<Enemy*> Gameplay::getWave(){
	return enemies;
}

void Gameplay::createWave(){

	wave_killcount = 0;
	setVariables();
	wave_monsters += 1 + rand() % 3;
	monstercount = wave_monsters;
	int randomizer;

	for (int i = 0; i < wave_monsters; i++){
		randomizer = rand() % 100 + wave*2;
		if (randomizer < 40){
			if (rand() % 2 == 0) easy[0]++;
			else  easy[1]++;
		}
		if (randomizer >= 40 && randomizer < 65){
			if (rand() % 2 == 0) normal[0]++;
			else normal[1]++;
		}
		if (randomizer >= 65 && randomizer < 85){
			if (rand() % 2 == 0) hard[0]++;
			else hard[1]++;
		}
		if(randomizer >= 85){
			if (rand() % 2 == 0) brutal[0]++;
			else brutal[1]++;

		}
	}

	wave++;
}

void Gameplay::sendWave(){

	createWave();
	for (int i = 0; i < 2; i++){

		for (int j = 0; j < easy[i]; j++){
			Enemy* enemy = new Enemy(0 + 4 * i);
			enemies.push_back(enemy);
		}
		for (int j = 0; j < normal[i]; j++){
			Enemy* enemy = new Enemy(1 + 4 * i);
			enemies.push_back(enemy);
		}

		for (int j = 0; j < hard[i]; j++){
			Enemy* enemy = new Enemy(2 + 4 * i);
			enemies.push_back(enemy);
		}

		for (int j = 0; j < brutal[i]; j++){
			Enemy* enemy = new Enemy(3 + 4 * i);
			enemies.push_back(enemy);
		}
	}

}

void Gameplay::endWave(){

	enemies.clear();
	p->getMagazine().clear();

}

//////////////
//collisions//
//////////////

void Gameplay::bulletCollision(){
	FloatRect bullet_hitbox, enemy_hitbox;

	if (bullet_it->isDone()) bullet_it->first(); //reseting iterator
	while (!bullet_it->isDone()){
		bullet_hitbox = bullet_it->currentItem()->getHitbox().getGlobalBounds();
		enemy_hitbox = bullet_it->currentItem()->getDestination().getGlobalBounds();
		if (!bullet_it->currentItem()->getHitStatus() && enemy_hitbox.intersects(bullet_hitbox)) {
			bullet_it->currentItem()->setHitStatus();
			bullet_it->currentItem()->getTarget()->setHitTexture();
			if (bullet_it->currentItem()->getTarget()->getKillTextureStatus()) {
				wave_killcount++;
				killcount++;
			}
		}
		bullet_it->next();
	}
}


void Gameplay::enemyCollision(){

	FloatRect player_hitbox, enemy_hitbox;
	if (enemy_it->isDone()) enemy_it->first(); //reseting iterator

	while (!enemy_it->isDone()){
		player_hitbox = FloatRect(p->getPlayerPosition() - Vector2f(10.0f, 16.0f), Vector2f(20, 32));
		enemy_hitbox = enemy_it->currentItem()->getHitbox().getGlobalBounds();

		if (!enemy_it->currentItem()->getKillStatus() && player_hitbox.intersects(enemy_hitbox)) {
			p->setKillStatus(true);
			lost_game = true;
		}

		enemy_it->next();
	}


}