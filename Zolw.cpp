#include "Zolw.h"
#include "Swiat.h"
#include <cstdlib>

Zolw::Zolw(Swiat* swiat, Punkt polozenie)
    : Zwierze(swiat, polozenie, 2, 1), ostatniRuch(0) {
}

char Zolw::rysowanie() const {
    return 'Z';
}

std::string Zolw::nazwa() const {
    return "Zolw";
}

void Zolw::akcja() {
    if (!swiat) return;

    if ((swiat->getTura() - ostatniRuch) >= 4) {
        ostatniRuch = swiat->getTura();

        std::vector<Punkt> sasiednie = swiat->getSasiedniePola(polozenie);
        if (!sasiednie.empty()) {
            Punkt nowy = sasiednie[rand() % sasiednie.size()];
            Organizm* cel = swiat->getOrganizmNa(nowy);
            if (cel)
                kolizja(cel);
            else
                polozenie = nowy;
        }
    }

    zwiekszWiek();
}

void Zolw::kolizja(Organizm* inny) {
    if (!swiat || !inny) return;

    if (inny->getSila() < 5) {
        swiat->dodajLog(nazwa() + " odbi³ atak " + inny->nazwa());
        return;
    }

    std::string mojNazwa = nazwa();
    std::string jegoNazwa = inny->nazwa();

    if (inny->getSila() >= sila) {
        swiat->dodajLog(mojNazwa + " zosta³ zabity przez " + jegoNazwa);
        swiat->usunOrganizm(this);
    }
    else {
        Punkt jegoPozycja = inny->getPolozenie();
        swiat->dodajLog(nazwa() + " zabi³ " + jegoNazwa);
        swiat->usunOrganizm(inny);
        polozenie = jegoPozycja;
    }
}
