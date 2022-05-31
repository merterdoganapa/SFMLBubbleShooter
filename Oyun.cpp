#include "Oyun.hpp"
#include <iostream>
#include <filesystem>
Oyun::Oyun()
{
	m_fps = 144;
	m_cerceveSuresi = sf::seconds(1.0f / m_fps);
	m_devamEdiyormu = false;
	m_bubbleYaricap = 30;

}

Oyun::~Oyun()
{

}

void Oyun::SetFps(int fps)
{

}

void Oyun::OyunuBaslat(int genislik, int yukseklik, const sf::String& pencereBaslik, sf::Color** colors, int levelSayisi)
{
	m_aktifLevelIndex = 0;
	float lineWidth = 2;
	float lineHeight = 85;
	m_genislik = genislik;
	m_yukseklik = yukseklik;
	m_levels = colors;
	m_levelSayisi = levelSayisi;
	m_line = Line::LineUret(sf::Vector2f(lineWidth, lineHeight), sf::Vector2f(genislik / 2, yukseklik - m_bubbleYaricap));
	m_dortgen = Dortgen::DortgenUret(sf::Vector2f(genislik, yukseklik), sf::Vector2f(0, 0));
	m_pencere.Olustur(genislik, yukseklik, pencereBaslik);
	LeveliYukle(false);
	Ayarla();
	SaatiYenidenBaslat();
	m_kaydirmaZamanlayici.restart();
	m_firlatmaZamanlayici.restart();

	while (m_pencere.AcikMi())
	{
		m_pencere.OlaylarýKontrolEt();

		if (m_saat.getElapsedTime() >= m_cerceveSuresi)
		{
			CizimFonksiyonu();
			SaatiYenidenBaslat();
		}
		else
		{
			sf::sleep(m_cerceveSuresi - m_saat.getElapsedTime());
		}
	}
}

void Oyun::SahneyiLevelIcinHazirla()
{
	m_line->cizgi.setRotation(0);
	m_dortgen->m_konum.y = 0;
	int renkSayac = 0;
	for (int i = 0; i < 4; i++)
	{
		int sayac = 0;
		int soldanUzaklik = 0;
		if (i % 2 == 0) {
			sayac = 8;
		}
		else {
			sayac = 7;
			soldanUzaklik = m_bubbleYaricap;
		}

		for (int j = 0; j < sayac; j++)
		{
			sf::Color color = *(m_levels[m_aktifLevelIndex] + renkSayac);
			if (color != sf::Color::Transparent) {
				BubblePtr m_bubble = Bubble::BubbleUret(m_bubbleYaricap, sf::Vector2f(j * m_bubbleYaricap * 2 + soldanUzaklik, i * 52), color, false);
				m_bubbleListesi.push_back(m_bubble);
			}
			renkSayac++;
		}
	}

	FirlatilacakBubbleOlustur(m_bubbleYaricap);

	m_kaydirmaZamanlayici.restart();
	m_firlatmaZamanlayici.restart();
}

void Oyun::TopuFirlat() {
	if (!m_firlatmayiSurdur) {
		m_firlatilacakBubble->YonAta(m_line->LineAciAl());
		m_firlatmayiSurdur = true;
	}
	m_firlatmaZamanlayici.restart();
}

void Oyun::OyunuKapat()
{
	m_pencere.Kapat();
}

void Oyun::Ayarla()
{
	ArayuzleriYukle();
	OlaylariBagla();
}

void Oyun::KaplamaEkle(sf::String dosyaIsmi, bool arkaPlanOlsunmu)
{
	if (m_aracKaplamaListesi.count(dosyaIsmi) == 0)
	{
		TexturePtr yeniKaplama = std::make_shared<sf::Texture>();
		sf::String yol = "./resimler/" + dosyaIsmi;

		if (arkaPlanOlsunmu)
		{
			if (yeniKaplama->loadFromFile(yol))
			{
				m_aracKaplamaListesi[dosyaIsmi] = yeniKaplama;
			}
		}
		else
		{
			sf::Image image;
			if (image.loadFromFile(yol))
			{
				auto maskeRengi = image.getPixel(0, 0);
				image.createMaskFromColor(maskeRengi);
				yeniKaplama->loadFromImage(image);
				m_aracKaplamaListesi[dosyaIsmi] = yeniKaplama;
			}
		}
	}
}

