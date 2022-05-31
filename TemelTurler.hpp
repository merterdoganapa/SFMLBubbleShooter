#pragma once
#include <SFML/Graphics.hpp>
#include<vector>
#include <map>
#include <functional>

typedef std::function<void(int, int)> FareHareketFonksiyonu;
typedef std::function<void(sf::Event::MouseButtonEvent)> FareButonFonksiyonu;
typedef std::function<void(sf::Keyboard::Key)> KlavyeTusFonksiyonu;
typedef std::function<void()>	TiklaFonksiyonu;
typedef std::vector<FareHareketFonksiyonu> FareHareketFonkListesi;
typedef std::vector<FareButonFonksiyonu> FareButonFonkListesi;
typedef std::vector<TiklaFonksiyonu>	TiklaFonksiyonuListesi;
typedef std::shared_ptr<sf::Font>	FontPtr;
typedef std::shared_ptr<sf::Texture> TexturePtr;
typedef std::map<sf::String, TexturePtr> KaplamaHaritasi;
