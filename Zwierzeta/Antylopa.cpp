#pragma execution_character_set("utf-8")
#include "Antylopa.h"
#include "../Swiat.h"
#include "../Roslina.h"
#include <cstdlib>

// Antylopa – porusza się o 2 pola i ma 50% szans na ucieczkę w kolizji

Antylopa::Antylopa(Swiat* swiat, Punkt polozenie)
    : Zwierze(USE_EMOJI ? u8"🦌" : "A", swiat, polozenie, 4, 4) {
}

std::string Antylopa::nazwa() const {
    return "Antylopa";
}

void Antylopa::akcja() {
    std::vector<Punkt> sasiednie = swiat->getSasiedniePola(polozenie);
    std::vector<Punkt> dalsze;

    for (const Punkt& p : sasiednie) {
        int dx = p.getX() - polozenie.getX();
        int dy = p.getY() - polozenie.getY();
        Punkt dalej(p.getX() + dx, p.getY() + dy);

        if (dalej.getX() >= 0 && dalej.getX() < swiat->getSzerokosc() &&
            dalej.getY() >= 0 && dalej.getY() < swiat->getWysokosc()) {
            dalsze.push_back(dalej);
        }
    }

    if (!dalsze.empty()) {
        Punkt cel = dalsze[rand() % dalsze.size()];
        Organizm* o = swiat->getOrganizmNa(cel);

        if (o != nullptr) {
            kolizja(o);
        }
        else {
            polozenie = cel;
        }
    }

    zwiekszWiek();
}

void Antylopa::kolizja(Organizm* inny) {
    if (!swiat || !inny) return;

    if (dynamic_cast<Roslina*>(inny)) {
        Zwierze::kolizja(inny);
        return;
    }

    if (rand() % 2 == 0) {
        std::vector<Punkt> wolne = swiat->getWolnePolaObok(polozenie);
        if (!wolne.empty()) {
            Punkt ucieczka = wolne[rand() % wolne.size()];
            polozenie = ucieczka;
            swiat->dodajLog(nazwa() + " uciekła przed " + inny->nazwa());
            return;
        }
    }

    Zwierze::kolizja(inny);
}
