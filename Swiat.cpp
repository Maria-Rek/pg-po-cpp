#pragma execution_character_set("utf-8")
#include "Swiat.h"
#include "Zwierzeta/Wilk.h"
#include "Zwierzeta/Owca.h"
#include "Zwierzeta/Lis.h"
#include "Zwierzeta/Zolw.h"
#include "Zwierzeta/Antylopa.h"
#include "Rosliny/Trawa.h"
#include "Rosliny/Guarana.h"
#include "Rosliny/Mlecz.h"
#include "Rosliny/WilczeJagody.h"
#include "Rosliny/BarszczSosnowskiego.h"
#include "Zwierzeta/CyberOwca.h"
#include "Czlowiek.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>

Swiat::Swiat(int szerokosc, int wysokosc)
    : szerokosc(szerokosc), wysokosc(wysokosc), tura(1) {
    // Człowiek dodawany później z main.cpp
}

Swiat::~Swiat() {
    for (Organizm* o : organizmy)
        delete o;
    organizmy.clear();
}

void Swiat::wykonajTure() {
    sortujOrganizmy();
    std::vector<Organizm*> doWykonania = organizmy;

    for (Organizm* o : doWykonania) {
        if (std::find(organizmy.begin(), organizmy.end(), o) != organizmy.end()) {
            o->akcja();
        }
    }

    tura++;
}

void Swiat::rysujSwiat() {
    std::string pusty = USE_EMOJI ? u8"⬛" : ".";

    std::vector<std::vector<std::string>> plansza(wysokosc, std::vector<std::string>(szerokosc, pusty));

    for (Organizm* o : organizmy) {
        Punkt p = o->getPolozenie();
        if (p.y >= 0 && p.y < wysokosc && p.x >= 0 && p.x < szerokosc) {
            if (plansza[p.y][p.x] == pusty || o->getInicjatywa() > 0) {
                plansza[p.y][p.x] = o->getIkona();  // zwierzęta nadpisują rośliny
            }
        }
    }

    std::cout << "\n--- Tura: " << tura << " ---\n";
    for (int y = 0; y < wysokosc; ++y) {
        for (int x = 0; x < szerokosc; ++x) {
            std::cout << plansza[y][x] << ' ';
        }
        std::cout << '\n';
    }

    std::cout << "\n[Zdarzenia]:\n";
    for (const std::string& log : logi) {
        std::string lowerLog = log;
        std::transform(lowerLog.begin(), lowerLog.end(), lowerLog.begin(), [](unsigned char c) {
            return std::tolower(c);
            });

        if (lowerLog.find("zabity") != std::string::npos ||
            lowerLog.find("zginął") != std::string::npos ||
            lowerLog.find("zjedz") != std::string::npos ||
            (lowerLog.find("barszcz sosnowskiego") != std::string::npos && lowerLog.find("zabił") != std::string::npos)) {
            std::cout << "\033[1;31m";  // czerwony
        }
        else if (lowerLog.find("zamrożon") != std::string::npos ||
            lowerLog.find("zamrożenie") != std::string::npos) {
            std::cout << "\033[1;36m";  // jasny niebieski)
        }
        else if (lowerLog.find("rozsiał") != std::string::npos ||
            lowerLog.find("rozsiało") != std::string::npos) {
            std::cout << "\033[1;32m";  // zielony
        }
        else if (lowerLog.find("rozmnożył") != std::string::npos) {
            std::cout << "\033[1;33m";  // pomarańczowy
        }
        else {
            std::cout << "\033[1;35m";  // różowy
        }

        std::cout << "- " << log << "\033[0m\n";
    }
    logi.clear();
}

void Swiat::sortujOrganizmy() {
    std::sort(organizmy.begin(), organizmy.end(),
        [](Organizm* a, Organizm* b) {
            if (a->getInicjatywa() != b->getInicjatywa())
                return a->getInicjatywa() > b->getInicjatywa();
            return a->getWiek() > b->getWiek();
        });
}

Organizm* Swiat::getOrganizmNa(const Punkt& p) const {
    for (Organizm* o : organizmy) {
        if (o->getPolozenie() == p)
            return o;
    }
    return nullptr;
}

std::vector<Punkt> Swiat::getSasiedniePola(const Punkt& p) const {
    std::vector<Punkt> pola;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;

            Punkt nowy(p.x + dx, p.y + dy);
            if (nowy.x >= 0 && nowy.x < szerokosc &&
                nowy.y >= 0 && nowy.y < wysokosc) {
                pola.push_back(nowy);
            }
        }
    }

    return pola;
}

std::vector<Punkt> Swiat::getWolnePolaObok(const Punkt& p) const {
    std::vector<Punkt> wolne;
    std::vector<Punkt> wszystkie = getSasiedniePola(p);

    for (const Punkt& pole : wszystkie) {
        if (getOrganizmNa(pole) == nullptr)
            wolne.push_back(pole);
    }

    return wolne;
}

void Swiat::stworzOrganizm(const std::type_info& typ, const Punkt& p) {
    if (p.x < 0 || p.y < 0 || p.x >= szerokosc || p.y >= wysokosc) return;

    if (typ == typeid(Wilk))
        organizmy.push_back(new Wilk(this, p));
    else if (typ == typeid(Owca))
        organizmy.push_back(new Owca(this, p));
    else if (typ == typeid(Lis))
        organizmy.push_back(new Lis(this, p));
    else if (typ == typeid(Zolw))
        organizmy.push_back(new Zolw(this, p));
    else if (typ == typeid(Antylopa))
        organizmy.push_back(new Antylopa(this, p));
    else if (typ == typeid(Trawa))
        organizmy.push_back(new Trawa(this, p));
    else if (typ == typeid(Guarana))
        organizmy.push_back(new Guarana(this, p));
    else if (typ == typeid(Mlecz))
        organizmy.push_back(new Mlecz(this, p));
    else if (typ == typeid(WilczeJagody))
        organizmy.push_back(new WilczeJagody(this, p));
    else if (typ == typeid(BarszczSosnowskiego))
        organizmy.push_back(new BarszczSosnowskiego(this, p));
    else if (typ == typeid(CyberOwca))
        organizmy.push_back(new CyberOwca(this, p));
    else if (typ == typeid(Czlowiek))
        organizmy.push_back(new Czlowiek(this, p));
}

void Swiat::dodajOrganizm(Organizm* org) {
    if (org) organizmy.push_back(org);
}

void Swiat::usunOrganizm(Organizm* org) {
    if (!org) return;
    auto it = std::find(organizmy.begin(), organizmy.end(), org);
    if (it != organizmy.end()) {
        delete* it;
        organizmy.erase(it);
    }
}

void Swiat::dodajLog(const std::string& tekst) {
    logi.push_back(tekst);
}

int Swiat::getSzerokosc() const { return szerokosc; }
int Swiat::getWysokosc() const { return wysokosc; }
int Swiat::getTura() const { return tura; }

const std::vector<Organizm*>& Swiat::getOrganizmy() const {
    return organizmy;
}
