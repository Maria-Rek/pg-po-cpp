#include "BarszczSosnowskiego.h"
#include "Swiat.h"
#include "Zwierze.h"
#include "CyberOwca.h"  // potrzebne do dynamic_cast
#include <cstdlib>
#include <typeinfo>

BarszczSosnowskiego::BarszczSosnowskiego(Swiat* swiat, Punkt polozenie)
    : Roslina(swiat, polozenie, 10) {
}

char BarszczSosnowskiego::rysowanie() const {
    return 'B';
}

std::string BarszczSosnowskiego::nazwa() const {
    return "Barszcz Sosnowskiego";
}

void BarszczSosnowskiego::akcja() {
    std::vector<Punkt> sasiednie = swiat->getSasiedniePola(polozenie);

    for (const Punkt& p : sasiednie) {
        Organizm* o = swiat->getOrganizmNa(p);
        // Zabija tylko zwierzêta, ale NIE CyberOwce
        if (o != nullptr &&
            dynamic_cast<Zwierze*>(o) != nullptr &&
            dynamic_cast<CyberOwca*>(o) == nullptr) {

            swiat->dodajLog(nazwa() + " zabi³ " + o->nazwa() + " obok siebie");
            swiat->usunOrganizm(o);
        }
    }

    Roslina::akcja();  // mo¿e siê rozmno¿yæ
}

void BarszczSosnowskiego::kolizja(Organizm* inny) {
    if (inny == nullptr || swiat->getOrganizmNa(inny->getPolozenie()) != inny) {
        return; // ju¿ nie istnieje
    }

    swiat->dodajLog(inny->nazwa() + " zjad³ " + nazwa() + " i zgin¹³!");
    swiat->usunOrganizm(inny);

    if (swiat->getOrganizmNa(polozenie) == this) {
        swiat->usunOrganizm(this);
    }
}
