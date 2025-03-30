#include "Zolw.h"
#include "Swiat.h"

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
        swiat->usunOrganizm(this);
        swiat->dodajLog(nazwa() + " zosta³ zabity przez " + inny->nazwa());
    }
    else {
        swiat->usunOrganizm(inny);
        polozenie = inny->getPolozenie();
        swiat->dodajLog(nazwa() + " zabi³ " + inny->nazwa());
    }
}
