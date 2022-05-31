#include "Bubble.hpp"
#include "Pencere.hpp"
#include "Oyun.hpp"
#include <math.h>
#include <iostream>

Bubble::Bubble(float boyut, sf::Vector2f position, sf::Color renk, bool firlatilabilirMi)
{
	m_firlatilabilir = firlatilabilirMi;
	sekil.setRadius(boyut);
	sekil.setFillColor(renk);
	m_konum = position;
	m_boyut = boyut;
	m_hiz = 8.0f;
	m_renk = renk;
}

void Bubble::Ciz(Pencere& pencere)
{
	sekil.setPosition(m_konum);
	pencere.Ciz(sekil);
}

BubblePtr Bubble::BubbleUret(float boyut, sf::Vector2f position, sf::Color renk, bool firlatilabilirMi)
{
	return std::make_shared<Bubble>(boyut, position, renk, firlatilabilirMi);
}

void Bubble::HareketEttir()
{
	if (m_konum.x < 0 || m_konum.x > 480 - m_boyut * 2)
	{
		yon.x *= -1;
	}
	m_konum.x += yon.x * m_hiz;
	m_konum.y -= yon.y * m_hiz;
}

void Bubble::YonAta(float aci)
{
	auto radyan = aci * 3.14159 / 180;
	yon.x = sinf(radyan);
	yon.y = cosf(radyan);
}

float Bubble::BoyutAl()
{
	return m_boyut;
}

void Bubble::BilgileriGuncelle(sf::Vector2f yeniKonum, float yeniHiz)
{
	m_konum = yeniKonum;
	m_hiz = yeniHiz;
}

bool Bubble::SagdanMiCarpicak(float hedefMinX, float hedefMax, float simdikiMinX)
{
	return (hedefMax >= simdikiMinX && simdikiMinX >= hedefMinX);
}

bool Bubble::SoldanMiCarpicak(float hedefMinX, float hedefMax, float simdikiMinX)
{
	return (hedefMax >= simdikiMinX && simdikiMinX >= hedefMinX);
}

void Bubble::AsagiyaKaydir(float kaymaMiktari)
{
	m_konum.y += kaymaMiktari;
}

sf::Vector2f Bubble::SagKonumDon()
{
	return sf::Vector2f(m_konum.x + m_boyut * 2, m_konum.y);
}

sf::Vector2f Bubble::SolKonumDon()
{
	return sf::Vector2f(m_konum.x - m_boyut * 2, m_konum.y);
}

sf::Vector2f Bubble::SolUstKonumDon()
{
	return sf::Vector2f(m_konum.x - m_boyut, m_konum.y - m_boyut * 2 + 8);
}

sf::Vector2f Bubble::SagUstKonumDon()
{
	return sf::Vector2f(m_konum.x + m_boyut, m_konum.y - m_boyut * 2 + 8);
}

sf::Vector2f Bubble::SolAltKonumDon()
{
	return sf::Vector2f(m_konum.x - m_boyut, m_konum.y + m_boyut * 2 - 8);
}

sf::Vector2f Bubble::SagAltKonumDon()
{
	return sf::Vector2f(m_konum.x + m_boyut, m_konum.y + m_boyut * 2 - 8);
}


bool Bubble::CarpistilarMi(BubblePtr targetBubble)
{
	int bubbleCap = m_boyut * 2;

	auto targetBubbleMinPosition = sf::Vector2f(targetBubble->m_konum.x, targetBubble->m_konum.y);
	auto targetBubbleMaxPosition = sf::Vector2f(targetBubbleMinPosition.x + bubbleCap, targetBubbleMinPosition.y + bubbleCap);
	auto targetBubbleCenterPosition = sf::Vector2f(targetBubbleMinPosition.x + m_boyut, targetBubbleMinPosition.y + m_boyut);
	auto currentBubbleMinPosition = sf::Vector2f(m_konum.x, m_konum.y);
	auto currentBubbleMaxPosition = sf::Vector2f(m_konum.x + bubbleCap, m_konum.y + bubbleCap);
	auto currentBubbleCenterPosition = sf::Vector2f(currentBubbleMinPosition.x + m_boyut, currentBubbleMinPosition.y + m_boyut);

	auto uzaklik = sqrt(pow(targetBubbleCenterPosition.x - currentBubbleCenterPosition.x, 2) +
		pow(targetBubbleCenterPosition.y - currentBubbleCenterPosition.y, 2));

	if (uzaklik > (bubbleCap)) return false;


	if ((targetBubbleMaxPosition.y >= currentBubbleMinPosition.y && currentBubbleMinPosition.y >= targetBubbleMinPosition.y)) {
		int yeniX = 0;
		int yeniY = 0;
		if (SagdanMiCarpicak(targetBubbleMinPosition.x, targetBubbleMaxPosition.x, currentBubbleMinPosition.x)) {
			if (currentBubbleCenterPosition.y - targetBubbleCenterPosition.y < 20) { // merkez noktalar yeterince yakin mi
				yeniX = targetBubbleMinPosition.x + bubbleCap;
				yeniY = targetBubbleMinPosition.y;
			}
			else {
				yeniX = targetBubbleMinPosition.x + m_boyut;
				yeniY = targetBubbleMaxPosition.y - 8;
			}
			m_konum = sf::Vector2f(yeniX, yeniY);
			m_hiz = 0.0f;
			return true;
		}
		else if (SoldanMiCarpicak(targetBubbleMinPosition.x, targetBubbleMaxPosition.x, currentBubbleMaxPosition.x)) {
			if (currentBubbleCenterPosition.y - targetBubbleCenterPosition.y < 20) {
				yeniX = targetBubbleMinPosition.x - bubbleCap;
				yeniY = targetBubbleMinPosition.y;
			}
			else {
				yeniX = targetBubbleMinPosition.x - m_boyut;
				yeniY = targetBubbleMaxPosition.y - 8;
			}
			m_konum = sf::Vector2f(yeniX, yeniY);
			m_hiz = 0.0f;
			return true;
		}
	}

	return false;
}

