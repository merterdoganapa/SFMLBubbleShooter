#pragma once
#include "Cizilebilir.hpp"

class Bubble : public Cizilebilir {
public:
	sf::CircleShape sekil;
	sf::Color m_renk;
	bool m_firlatilabilir;
	Bubble(float boyut, sf::Vector2f yon, sf::Color renk, bool firlatilabilirMi);
	virtual void Ciz(Pencere& pencere) override;
	static std::shared_ptr<Bubble> BubbleUret(float boyut, sf::Vector2f position, sf::Color renk, bool firlatilabilirMi);
	void HareketEttir();
	void YonAta(float aci);
	float BoyutAl();
	bool CarpistilarMi(std::shared_ptr<Bubble> bubble);
	void BilgileriGuncelle(sf::Vector2f yeniKonum, float yeniHiz);
	bool SagdanMiCarpicak(float hedefMinX, float hedefMax, float simdikiMinX);
	bool SoldanMiCarpicak(float hedefMinX, float hedefMax, float simdikiMaxX);
	void AsagiyaKaydir(float kaymaMiktari);
	sf::Vector2f SagKonumDon();
	sf::Vector2f SolKonumDon();
	sf::Vector2f SolUstKonumDon();
	sf::Vector2f SagUstKonumDon();
	sf::Vector2f SolAltKonumDon();
	sf::Vector2f SagAltKonumDon();
private:
	float m_hiz;
	sf::Vector2f yon;
	float m_boyut;
};

typedef std::shared_ptr<Bubble> BubblePtr;
typedef std::vector<BubblePtr> BubbleListesi;