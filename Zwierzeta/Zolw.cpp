#pragma execution_character_set("utf-8")
#include "Zolw.h"
#include "../Swiat.h"
#include <cstdlib>

Zolw::Zolw(Swiat* swiat, Punkt polozenie)
    : Zwierze(USE_EMOJI ? u8"🐢" : "Z", swiat, polozenie, 2, 1) {
}

std::string Zolw::nazwa() const {
    return "Zolw";
}

void Zolw::akcja() {
    if (!swiat) return;

    // 25% szansy na ruch
    if (rand() % 4 == 0) {
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
    else {
        swiat->dodajLog("Żółw nie poruszył się (25% szansy na ruch)");
    }

    zwiekszWiek();
}

bool Zolw::czyOdbilAtak(Organizm* atakujacy) const {
    return atakujacy->getSila() < 5;
}
