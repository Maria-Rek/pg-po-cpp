#pragma execution_character_set("utf-8")
#include "Zwierze.h"
#include "Swiat.h"
#include "Roslina.h"
#include <cstdlib>
#include <typeinfo>

Zwierze::Zwierze(std::string ikona, Swiat* swiat, Punkt polozenie, int sila, int inicjatywa)
    : Organizm(swiat, polozenie, sila, inicjatywa) {
    this->ikona = ikona;
}

void Zwierze::akcja() {
    if (!swiat) return;

    // DEBUG: log siły i wieku przed akcją
    //swiat->dodajLog(nazwa() + " – Siła: " + std::to_string(getSila()));
    //swiat->dodajLog(nazwa() + " – Wiek: " + std::to_string(getWiek()));

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

    if (inny->nazwa() == "Trawa" || inny->nazwa() == "Mlecz") {
        polozenie = inny->getPolozenie();
        swiat->dodajLog(nazwa() + " wszedł na " + inny->nazwa() + ", ale jej nie zjadł");
        return;
    }

    if (typeid(*this) == typeid(*inny)) {
        std::vector<Punkt> wolne = swiat->getWolnePolaObok(polozenie);
        if (!wolne.empty()) {
            Punkt dzieckoPozycja = wolne[rand() % wolne.size()];
            swiat->stworzOrganizm(typeid(*this), dzieckoPozycja);
            swiat->dodajLog(nazwa() + " rozmnożył się");
        }
        else {
            swiat->dodajLog(nazwa() + " próbował się rozmnożyć, ale nie było wolnego miejsca.");
        }
        return;
    }

    if (inny->czyOdbilAtak(this)) {
        swiat->dodajLog(inny->nazwa() + " odbił atak " + nazwa());
        return;
    }

    //Jeśli inny to roślina – pozwól jej samej obsłużyć kolizję
    if (dynamic_cast<Roslina*>(inny)) {
        inny->kolizja(this);
        return;
    }

    std::string nazwaA = nazwa();
    std::string nazwaB = inny->nazwa();

    if (inny->getSila() <= sila) {
        Punkt jegoPozycja = inny->getPolozenie();
        swiat->dodajLog(nazwaB + " został zabity przez " + nazwaA);

        // DEBUG: log siły zwycięzcy
        //swiat->dodajLog("Siła " + nazwaA + ": " + std::to_string(sila));

        polozenie = jegoPozycja;
        swiat->usunOrganizm(inny);
    }
    else {
        swiat->dodajLog(nazwaA + " został zabity przez " + nazwaB);

        // DEBUG: log siły przeciwnika
        //swiat->dodajLog("Siła " + nazwaB + ": " + std::to_string(inny->getSila()));

        swiat->usunOrganizm(this);
    }
}
