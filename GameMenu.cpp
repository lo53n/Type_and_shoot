#include "GameMenu.h"

void Menu::initialize(){

	music.openFromFile("ambient.ogg");
	music.setLoop(true);
	music.play();
	soundbuffer.loadFromFile("mouseclick.wav");
	sound.setBuffer(soundbuffer);

	bigWindow.setPosition(200, 150);
	bigWindow.setSize(Vector2f(400.0f, 340.0f));
	bigWindow.setFillColor(Color::Color(50, 40, 20, 255));
	bigWindow.setOutlineColor(Color::Color(90, 80, 60, 255));
	bigWindow.setOutlineThickness(3.0f);

	for (int i = 0; i < 2; i++){
		button[i].setSize(Vector2f(200.0f, 60.0f));
		button[i].setFillColor(Color::Color(90, 80, 60, 255));
		button[i].setOutlineColor(Color::Color(130, 120, 100, 255));
		button[i].setOutlineThickness(2.0f);
		button[i].setPosition(300, 270 + 100 * i);
	}

	font.loadFromFile("arial.ttf");

	logo.setString("Type'n'Shoot!");
	logo.setFont(font);
	logo.setCharacterSize(40);
	logo.setPosition(Vector2f(280, 180));

	start.setString("Start game!");
	start.setFont(font);
	start.setCharacterSize(30);
	start.setPosition(Vector2f(320, 280));

	exit.setString("Exit game!");
	exit.setFont(font);
	exit.setCharacterSize(30);
	exit.setPosition(Vector2f(327, 380));


}


bool Menu::isActive(){

	return is_active;
}
void Menu::setActive(bool status){

	is_active = status;
	if (status) music.play();
	else music.stop();
}

int Menu::clickOption(Event event){

	Vector2f local_click;

	local_click.x = event.mouseButton.x;
	local_click.y = event.mouseButton.y;
	for (int i = 0; i < 2; i++) if (button[i].getGlobalBounds().contains(local_click)) {
		sound.play(); 
		return i;
	}
	return 2;

}