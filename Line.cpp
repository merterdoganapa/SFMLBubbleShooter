#include "Line.hpp"
#include "Pencere.hpp"
void Line::Dondur(float angle)
{
	auto cizgiRotasyon = cizgi.getRotation();
	if ((angle < 0 && cizgiRotasyon == 285) || (angle > 0 && cizgiRotasyon == 75)) return;
	cizgi.rotate(angle);
}

Line::Line(sf::Vector2f boyut, sf::Vector2f pozisyon)
{
	m_konum = pozisyon;
	cizgi.setPosition(pozisyon);
	cizgi.setSize(boyut);
	cizgi.setOrigin(sf::Vector2f(boyut.x / 2, boyut.y));
}

LinePtr Line::LineUret(sf::Vector2f boyut, sf::Vector2f pozisyon)
{
	return std::make_shared<Line>(boyut, pozisyon);
}

void Line::Ciz(Pencere& pencere)
{
	cizgi.setPosition(m_konum);
	pencere.Ciz(cizgi);
}

float Line::LineAciAl()
{
	return cizgi.getRotation();
}
