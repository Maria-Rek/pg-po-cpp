#include "WilczeJagody.h"
#include "Swiat.h"

WilczeJagody::WilczeJagody(Swiat* swiat, Punkt polozenie)
    : Roslina(USE_EMOJI ? u8"☠️" : "J", swiat, polozenie, 99) {
}

std::string WilczeJagody::nazwa() const {
    return "Wilcze Jagody";
}

void WilczeJagody::kolizja(Organizm* inny) {
    if (!swiat || !inny) return;

    if (swiat->getOrganizmNa(inny->getPolozenie()) != inny)
        return;

    swiat->dodajLog(inny->nazwa() + " zjadł " + nazwa() + " i zginął!");
    swiat->usunOrganizm(inny);

    if (swiat->getOrganizmNa(polozenie) == this) {
        swiat->usunOrganizm(this);
    }
}
