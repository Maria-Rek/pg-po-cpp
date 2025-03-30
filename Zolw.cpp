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
    if ((swiat->getTura() - ostatniRuch) >= 4) {
        ostatniRuch = swiat->getTura();  // zapamiêtaj turê

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
    if (inny->getSila() < 5) {
        swiat->dodajLog(nazwa() + " odbi³ atak " + inny->nazwa());
        return;  // ¿ó³w nie zostaje zaatakowany
    }

    // normalna walka
    if (inny->getSila() >= sila) {
        std::string mojNazwa = nazwa();             //  zapisz nazwê przed usuniêciem
        std::string jegoNazwa = inny->nazwa();
        swiat->usunOrganizm(this);
        swiat->dodajLog(mojNazwa + " zosta³ zabity przez " + jegoNazwa);
    }
    else {
        std::string jegoNazwa = inny->nazwa();       // zapisz nazwê przed usuniêciem
        Punkt jegoPozycja = inny->getPolozenie();
        swiat->usunOrganizm(inny);
        polozenie = jegoPozycja;
        swiat->dodajLog(nazwa() + " zabi³ " + jegoNazwa);
    }
}
