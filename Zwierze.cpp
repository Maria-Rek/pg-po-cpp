#pragma execution_character_set("utf-8")
#include "Zwierze.h"
#include "Swiat.h"
#include <cstdlib>
#include <typeinfo>

Zwierze::Zwierze(std::string ikona, Swiat* swiat, Punkt polozenie, int sila, int inicjatywa)
    : Organizm(swiat, polozenie, sila, inicjatywa) {
    this->ikona = ikona;
}

void Zwierze::akcja() {
    if (!swiat) return;

    std::vector<Punkt> sasiednie = swiat->getSasiedniePola(polozenie);

    if (!sasiednie.empty()) {
        Punkt nowaPozycja = sasiednie[rand() % sasiednie.size()];
        Organizm* cel = swiat->getOrganizmNa(nowaPozycja);

        if (cel)
            kolizja(cel);
        else
            polozenie = nowaPozycja;
    }

    zwiekszWiek();
}

void Zwierze::kolizja(Organizm* inny) {
    if (!swiat || !inny) return;

    if (typeid(*this) == typeid(*inny)) {
        std::vector<Punkt> wolne = swiat->getWolnePolaObok(polozenie);
        if (!wolne.empty()) {
            Punkt dzieckoPozycja = wolne[rand() % wolne.size()];
            swiat->stworzOrganizm(typeid(*this), dzieckoPozycja);
            swiat->dodajLog(nazwa() + " rozmnożył się");
        }
        return;
    }

    if (inny->czyOdbilAtak(this)) {
        swiat->dodajLog(inny->nazwa() + " odbił atak " + nazwa());
        return;
    }

    std::string nazwaA = nazwa();
    std::string nazwaB = inny->nazwa();

    if (inny->getSila() <= sila) {
        Punkt jegoPozycja = inny->getPolozenie();
        swiat->dodajLog(nazwaA + " zabił " + nazwaB);
        swiat->usunOrganizm(inny);
        polozenie = jegoPozycja;
    }
    else {
        swiat->dodajLog(nazwaA + " został zabity przez " + nazwaB);
        swiat->usunOrganizm(this);
    }
}
