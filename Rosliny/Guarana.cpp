#include "Guarana.h"
#include "../Swiat.h"

Guarana::Guarana(Swiat* swiat, Punkt polozenie)
    : Roslina(USE_EMOJI ? u8"🍒" : "G", swiat, polozenie, 0) {
}

std::string Guarana::nazwa() const {
    return "Guarana";
}

void Guarana::kolizja(Organizm* inny) {
    if (swiat && inny) {
        int nowaSila = inny->getSila() + 3;
        inny->setSila(nowaSila);

        swiat->dodajLog(nazwa() + " została zjedzona przez " + inny->nazwa() + " (zyskał +3 siły)");
        swiat->usunOrganizm(this);
    }
}
