#include "Guarana.h"
#include "Swiat.h"

Guarana::Guarana(Swiat* swiat, Punkt polozenie)
    : Roslina(swiat, polozenie, 0) {
}  // zgodnie z Twoim konstruktorem

char Guarana::rysowanie() const {
    return 'G';
}

std::string Guarana::nazwa() const {
    return "Guarana";
}

void Guarana::kolizja(Organizm* inny) {
    if (inny != nullptr) {
        inny->zwiekszSile(3);
        swiat->dodajLog(inny->nazwa() + " zjad³ Guaranê i zyska³ 3 si³y");
        swiat->usunOrganizm(this);
    }
}
