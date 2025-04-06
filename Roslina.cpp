#pragma execution_character_set("utf-8")
#include "Roslina.h"
#include "Swiat.h"
#include <cstdlib>
#include <typeinfo>

Roslina::Roslina(const std::string& ikona, Swiat* swiat, Punkt polozenie, int sila)
    : Organizm(swiat, polozenie, sila, 0) {
    this->ikona = ikona;
}

void Roslina::akcja() {
    if (!swiat) return;

    if (rand() % 10 == 0) {
        std::vector<Punkt> wolne = swiat->getWolnePolaObok(polozenie);
        if (!wolne.empty()) {
            Punkt nowy = wolne[rand() % wolne.size()];
            swiat->stworzOrganizm(typeid(*this), nowy);
            swiat->dodajLog(nazwa() + " rozsiało się");
        }
    }

    zwiekszWiek();
}

void Roslina::kolizja(Organizm* inny) {
    if (!swiat || !inny) return;

    if (nazwa() == "Trawa" || nazwa() == "Mlecz") {
        swiat->dodajLog(nazwa() + " została przygnieciona przez " + inny->nazwa() + ", ale przetrwała");
        return;
    }

    swiat->dodajLog(nazwa() + " zostało zjedzone przez " + inny->nazwa());
    swiat->usunOrganizm(this);
}
