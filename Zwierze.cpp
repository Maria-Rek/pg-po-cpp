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
            return;  // Zabezpieczenie: jeśli umrę w kolizji, nie kontynuuj
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
        Punkt jegoPozycja = inny->getPolozenie();     // zapisz pozycję
        std::string jegoNazwa = inny->nazwa();        // zapisz nazwę
        swiat->usunOrganizm(inny);                    // usuń dopiero po zapisie
        polozenie = jegoPozycja;
        swiat->dodajLog(nazwa() + " zabił " + jegoNazwa);
    }
    else {
        std::string mojNazwa = nazwa();               // zapisz swoją nazwę
        swiat->usunOrganizm(this);                    // usuń siebie
        swiat->dodajLog(mojNazwa + " został zabity przez " + inny->nazwa());
    }
}