void Oyun::FareBasilmaKontrolEt(sf::Event::MouseButtonEvent olay)
{
	int x = olay.x;
	int y = olay.y;
	for (auto siradaki : m_panelListesi)
	{
		if (siradaki->icerdemi(x, y))
			siradaki->fareButonBasildi(olay);
	}
}

void Oyun::FareBirakmaKontrolEt(sf::Event::MouseButtonEvent olay)
{
	int x = olay.x;
	int y = olay.y;
	for (auto siradaki : m_panelListesi)
		siradaki->fareButonBirakildi(olay);
}

void Oyun::OlaylariBagla()
{
	m_pencere.KlavyeTusFonksiyonEkle(
		std::bind(&Oyun::KlavyeTusKontrol, this, std::placeholders::_1)
	);

	m_pencere.FareHareketFonksiyonuEkle(
		std::bind(&Oyun::FareHareketKontrolEt, this, std::placeholders::_1, std::placeholders::_2));

	m_pencere.FareBasilmaFonksiyonuEkle(
		std::bind(&Oyun::FareBasilmaKontrolEt, this, std::placeholders::_1));

	m_pencere.FareBirakilmaFonksiyonuEkle(
		std::bind(&Oyun::FareBirakmaKontrolEt, this, std::placeholders::_1));
}

void Oyun::FareHareketKontrolEt(int x, int y)
{
	for (auto siradaki : m_panelListesi)
	{
		if (siradaki->icerdemi(x, y))
			siradaki->fareHareket(x, y);
	}
}

void Oyun::ArayuzleriYukle()
{
	m_font = std::make_shared<sf::Font>();
	if (!m_font->loadFromFile("./fontlar/alev.ttf"))
	{
		std::cout << "font bulunamadi" << std::endl;
	}
	KaplamaEkle("Button.png");
	KaplamaEkle("Windows.png");
	AracPaneliPtr yeniPanel = std::make_shared<AracPaneli>();
	yeniPanel->fontAta(m_font);
	yeniPanel->aracKaplamasi(m_aracKaplamaListesi["Button.png"]);
	yeniPanel->arkaPlanAta(m_aracKaplamaListesi["Windows.png"], sf::IntRect(sf::Vector2i(799, 933), sf::Vector2i(550, 742)));

	auto btnYeniOyun = yeniPanel->butonEkle("Yeni Oyun");
	auto btnCikis = yeniPanel->butonEkle("Cikis");

	btnCikis->tiklaFonksiyonuEkle([&] {
		this->OyunuKapat();
		});

	btnYeniOyun->tiklaFonksiyonuEkle([&] {
		m_panelListesi[0]->gorunurluk(false);
		m_devamEdiyormu = true;
		});

	float x = (m_genislik - yeniPanel->boyutGetir().x) / 2;
	float y = (m_yukseklik - yeniPanel->boyutGetir().y) / 2;
	yeniPanel->konumAta(sf::Vector2f(x, y));

	m_panelListesi.push_back(yeniPanel);
}

void Oyun::KlavyeTusKontrol(sf::Keyboard::Key tiklanilanTus)
{
	switch (tiklanilanTus)
	{
	case sf::Keyboard::Right:
		m_line->Dondur(5);
		break;
	case sf::Keyboard::Left:
		m_line->Dondur(-5);
		break;
	case sf::Keyboard::Space:
		if (m_firlatmayiSurdur) return;
		TopuFirlat();
		break;
	default:
		break;
	}
}

