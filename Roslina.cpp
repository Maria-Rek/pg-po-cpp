#include "Roslina.h"
#include "Swiat.h"
#include <cstdlib>
#include <typeinfo>

Roslina::Roslina(Swiat* swiat, Punkt polozenie, int sila)
    : Organizm(swiat, polozenie, sila, 0) {
}

void Roslina::akcja() {
    if (!swiat) return;

    if (rand() % 10 == 0) { // 10% szansy
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

    std::string nazwaRosliny = nazwa();
    std::string nazwaAtakujacego = inny->nazwa();

    swiat->dodajLog(nazwaRosliny + " zosta³o zjedzone przez " + nazwaAtakujacego);
    swiat->usunOrganizm(this);
}
