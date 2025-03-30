#include "Swiat.h"
#include <iostream>
#include <algorithm>
#include <typeinfo>
#include "Wilk.h"  // tymczasowo, póŸniej dodasz inne organizmy

Swiat::Swiat(int szerokosc, int wysokosc)
    : szerokosc(szerokosc), wysokosc(wysokosc), tura(1) {
}

Swiat::~Swiat() {
    for (Organizm* o : organizmy) {
        delete o;
    }
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
    if (typ == typeid(Wilk)) {
        organizmy.push_back(new Wilk(this, p));
    }
    // Dodasz tu inne typy organizmów w przysz³oœci
}

void Swiat::dodajOrganizm(Organizm* org) {
    organizmy.push_back(org);
}

void Swiat::usunOrganizm(Organizm* org) {
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
