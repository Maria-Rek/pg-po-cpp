#pragma execution_character_set("utf-8")
#include "Antylopa.h"
#include "../Swiat.h"
#include "../Roslina.h"
#include <cstdlib>

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
        int dx = p.x - polozenie.x;
        int dy = p.y - polozenie.y;
        Punkt dalej(p.x + dx, p.y + dy);

        if (dalej.x >= 0 && dalej.x < swiat->getSzerokosc() &&
            dalej.y >= 0 && dalej.y < swiat->getWysokosc()) {
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

    //Antylopa nie ucieka przed roślinami
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
