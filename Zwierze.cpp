#include "Zwierze.h"
#include "Swiat.h"
#include <cstdlib>
#include <ctime>
#include <typeinfo>

Zwierze::Zwierze(Swiat* swiat, Punkt polozenie, int sila, int inicjatywa)
    : Organizm(swiat, polozenie, sila, inicjatywa) {
}

void Zwierze::akcja() {
    std::vector<Punkt> sasiednie = swiat->getSasiedniePola(polozenie);

    if (!sasiednie.empty()) {
        Punkt nowaPozycja = sasiednie[rand() % sasiednie.size()];
        Organizm* cel = swiat->getOrganizmNa(nowaPozycja);

        if (cel != nullptr) {
            kolizja(cel);
        }
        else {
            polozenie = nowaPozycja;
        }
    }

    zwiekszWiek();
}

void Zwierze::kolizja(Organizm* inny) {
    if (typeid(*this) == typeid(*inny)) {
        std::vector<Punkt> wolne = swiat->getWolnePolaObok(polozenie);
        if (!wolne.empty()) {
            Punkt dzieckoPozycja = wolne[rand() % wolne.size()];
            swiat->stworzOrganizm(typeid(*this), dzieckoPozycja);
            swiat->dodajLog(nazwa() + " rozmno¿y³ siê");
        }
        return;
    }

    // Walka – wygrywa silniejszy
    if (inny->getSila() <= sila) {
        swiat->usunOrganizm(inny);
        polozenie = inny->getPolozenie();
        swiat->dodajLog(nazwa() + " zabi³ " + inny->nazwa());
    }
    else {
        swiat->usunOrganizm(this);
        swiat->dodajLog(nazwa() + " zosta³ zabity przez " + inny->nazwa());
    }
}
