#include "Dortgen.hpp"

Dortgen::Dortgen(sf::Vector2f boyut, sf::Vector2f pozisyon)
{
	sekil.setSize(boyut);
	sekil.setOrigin(sf::Vector2f(0, boyut.y));
	sekil.setPosition(pozisyon);
	sekil.setFillColor(sf::Color::White);
	m_konum = pozisyon;
}

DortgenPtr Dortgen::DortgenUret(sf::Vector2f boyut, sf::Vector2f pozisyon)
{
	return std::make_shared<Dortgen>(boyut, pozisyon);
}

void Dortgen::AsagiyaKaydir(float kaymaMiktari)
{
	m_konum.y += kaymaMiktari;
}

void Dortgen::Ciz(Pencere& pencere)
{
	sekil.setPosition(m_konum);
	pencere.Ciz(sekil);
}
