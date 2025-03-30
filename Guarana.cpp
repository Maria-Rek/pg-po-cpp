#include "Guarana.h"
#include "Swiat.h"

Guarana::Guarana(Swiat* swiat, Punkt polozenie)
    : Roslina(swiat, polozenie, 0) {
}

char Guarana::rysowanie() const {
    return 'G';
}

std::string Guarana::nazwa() const {
    return "Guarana";
}

void Guarana::kolizja(Organizm* inny) {
    inny->setSila(inny->getSila() + 3);  // bonus +3 do si³y
    std::string atakujacy = inny->nazwa();
    std::string ja = nazwa();
    swiat->usunOrganizm(this);
    swiat->dodajLog(ja + " zosta³a zjedzona przez " + atakujacy + " (zyska³ +3 si³y)");
}
