#include "CyberOwca.h"
#include "Swiat.h"
#include "BarszczSosnowskiego.h"
#include <cstdlib>
#include <cmath>
#include <limits>

CyberOwca::CyberOwca(Swiat* swiat, Punkt polozenie)
    : Zwierze(swiat, polozenie, 11, 4) {
}

char CyberOwca::rysowanie() const {
    return 'C';
}

std::string CyberOwca::nazwa() const {
    return "CyberOwca";
}

void CyberOwca::akcja() {
    Punkt cel = znajdzNajblizszyBarszcz();

    if (cel.x != -1) {
        int dx = (cel.x > polozenie.x) ? 1 : (cel.x < polozenie.x) ? -1 : 0;
        int dy = (cel.y > polozenie.y) ? 1 : (cel.y < polozenie.y) ? -1 : 0;

        Punkt nowaPozycja(polozenie.x + dx, polozenie.y + dy);
        Organizm* celny = swiat->getOrganizmNa(nowaPozycja);
        if (celny)
            kolizja(celny);
        else
            polozenie = nowaPozycja;
    }

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
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}
