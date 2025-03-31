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

bool Zolw::czyOdbilAtak(Organizm* atakujacy) const {
    return atakujacy->getSila() < 5;
}
