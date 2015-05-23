#ifndef GameMenu
#define GameMenu


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <cstdlib>
#include <iostream>


using namespace sf;
using namespace std;

class Menu : public Drawable {

private:
	bool is_active = true;

	SoundBuffer soundbuffer;
	Music music;

	RectangleShape bigWindow;
	RectangleShape button[2];
	Text logo, start, exit;
	Font font;




	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(bigWindow);
		for (int i = 0; i < 2; i++) target.draw(button[i]);
		target.draw(logo);
		target.draw(start);
		target.draw(exit);

	}

public:
	Sound sound;
	Menu(){ initialize(); }

	void initialize();

	bool isActive();
	void setActive(bool status);

	int clickOption(Event event);



};

#endif