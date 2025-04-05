#pragma execution_character_set("utf-8")
#include "Mlecz.h"
#include "../Swiat.h"
#include <cstdlib>
#include <typeinfo>

Mlecz::Mlecz(Swiat* swiat, Punkt polozenie)
    : Roslina(USE_EMOJI ? u8"🌼" : "M", swiat, polozenie, 0) {
}

std::string Mlecz::nazwa() const {
    return "Mlecz";
}

void Mlecz::akcja() {
    if (!swiat) return;

    for (int i = 0; i < 3; ++i) {
        if (rand() % 10 == 0) {
            std::vector<Punkt> wolne = swiat->getWolnePolaObok(polozenie);
            if (!wolne.empty()) {
                Punkt nowy = wolne[rand() % wolne.size()];
                swiat->stworzOrganizm(typeid(*this), nowy);
                swiat->dodajLog(nazwa() + " rozsiało się");
            }
        }
    }

    zwiekszWiek();
}
