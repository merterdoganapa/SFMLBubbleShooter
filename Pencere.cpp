#include "Pencere.hpp"

Pencere::Pencere()
{
}

void Pencere::Olustur(int genislik, int yukseklik, const sf::String& pencereBaslik)
{
	m_pencereGenislik = genislik;
	m_pencereYukseklik = yukseklik;
	m_pencere.create(sf::VideoMode(genislik, yukseklik), pencereBaslik);
}

bool Pencere::AcikMi()
{
	return m_pencere.isOpen();
}

void Pencere::Kapat()
{
	m_pencere.close();
}

void Pencere::OlaylarýKontrolEt()
{
	sf::Event olay;
	while (m_pencere.pollEvent(olay))
	{
		if (olay.type == sf::Event::Closed)
		{
			Kapat();
		}
		if (olay.type == sf::Event::KeyPressed)
		{
			m_klavyeTusFonksiyonu(olay.key.code);
		}
		if (olay.type == sf::Event::MouseMoved)
		{
			for (auto siradaki : m_fareHareketFonkListesi)
				siradaki(olay.mouseMove.x, olay.mouseMove.y);
		}
		if (olay.type == sf::Event::MouseButtonPressed)
		{
			for (auto siradaki : m_fareBasilmaFonkListesi)
				siradaki(olay.mouseButton);
		}
		if (olay.type == sf::Event::MouseButtonReleased)
		{
			for (auto siradaki : m_fareBirakmaFonkListesi)
				siradaki(olay.mouseButton);
		}
	}
}

void Pencere::CizimeBasla()
{
	m_pencere.clear();
}

void Pencere::Ciz(sf::Drawable& sekil)
{
	m_pencere.draw(sekil);
}

void Pencere::CizimiBitir()
{
	m_pencere.display();
}

void Pencere::KlavyeTusFonksiyonEkle(KlavyeTusFonksiyonu fonksiyon)
{
	m_klavyeTusFonksiyonu = fonksiyon;
}

void Pencere::FareHareketFonksiyonuEkle(FareHareketFonksiyonu yeniFonksiyon)
{
	m_fareHareketFonkListesi.push_back(yeniFonksiyon);
}

void Pencere::FareBasilmaFonksiyonuEkle(FareButonFonksiyonu yeniFonksiyon)
{
	m_fareBasilmaFonkListesi.push_back(yeniFonksiyon);
}

void Pencere::FareBirakilmaFonksiyonuEkle(FareButonFonksiyonu yeniFonksiyon)
{
	m_fareBirakmaFonkListesi.push_back(yeniFonksiyon);
}

sf::Vector2f Pencere::PencereBoyutunuAl()
{
	return sf::Vector2f(m_pencereGenislik, m_pencereYukseklik);
}
