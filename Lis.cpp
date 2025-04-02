#include "Lis.h"
#include "Swiat.h"
#include <cstdlib>

Lis::Lis(Swiat* swiat, Punkt polozenie)
    : Zwierze(USE_EMOJI ? u8"🦊" : "L", swiat, polozenie, 3, 7) {
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
        if (cel)
            kolizja(cel);
        else
            polozenie = nowaPozycja;
    }
    else {
        swiat->dodajLog(nazwa() + " nie znalazł bezpiecznego pola i pozostał w miejscu");
    }

    zwiekszWiek();
}