void Oyun::CizimFonksiyonu()
{
	m_pencere.CizimeBasla();

	if (m_devamEdiyormu)
	{
		if (m_kaydirmaZamanlayici.getElapsedTime() >= sf::seconds(7.0f))
		{
			OyunuAsagiyaKaydir();
			m_kaydirmaZamanlayici.restart();
		}

		if (m_firlatmaZamanlayici.getElapsedTime() >= sf::seconds(5.0f))
		{
			std::cout << m_firlatilacakBubble;
			TopuFirlat();
			m_firlatmaZamanlayici.restart();
		}

		if (m_firlatmayiSurdur && m_firlatilacakBubble != NULL) {

			m_firlatilacakBubble->HareketEttir();
			if (CarpismayiKontrolEt()) {
				FirlatilacakBubbleOlustur(m_bubbleYaricap);
			}
			if (FirlatilanSinireUlastimi()) {
				FirlatilaniSiniraYerlestir();
				FirlatilacakBubbleOlustur(m_bubbleYaricap);
			}
		}

		for (auto siradaki : m_bubbleListesi)
		{
			siradaki->Ciz(m_pencere);
		}

		m_line->Ciz(m_pencere);
		m_dortgen->Ciz(m_pencere);
	}
	else
	{
		for (auto siradaki : m_panelListesi)
		{
			siradaki->ciz(m_pencere);
		}
	}

	m_pencere.CizimiBitir();
}

void Oyun::FirlatilacakBubbleOlustur(float bubbleYaricap)
{
	sf::Vector2f bubblePozisyon = sf::Vector2f(m_genislik / 2 - bubbleYaricap, m_yukseklik - bubbleYaricap * 2);
	if (KonumdanBubbleGetir(bubblePozisyon) != NULL) return;
	sf::Color bubbleColor = RastgeleRenkGetir();
	BubblePtr m_bubble = Bubble::BubbleUret(bubbleYaricap, bubblePozisyon, bubbleColor, true);
	m_bubbleListesi.push_back(m_bubble);
	m_firlatilacakBubble = m_bubble;
	m_firlatmayiSurdur = false;
}

bool Oyun::CarpismayiKontrolEt()
{
	for (int i = m_bubbleListesi.size() - 1; i >= 0; i--)
	{
		if (m_firlatilacakBubble == m_bubbleListesi[i]) continue;
		if (m_firlatilacakBubble->CarpistilarMi(m_bubbleListesi[i]))
		{
			AyniRenkleriPatlatmayiDene();
			m_firlatmayiSurdur = false;
			return true;
		}
	}
	return false;
}

bool Oyun::FirlatilanSinireUlastimi()
{
	return m_firlatilacakBubble->m_konum.y <= m_dortgen->m_konum.y ? true : false;
}

void Oyun::FirlatilaniSiniraYerlestir()
{
	int bubbleCap = m_bubbleYaricap * 2;
	int simdikiX = (int)m_firlatilacakBubble->m_konum.x + m_bubbleYaricap;
	int izgaraOncekiX = (simdikiX / bubbleCap) * bubbleCap;
	int izgaraSonrakiX = (simdikiX / bubbleCap + 1) * bubbleCap;
	int secilenX = izgaraOncekiX;
	if ((simdikiX - izgaraOncekiX) > (izgaraSonrakiX - simdikiX))
		secilenX = izgaraSonrakiX;
	auto yeniPozisyon = sf::Vector2f(secilenX, m_dortgen->m_konum.y);
	auto yeniHiz = 0;
	m_firlatilacakBubble->BilgileriGuncelle(yeniPozisyon, yeniHiz);
	AyniRenkleriPatlatmayiDene();
}

