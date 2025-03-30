#include "Swiat.h"
#include <iostream>
#include <algorithm>
#include <typeinfo>

#include "Wilk.h"
#include "Owca.h"
#include "Lis.h"
#include "Zolw.h"
#include "Antylopa.h"
#include "Trawa.h"
#include "Guarana.h"
#include "Mlecz.h"
#include "WilczeJagody.h"

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
    std::vector<std::vector<char>> plansza(wysokosc, std::vector<char>(szerokosc, '.'));

    for (Organizm* o : organizmy) {
        Punkt p = o->getPolozenie();
        if (p.y >= 0 && p.y < wysokosc && p.x >= 0 && p.x < szerokosc)
            plansza[p.y][p.x] = o->rysowanie();
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
        std::cout << "- " << log << '\n';
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
    const int dx[] = { -1, 1, 0, 0 };
    const int dy[] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; ++i) {
        Punkt nowy(p.x + dx[i], p.y + dy[i]);
        if (nowy.x >= 0 && nowy.x < szerokosc && nowy.y >= 0 && nowy.y < wysokosc)
            pola.push_back(nowy);
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
    if (typ == typeid(Wilk)) organizmy.push_back(new Wilk(this, p));
    else if (typ == typeid(Owca)) organizmy.push_back(new Owca(this, p));
    else if (typ == typeid(Lis)) organizmy.push_back(new Lis(this, p));
    else if (typ == typeid(Zolw)) organizmy.push_back(new Zolw(this, p));
    else if (typ == typeid(Antylopa)) organizmy.push_back(new Antylopa(this, p));
    else if (typ == typeid(Trawa)) organizmy.push_back(new Trawa(this, p));
    else if (typ == typeid(Guarana)) organizmy.push_back(new Guarana(this, p));
    else if (typ == typeid(Mlecz)) organizmy.push_back(new Mlecz(this, p));
    else if (typ == typeid(WilczeJagody)) organizmy.push_back(new WilczeJagody(this, p));
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
