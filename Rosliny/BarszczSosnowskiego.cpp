#pragma execution_character_set("utf-8")
#include "BarszczSosnowskiego.h"
#include "../Swiat.h"
#include "../Zwierze.h"
#include "../Zwierzeta/CyberOwca.h"
#include <cstdlib>
#include <typeinfo>

BarszczSosnowskiego::BarszczSosnowskiego(Swiat* swiat, Punkt polozenie)
    : Roslina(USE_EMOJI ? u8"🧪" : "B", swiat, polozenie, 10) {
}

std::string BarszczSosnowskiego::nazwa() const {
    return "Barszcz Sosnowskiego";
}

void BarszczSosnowskiego::akcja() {
    std::vector<Punkt> sasiednie = swiat->getSasiedniePola(polozenie);

    for (const Punkt& p : sasiednie) {
        Organizm* o = swiat->getOrganizmNa(p);
        if (o && dynamic_cast<Zwierze*>(o) && dynamic_cast<CyberOwca*>(o) == nullptr) {
            swiat->dodajLog(nazwa() + " zabił " + o->nazwa() + " obok siebie");
            swiat->usunOrganizm(o);
        }
    }

    Roslina::akcja();
}

void BarszczSosnowskiego::kolizja(Organizm* inny) {
    if (!inny || swiat->getOrganizmNa(inny->getPolozenie()) != inny) return;

    if (dynamic_cast<CyberOwca*>(inny)) {
        swiat->dodajLog(inny->nazwa() + " zjadł " + nazwa() + " i przetrwał!");
        swiat->usunOrganizm(this);
    }
    else {
        swiat->dodajLog(inny->nazwa() + " zjadł " + nazwa() + " i zginął!");
        swiat->usunOrganizm(inny);
        if (swiat->getOrganizmNa(polozenie) == this) {
            swiat->usunOrganizm(this);
        }
    }
}
