#pragma once
#include "Pencere.hpp"
#include "Line.hpp"
#include "Dortgen.hpp"
#include "Bubble.hpp"
#include "AracPaneli.hpp"
class Oyun {
public:
	Oyun();
	~Oyun();
	void SetFps(int fps);
	void OyunuBaslat(int genislik, int yukseklik, const sf::String& pencereBaslik, sf::Color** colors, int levelSayisi);
	void OyunuKapat();
	void Ayarla();
	void KaplamaEkle(sf::String dosyaIsmi, bool arkaPlanOlsunmu = true);
	void FareHareketKontrolEt(int x, int y);
	void FareBasilmaKontrolEt(sf::Event::MouseButtonEvent olay);
	void FareBirakmaKontrolEt(sf::Event::MouseButtonEvent olay);
	void OlaylariBagla();
	void ArayuzleriYukle();
	void KlavyeTusKontrol(sf::Keyboard::Key tiklanilanTus);
	void CizimFonksiyonu();
	void SahneyiLevelIcinHazirla();
	void FirlatilacakBubbleOlustur(float bubbleYaricap);
	bool CarpismayiKontrolEt();
	bool FirlatilanSinireUlastimi();
	void FirlatilaniSiniraYerlestir();
	void AyniRenkleriPatlatmayiDene();
	void TemasiOlmayanlariPatlatmayiDene();
	void TemastakiAyniRenkleriBul(BubbleListesi& liste, BubblePtr temasEden);
	BubblePtr KonumdanBubbleGetir(sf::Vector2f konum);
	bool TekrarEdenBubbleVarmi(BubbleListesi& liste, BubblePtr eleman);
	sf::Color RastgeleRenkGetir();
	void BubbleListesindenKaldir(BubblePtr bubble);
	void OyunuAsagiyaKaydir();
	void BaglantiliBubblelariOlanlariBul(BubbleListesi& liste, BubblePtr kontrolEdilen);
	void OyunBittiMiKontrolEt();
	void LeveliYukle(bool sonrakiLevelMi);
	void OyunuBastanBaslat();
	void TopuFirlat();


private:

	void SaatiYenidenBaslat();

	sf::Time			m_cerceveSuresi;
	sf::Clock			m_saat;
	sf::Clock			m_kaydirmaZamanlayici;
	sf::Clock			m_firlatmaZamanlayici;
	int					m_fps;
	Pencere				m_pencere;
	KaplamaHaritasi		m_aracKaplamaListesi;
	AracPaneliListesi	m_panelListesi;
	LinePtr				m_line;
	DortgenPtr			m_dortgen;
	BubblePtr			m_firlatilacakBubble;
	BubbleListesi		m_bubbleListesi;
	bool				m_devamEdiyormu;
	FontPtr				m_font;
	int					m_genislik;
	int					m_yukseklik;
	bool				m_firlatmayiSurdur;
	int					m_bubbleYaricap;
	int					m_aktifLevelIndex;
	sf::Color** m_levels;
	int					m_levelSayisi;

};