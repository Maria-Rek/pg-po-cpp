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
            swiat->dodajLog(nazwa() + " rozsia³o siê");
        }
    }

    zwiekszWiek();
}

void Roslina::kolizja(Organizm* inny) {
    if (!swiat || !inny) return;

    swiat->dodajLog(nazwa() + " zosta³o zjedzone przez " + inny->nazwa());
    swiat->usunOrganizm(this);
}
