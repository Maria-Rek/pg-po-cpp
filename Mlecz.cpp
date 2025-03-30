#include "Mlecz.h"
#include "Swiat.h"
#include <cstdlib>
#include <typeinfo>

Mlecz::Mlecz(Swiat* swiat, Punkt polozenie)
    : Roslina(swiat, polozenie, 0) {
}

char Mlecz::rysowanie() const {
    return 'M';
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
                swiat->dodajLog(nazwa() + " rozsia³o siê");
            }
        }
    }

    zwiekszWiek();
}
