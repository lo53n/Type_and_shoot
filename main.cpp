#include <SFML/Graphics.hpp>
#include <cstdlib>

#include <iostream>

#include "GamePlay.h"
#include "GameMenu.h"
#include "StringAggregate.h"
#include "IteratorPattern.h"
#include "VectorAggregate.h"

using namespace std;
using namespace sf;


int main()
{
	
	sf::RenderWindow window(sf::VideoMode(800, 640), "SFML works!", Style::Close);

	//RANDOMIZEEEEEEE!!!
	srand(time(NULL));

	Clock clock;
	Menu menu;
	Gameplay gameplay;
	Player *p = &Player::getPlayer();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if(menu.isActive()) switch (menu.clickOption(event)){
				case 0: gameplay.setActive(true);
					menu.setActive(false);
					break;
				case 1: exit(1);
				}
			}
			if(!p->getKillStatus() && gameplay.getActive()) gameplay.playerAction(event);
		}

		if (gameplay.hasLost()) {
			if (gameplay.losingPopup(event)){
				gameplay.setActive(false);
				menu.setActive(true);
				gameplay.restart();
			}
		}

		const double dt(clock.restart().asSeconds());
		if(gameplay.getActive()) gameplay.stuffHappens(dt);
		
		window.clear();
		if (gameplay.getActive()) window.draw(gameplay);
		if (menu.isActive()) window.draw(menu);
		window.display();
	}

	return 0;
}