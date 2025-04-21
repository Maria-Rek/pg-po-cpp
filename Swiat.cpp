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
#include <fstream>
#include <sstream>

Swiat::Swiat(int szerokosc, int wysokosc)
    : szerokosc(szerokosc), wysokosc(wysokosc), tura(1) {
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
        if (p.getY() >= 0 && p.getY() < wysokosc && p.getX() >= 0 && p.getX() < szerokosc) {
            if (plansza[p.getY()][p.getX()] == pusty || o->getInicjatywa() > 0) {
                plansza[p.getY()][p.getX()] = o->getIkona();
            }
        }
    }


    std::cout << "\nAutor: Maria Rek (203174)\n";
    std::cout << "--- Tura: " << tura << " ---\n";
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

        if (lowerLog.find("człowiek użył umiejętności") != std::string::npos ||
            lowerLog.find("spalony") != std::string::npos) {
            std::cout << "\033[1;33m";
        }
        else if (lowerLog.find("zabity") != std::string::npos ||
            lowerLog.find("zginął") != std::string::npos ||
            lowerLog.find("zjedz") != std::string::npos ||
            (lowerLog.find("barszcz sosnowskiego") != std::string::npos && lowerLog.find("zabił") != std::string::npos)) {
            std::cout << "\033[1;31m";
        }
        else if (lowerLog.find("rozmnożył") != std::string::npos ||
            lowerLog.find("próbował się rozmnożyć") != std::string::npos) {
            std::cout << "\033[1;36m";
        }
        else if (lowerLog.find("rozsiał") != std::string::npos ||
            lowerLog.find("rozsiało") != std::string::npos) {
            std::cout << "\033[1;32m";
        }
        else {
            std::cout << "\033[1;35m";
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

            Punkt nowy(p.getX() + dx, p.getY() + dy);
            if (nowy.getX() >= 0 && nowy.getX() < szerokosc &&
                nowy.getY() >= 0 && nowy.getY() < wysokosc) {
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
    if (p.getX() < 0 || p.getY() < 0 || p.getX() >= szerokosc || p.getY() >= wysokosc) return;

    if (typ == typeid(Wilk)) organizmy.push_back(new Wilk(this, p));
    else if (typ == typeid(Owca)) organizmy.push_back(new Owca(this, p));
    else if (typ == typeid(Lis)) organizmy.push_back(new Lis(this, p));
    else if (typ == typeid(Zolw)) organizmy.push_back(new Zolw(this, p));
    else if (typ == typeid(Antylopa)) organizmy.push_back(new Antylopa(this, p));
    else if (typ == typeid(Trawa)) organizmy.push_back(new Trawa(this, p));
    else if (typ == typeid(Guarana)) organizmy.push_back(new Guarana(this, p));
    else if (typ == typeid(Mlecz)) organizmy.push_back(new Mlecz(this, p));
    else if (typ == typeid(WilczeJagody)) organizmy.push_back(new WilczeJagody(this, p));
    else if (typ == typeid(BarszczSosnowskiego)) organizmy.push_back(new BarszczSosnowskiego(this, p));
    else if (typ == typeid(CyberOwca)) organizmy.push_back(new CyberOwca(this, p));
    else if (typ == typeid(Czlowiek)) organizmy.push_back(new Czlowiek(this, p));
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

void Swiat::zapiszStanDoPliku(const std::string& nazwaPliku) {
    std::ofstream out(nazwaPliku);
    if (!out.is_open()) {
        std::cerr << "Błąd zapisu do pliku: " << nazwaPliku << std::endl;
        return;
    }

    out << "TURA " << tura << std::endl;
    out << "ROZMIAR " << szerokosc << " " << wysokosc << std::endl;

    for (Organizm* o : organizmy) {
        o->zapisz(out);
    }

    out.close();
    std::cout << "[Zapisano stan gry do pliku: " << nazwaPliku << "]" << std::endl;
}

void Swiat::wczytajStanZPliku(const std::string& nazwaPliku) {
    std::ifstream in(nazwaPliku);
    if (!in.is_open()) {
        std::cerr << "Błąd odczytu pliku: " << nazwaPliku << std::endl;
        return;
    }

    //usuń stare organizmy
    for (Organizm* o : organizmy)
        delete o;
    organizmy.clear();

    std::string linia;
    while (std::getline(in, linia)) {
        std::istringstream iss(linia);
        std::string nazwa;
        iss >> nazwa;

        if (nazwa == "TURA") {
            iss >> tura;
        }
        else if (nazwa == "ROZMIAR") {
            iss >> szerokosc >> wysokosc;
        }
        else {
            int x, y, sila, inicjatywa, wiek;
            iss >> x >> y >> sila >> inicjatywa >> wiek;

            Organizm* nowy = nullptr;
            if (nazwa == "Wilk") nowy = new Wilk(this, Punkt(x, y));
            else if (nazwa == "Owca") nowy = new Owca(this, Punkt(x, y));
            else if (nazwa == "Lis") nowy = new Lis(this, Punkt(x, y));
            else if (nazwa == "Zolw") nowy = new Zolw(this, Punkt(x, y));
            else if (nazwa == "Antylopa") nowy = new Antylopa(this, Punkt(x, y));
            else if (nazwa == "Trawa") nowy = new Trawa(this, Punkt(x, y));
            else if (nazwa == "Guarana") nowy = new Guarana(this, Punkt(x, y));
            else if (nazwa == "Mlecz") nowy = new Mlecz(this, Punkt(x, y));
            else if (nazwa == "WilczeJagody") nowy = new WilczeJagody(this, Punkt(x, y));
            else if (nazwa == "BarszczSosnowskiego") nowy = new BarszczSosnowskiego(this, Punkt(x, y));
            else if (nazwa == "CyberOwca") nowy = new CyberOwca(this, Punkt(x, y));
            else if (nazwa == "Czlowiek") {
                int aktywne, cooldown;
                iss >> aktywne >> cooldown;
                Czlowiek* cz = new Czlowiek(this, Punkt(x, y));
                cz->setSila(sila);
                cz->zwiekszWiek();
                for (int i = 1; i < wiek; ++i)
                    cz->zwiekszWiek();
                cz->setCooldown(aktywne, cooldown);
                organizmy.push_back(cz);
                continue;
            }

            if (nowy) {
                nowy->setSila(sila);
                nowy->zwiekszWiek();  // zwiększ `wiek` x razy
                for (int i = 1; i < wiek; ++i)
                    nowy->zwiekszWiek();
                organizmy.push_back(nowy);
            }
        }
    }

    in.close();
    std::cout << "[Wczytano stan gry z pliku: " << nazwaPliku << "]" << std::endl;
}
