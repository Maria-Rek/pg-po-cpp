#include "Lis.h"
#include "Swiat.h"
#include <cstdlib>

Lis::Lis(Swiat* swiat, Punkt polozenie)
    : Zwierze(swiat, polozenie, 3, 7) {
}  // si³a 3, inicjatywa 7

char Lis::rysowanie() const {
    return 'L';
}

std::string Lis::nazwa() const {
    return "Lis";
}

void Lis::akcja() {
    if (!swiat) return;

    std::vector<Punkt> sasiednie = swiat->getSasiedniePola(polozenie);
    std::vector<Punkt> bezpieczne;

    for (const Punkt& p : sasiednie) {
        Organizm* o = swiat->getOrganizmNa(p);
        if (o == nullptr || o->getSila() <= sila) {
            bezpieczne.push_back(p);
        }
    }

    if (!bezpieczne.empty()) {
        Punkt nowaPozycja = bezpieczne[rand() % bezpieczne.size()];
        Organizm* cel = swiat->getOrganizmNa(nowaPozycja);
        if (cel != nullptr) {
            kolizja(cel);
        }
        else {
            polozenie = nowaPozycja;
        }
    }
    else {
        swiat->dodajLog(nazwa() + " nie znalaz³ bezpiecznego pola i pozosta³ w miejscu");
    }

    zwiekszWiek();
}
