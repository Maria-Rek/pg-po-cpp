#include "Zwierze.h"
#include "Swiat.h"
#include <cstdlib>
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
            swiat->dodajLog(nazwa() + " rozmnożył się");
        }

        return;
    }

    if (inny->getSila() <= sila) {
        std::string jegoNazwa = inny->nazwa();
        Punkt jegoPozycja = inny->getPolozenie();
        swiat->usunOrganizm(inny);
        polozenie = jegoPozycja;
        swiat->dodajLog(nazwa() + " zabił " + jegoNazwa);
    }
    else {
        std::string mojaNazwa = nazwa();
        swiat->usunOrganizm(this);
        swiat->dodajLog(mojaNazwa + " został zabity przez " + inny->nazwa());
    }
}
