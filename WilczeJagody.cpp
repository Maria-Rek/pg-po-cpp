#include "WilczeJagody.h"
#include "Swiat.h"

WilczeJagody::WilczeJagody(Swiat* swiat, Punkt polozenie)
    : Roslina(swiat, polozenie, 99) {
}

char WilczeJagody::rysowanie() const {
    return 'J';
}

std::string WilczeJagody::nazwa() const {
    return "Wilcze Jagody";
}

void WilczeJagody::kolizja(Organizm* inny) {
    if (!swiat || !inny) return;

    // Zabezpieczenie: czy ten organizm nadal ¿yje
    if (swiat->getOrganizmNa(inny->getPolozenie()) != inny)
        return;

    std::string atakujacy = inny->nazwa();
    std::string jagody = nazwa();

    swiat->dodajLog(atakujacy + " zjad³ " + jagody + " i zgin¹³!");

    swiat->usunOrganizm(inny);  // atakuj¹cy ginie

    // Czy jagody nadal istniej¹ – sprawdŸ po w³asnym po³o¿eniu
    if (swiat->getOrganizmNa(polozenie) == this) {
        swiat->usunOrganizm(this);
    }
}