void Oyun::AyniRenkleriPatlatmayiDene()
{
	BubbleListesi ayniRenkliBubblelar;

	TemastakiAyniRenkleriBul(ayniRenkliBubblelar, m_firlatilacakBubble);

	if (ayniRenkliBubblelar.size() >= 3) {
		for (int i = ayniRenkliBubblelar.size() - 1; i >= 0; i--)
		{
			BubbleListesindenKaldir(ayniRenkliBubblelar[i]);
			m_firlatilacakBubble = NULL;
		}
		TemasiOlmayanlariPatlatmayiDene();
	}
	OyunBittiMiKontrolEt();
}

void Oyun::TemasiOlmayanlariPatlatmayiDene()
{
	BubbleListesi silinmeyecekler;

	for (auto siradaki : m_bubbleListesi)
	{
		if (siradaki->m_konum.y != m_dortgen->m_konum.y) continue;

		BaglantiliBubblelariOlanlariBul(silinmeyecekler, siradaki);
	}

	m_bubbleListesi = silinmeyecekler;
}

void Oyun::BaglantiliBubblelariOlanlariBul(BubbleListesi& liste, BubblePtr kontrolEdilen)
{
	if (kontrolEdilen == NULL || TekrarEdenBubbleVarmi(liste, kontrolEdilen)) return;
	liste.push_back(kontrolEdilen);

	BubblePtr sagdakiBubble = KonumdanBubbleGetir(kontrolEdilen->SagKonumDon());
	if (sagdakiBubble != NULL) {
		BaglantiliBubblelariOlanlariBul(liste, sagdakiBubble);
	}

	BubblePtr soldakiBubble = KonumdanBubbleGetir(kontrolEdilen->SolKonumDon());
	if (soldakiBubble != NULL) {
		BaglantiliBubblelariOlanlariBul(liste, soldakiBubble);
	}

	BubblePtr sagUstBubble = KonumdanBubbleGetir(kontrolEdilen->SagUstKonumDon());
	if (sagUstBubble != NULL) {
		BaglantiliBubblelariOlanlariBul(liste, sagUstBubble);
	}

	BubblePtr solUstBubble = KonumdanBubbleGetir(kontrolEdilen->SolUstKonumDon());
	if (solUstBubble != NULL) {
		BaglantiliBubblelariOlanlariBul(liste, solUstBubble);
	}

	BubblePtr sagAltBubble = KonumdanBubbleGetir(kontrolEdilen->SagAltKonumDon());
	if (sagAltBubble != NULL) {
		BaglantiliBubblelariOlanlariBul(liste, sagAltBubble);
	}

	BubblePtr solAltBubble = KonumdanBubbleGetir(kontrolEdilen->SolAltKonumDon());
	if (solAltBubble != NULL) {
		BaglantiliBubblelariOlanlariBul(liste, solAltBubble);
	}
}

void Oyun::OyunBittiMiKontrolEt()
{

	for (int i = m_bubbleListesi.size() - 1; i >= 0; i--) {
		BubblePtr bubble = m_bubbleListesi[i];
		if (bubble == m_firlatilacakBubble || bubble == NULL) continue;
		if (bubble->m_konum.y + m_bubbleYaricap * 5.0f >= (float)m_yukseklik) {
			OyunuBastanBaslat();
			break;
		}
	}
	if (m_bubbleListesi.size() == 0) {
		LeveliYukle(true);
	}
}

void Oyun::LeveliYukle(bool sonrakiLevelMi)
{
	if (sonrakiLevelMi)
	{
		m_aktifLevelIndex = (m_aktifLevelIndex + 1) % (m_levelSayisi);
	}
	else {
		m_aktifLevelIndex = 0;
	}
	m_bubbleListesi.clear();
	SahneyiLevelIcinHazirla();
}

void Oyun::OyunuBastanBaslat()
{
	LeveliYukle(false);
}

