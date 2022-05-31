#pragma once
#include "Cizilebilir.hpp"
#include "Pencere.hpp"
class Dortgen : public Cizilebilir {
public:
	sf::RectangleShape sekil;
	Dortgen(sf::Vector2f boyut, sf::Vector2f pozisyon);
	static std::shared_ptr<Dortgen> DortgenUret(sf::Vector2f boyut, sf::Vector2f pozisyon);
	void AsagiyaKaydir(float kaymaMiktari);
	virtual void Ciz(Pencere& pencere) override;
};

typedef std::shared_ptr<Dortgen> DortgenPtr;