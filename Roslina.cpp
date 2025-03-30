#include "Roslina.h"
#include "Swiat.h"
#include <cstdlib>

Roslina::Roslina(Swiat* swiat, Punkt polozenie, int sila)
    : Organizm(swiat, polozenie, sila, 0) {
}  // Wszystkie roœliny maj¹ inicjatywê 0

void Roslina::akcja() {
    const int SZANSA_NA_ZASIANIE = 20; // 20% szans na rozprzestrzenienie

    int los = rand() % 100;
    if (los < SZANSA_NA_ZASIANIE) {
        std::vector<Punkt> wolne = swiat->getWolnePolaObok(polozenie);
        if (!wolne.empty()) {
            Punkt nowy = wolne[rand() % wolne.size()];
            swiat->stworzOrganizm(typeid(*this), nowy);
            swiat->dodajLog(nazwa() + " rozsia³ siê");
        }
    }

    zwiekszWiek();
}

// Domyœlnie roœlina nic nie robi przy kolizji – zostanie zjedzona
void Roslina::kolizja(Organizm* inny) {
    // Pusta implementacja – nadpisywana np. w wilczych jagodach
}
