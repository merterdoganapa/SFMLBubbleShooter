#pragma once
#include <SFML/Graphics.hpp>
#include "TemelTurler.hpp"
class Pencere
{
public:
	Pencere();
	void Olustur(int genislik, int yukseklik, const sf::String& pencereBaslik);
	bool AcikMi();
	void Kapat();
	void OlaylarýKontrolEt();
	void CizimeBasla();
	void Ciz(sf::Drawable& sekil);
	void CizimiBitir();
	void KlavyeTusFonksiyonEkle(KlavyeTusFonksiyonu fonksiyon);
	void FareHareketFonksiyonuEkle(FareHareketFonksiyonu yeniFonksiyon);
	void FareBasilmaFonksiyonuEkle(FareButonFonksiyonu yeniFonksiyon);
	void FareBirakilmaFonksiyonuEkle(FareButonFonksiyonu yeniFonksiyon);
	sf::Vector2f PencereBoyutunuAl();

private:
	sf::RenderWindow m_pencere;
	int m_pencereGenislik;
	int m_pencereYukseklik;
	KlavyeTusFonksiyonu m_klavyeTusFonksiyonu;
	FareHareketFonkListesi	m_fareHareketFonkListesi;
	FareButonFonkListesi	m_fareBasilmaFonkListesi;
	FareButonFonkListesi	m_fareBirakmaFonkListesi;
};