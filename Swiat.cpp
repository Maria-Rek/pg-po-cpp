#include "Swiat.h"
#include <iostream>
#include <algorithm>
#include <windows.h>
#include "Wilk.h"
#include "Owca.h"
#include "Zolw.h"
#include "Lis.h"
#include "Antylopa.h"
#include "Trawa.h"
#include "Guarana.h"

Swiat::Swiat(int szerokosc, int wysokosc)
    : szerokosc(szerokosc), wysokosc(wysokosc), tura(1) {
}

Swiat::~Swiat() {
    for (Organizm* o : organizmy)
        delete o;
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
    system("cls");
    std::cout << "--- Tura: " << tura << " ---\n";

    for (int y = 0; y < wysokosc; ++y) {
        for (int x = 0; x < szerokosc; ++x) {
            Organizm* o = getOrganizmNa(Punkt(x, y));
            if (o)
                std::cout << o->rysowanie() << ' ';
            else
                std::cout << ". ";
        }
        std::cout << '\n';
    }

    std::cout << "\n[Zdarzenia]:\n";
    for (const std::string& log : logi)
        std::cout << log << '\n';

    logi.clear();
}

Organizm* Swiat::getOrganizmNa(const Punkt& p) const {
    for (Organizm* o : organizmy) {
        if (o->getPolozenie() == p)
            return o;
    }
    return nullptr;
}

std::vector<Punkt> Swiat::getSasiedniePola(const Punkt& p) const {
    std::vector<Punkt> sasiednie;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            Punkt nowy(p.x + dx, p.y + dy);

            if (nowy.x >= 0 && nowy.x < szerokosc && nowy.y >= 0 && nowy.y < wysokosc)
                sasiednie.push_back(nowy);
        }
    }

    return sasiednie;
}

std::vector<Punkt> Swiat::getWolnePolaObok(const Punkt& p) const {
    std::vector<Punkt> pola = getSasiedniePola(p);
    std::vector<Punkt> wolne;

    for (const Punkt& pt : pola) {
        if (getOrganizmNa(pt) == nullptr)
            wolne.push_back(pt);
    }

    return wolne;
}

void Swiat::stworzOrganizm(const std::type_info& typ, const Punkt& p) {
    if (typ == typeid(Wilk)) organizmy.push_back(new Wilk(this, p));
    else if (typ == typeid(Owca)) organizmy.push_back(new Owca(this, p));
    else if (typ == typeid(Zolw)) organizmy.push_back(new Zolw(this, p));
    else if (typ == typeid(Lis)) organizmy.push_back(new Lis(this, p));
    else if (typ == typeid(Antylopa)) organizmy.push_back(new Antylopa(this, p));
    else if (typ == typeid(Trawa)) organizmy.push_back(new Trawa(this, p));
    else if (typ == typeid(Guarana)) organizmy.push_back(new Guarana(this, p));
}

void Swiat::dodajOrganizm(Organizm* org) {
    organizmy.push_back(org);
}

void Swiat::usunOrganizm(Organizm* org) {
    auto it = std::find(organizmy.begin(), organizmy.end(), org);
    if (it != organizmy.end()) {
        organizmy.erase(it);
        delete org;
    }
}

void Swiat::dodajLog(const std::string& tekst) {
    logi.push_back(tekst);
}

int Swiat::getSzerokosc() const {
    return szerokosc;
}

int Swiat::getWysokosc() const {
    return wysokosc;
}

int Swiat::getTura() const {
    return tura;
}

void Swiat::sortujOrganizmy() {
    std::sort(organizmy.begin(), organizmy.end(), [](Organizm* a, Organizm* b) {
        if (a->getInicjatywa() != b->getInicjatywa())
            return a->getInicjatywa() > b->getInicjatywa();
        return a->getWiek() > b->getWiek();
        });
}
