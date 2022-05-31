#pragma once
#include <SFML/Graphics.hpp>
#include "Cizilebilir.hpp"
class Line : public Cizilebilir
{
public:
	sf::RectangleShape cizgi;
	Line(sf::Vector2f boyut, sf::Vector2f pozisyon);
	static std::shared_ptr<Line> LineUret(sf::Vector2f boyut, sf::Vector2f pozisyon);
	void Dondur(float angle);
	virtual void Ciz(Pencere& pencere) override;
	float LineAciAl();
};

typedef std::shared_ptr<Line>	LinePtr;
