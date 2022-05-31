#include "Oyun.hpp"
#include <iostream>
int main()
{
	int LEVEL_COUNT = 3;
	sf::Color** levels;
	levels = new sf::Color * [LEVEL_COUNT];
	levels[0] = new sf::Color[30]{
		sf::Color::Transparent,sf::Color::Transparent,sf::Color::Yellow,sf::Color::Yellow,sf::Color::Green,sf::Color::Blue,sf::Color::Transparent,sf::Color::Transparent,
		sf::Color::Red,sf::Color::Red,sf::Color::Yellow,sf::Color::Yellow,sf::Color::Blue,sf::Color::Green,sf::Color::Green,
		sf::Color::Transparent,sf::Color::Transparent,sf::Color::Green,sf::Color::Green,sf::Color::Red,sf::Color::Red,sf::Color::Yellow,sf::Color::Yellow,
		sf::Color::Transparent,sf::Color::Transparent,sf::Color::Transparent,sf::Color::Blue,sf::Color::Blue,sf::Color::Transparent,sf::Color::Transparent,
	};
	levels[1] = new sf::Color[30]{
		sf::Color::Red,sf::Color::Red,sf::Color::Yellow,sf::Color::Yellow,sf::Color::Blue,sf::Color::Blue,sf::Color::Green,sf::Color::Green,
		sf::Color::Red,sf::Color::Red,sf::Color::Yellow,sf::Color::Yellow,sf::Color::Blue,sf::Color::Blue,sf::Color::Green,
		sf::Color::Blue,sf::Color::Blue,sf::Color::Green,sf::Color::Green,sf::Color::Red,sf::Color::Red,sf::Color::Yellow,sf::Color::Yellow,
		sf::Color::Blue,sf::Color::Green,sf::Color::Green,sf::Color::Red,sf::Color::Red,sf::Color::Yellow,sf::Color::Yellow,
	};
	levels[2] = new sf::Color[30]{
		sf::Color::Red,sf::Color::Green,sf::Color::Blue,sf::Color::Yellow,sf::Color::Cyan,sf::Color::Magenta,sf::Color::Red,sf::Color::Green,
		sf::Color::Cyan,sf::Color::Magenta,sf::Color::Red,sf::Color::Green,sf::Color::Blue,sf::Color::Yellow,sf::Color::Cyan,
		sf::Color::Red,sf::Color::Green,sf::Color::Blue,sf::Color::Yellow,sf::Color::Cyan,sf::Color::Magenta,sf::Color::Red,sf::Color::Green,
		sf::Color::Cyan,sf::Color::Magenta,sf::Color::Red,sf::Color::Green,sf::Color::Blue,sf::Color::Yellow,sf::Color::Cyan,
	};

	Oyun oyun;
	oyun.OyunuBaslat(480, 800, "Deneme", levels, LEVEL_COUNT);
}