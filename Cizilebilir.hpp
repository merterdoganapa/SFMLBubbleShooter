#pragma once
#include<SFML/Graphics.hpp>
class Pencere;

class Cizilebilir
{
public:
	virtual void Ciz(Pencere& pencere) = 0;
	sf::Vector2f m_konum;
};
