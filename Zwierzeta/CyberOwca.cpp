#pragma execution_character_set("utf-8")
#include "CyberOwca.h"
#include "../Swiat.h"
#include "../Rosliny/BarszczSosnowskiego.h"
#include <cstdlib>
#include <cmath>
#include <limits>
#include <typeinfo>

// CyberOwca – szuka najbliższego Barszczu Sosnowskiego i porusza się w jego stronę

CyberOwca::CyberOwca(Swiat* swiat, Punkt polozenie)
    : Zwierze(USE_EMOJI ? u8"🤖" : "C", swiat, polozenie, 11, 4) {
}

std::string CyberOwca::nazwa() const {
    return "CyberOwca";
}

void CyberOwca::akcja() {
    Punkt cel = znajdzNajblizszyBarszcz();

    if (cel.getX() == -1 && cel.getY() == -1) {
        swiat->dodajLog(nazwa() + " rozglądała się, ale nie znalazła Barszczu Sosnowskiego.");
        return;
    }

    int dx = (cel.getX() > polozenie.getX()) ? 1 : (cel.getX() < polozenie.getX()) ? -1 : 0;
    int dy = (cel.getY() > polozenie.getY()) ? 1 : (cel.getY() < polozenie.getY()) ? -1 : 0;

    Punkt nowaPozycja(polozenie.getX() + dx, polozenie.getY() + dy);

    if (nowaPozycja == polozenie)
        return;

    Organizm* celny = swiat->getOrganizmNa(nowaPozycja);
    if (celny)
        kolizja(celny);
    else
        polozenie = nowaPozycja;

    zwiekszWiek();
}

Punkt CyberOwca::znajdzNajblizszyBarszcz() const {
    Punkt najblizszy(-1, -1);
    int minDystans = std::numeric_limits<int>::max();

    for (int y = 0; y < swiat->getWysokosc(); ++y) {
        for (int x = 0; x < swiat->getSzerokosc(); ++x) {
            Organizm* o = swiat->getOrganizmNa(Punkt(x, y));
            if (o && typeid(*o) == typeid(BarszczSosnowskiego)) {
                int d = dystans(polozenie, Punkt(x, y));
                if (d < minDystans) {
                    minDystans = d;
                    najblizszy = Punkt(x, y);
                }
            }
        }
    }

    return najblizszy;
}

int CyberOwca::dystans(const Punkt& a, const Punkt& b) const {
    return std::abs(a.getX() - b.getX()) + std::abs(a.getY() - b.getY());
}