void Oyun::TemastakiAyniRenkleriBul(BubbleListesi& ayniRenkliBubblelar, BubblePtr temasEden)
{
	if (temasEden == NULL || TekrarEdenBubbleVarmi(ayniRenkliBubblelar, temasEden)) return;
	ayniRenkliBubblelar.push_back(temasEden);

	BubblePtr sagdakiBubble = KonumdanBubbleGetir(temasEden->SagKonumDon());
	if (sagdakiBubble != NULL && sagdakiBubble->m_renk == temasEden->m_renk) {
		TemastakiAyniRenkleriBul(ayniRenkliBubblelar, sagdakiBubble);
	}

	BubblePtr soldakiBubble = KonumdanBubbleGetir(temasEden->SolKonumDon());
	if (soldakiBubble != NULL && soldakiBubble->m_renk == temasEden->m_renk) {
		TemastakiAyniRenkleriBul(ayniRenkliBubblelar, soldakiBubble);
	}

	BubblePtr sagUstBubble = KonumdanBubbleGetir(temasEden->SagUstKonumDon());
	if (sagUstBubble != NULL && sagUstBubble->m_renk == temasEden->m_renk) {
		TemastakiAyniRenkleriBul(ayniRenkliBubblelar, sagUstBubble);
	}

	BubblePtr solUstBubble = KonumdanBubbleGetir(temasEden->SolUstKonumDon());
	if (solUstBubble != NULL && solUstBubble->m_renk == temasEden->m_renk) {
		TemastakiAyniRenkleriBul(ayniRenkliBubblelar, solUstBubble);
	}

	BubblePtr sagAltBubble = KonumdanBubbleGetir(temasEden->SagAltKonumDon());
	if (sagAltBubble != NULL && sagAltBubble->m_renk == temasEden->m_renk) {
		TemastakiAyniRenkleriBul(ayniRenkliBubblelar, sagAltBubble);
	}

	BubblePtr solAltBubble = KonumdanBubbleGetir(temasEden->SolAltKonumDon());
	if (solAltBubble != NULL && solAltBubble->m_renk == temasEden->m_renk) {
		TemastakiAyniRenkleriBul(ayniRenkliBubblelar, solAltBubble);
	}
}

BubblePtr Oyun::KonumdanBubbleGetir(sf::Vector2f konum) {
	for (int i = 0; i < m_bubbleListesi.size(); i++)
	{
		if (m_bubbleListesi[i]->m_konum == konum)
			return m_bubbleListesi[i];
	}
	return NULL;
}

bool Oyun::TekrarEdenBubbleVarmi(BubbleListesi& liste, BubblePtr eleman)
{
	for (auto siradaki : liste) {
		if (siradaki == eleman)
			return true;
	}
	return false;
}

sf::Color Oyun::RastgeleRenkGetir()
{
	if (m_bubbleListesi.size() == 0) return sf::Color::Transparent;
	int randomIndex = rand() % m_bubbleListesi.size();
	return m_bubbleListesi[randomIndex]->m_renk;
}

void Oyun::BubbleListesindenKaldir(BubblePtr bubble)
{
	BubbleListesi guncellenmisListe;

	for (auto siradaki : m_bubbleListesi) {
		if (siradaki == bubble) continue;
		guncellenmisListe.push_back(siradaki);
	}
	m_bubbleListesi.clear();
	for (auto siradaki : guncellenmisListe) {
		m_bubbleListesi.push_back(siradaki);
	}
}

void Oyun::OyunuAsagiyaKaydir()
{
	int kaymaMiktari = m_bubbleYaricap * 2 - 8;
	for (int i = 0; i < m_bubbleListesi.size(); i++)
	{
		if (m_firlatilacakBubble != NULL && m_bubbleListesi[i] == m_firlatilacakBubble) continue;
		m_bubbleListesi[i]->AsagiyaKaydir(kaymaMiktari);
	}
	m_dortgen->AsagiyaKaydir(kaymaMiktari);
	OyunBittiMiKontrolEt();
}

void Oyun::SaatiYenidenBaslat()
{
	m_saat.restart();
}
