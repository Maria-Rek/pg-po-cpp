#include "Trawa.h"

Trawa::Trawa(Swiat* swiat, Punkt polozenie)
    : Roslina(swiat, polozenie, 0) {
}  // si³a 0 – nic nie robi w kolizji

char Trawa::rysowanie() const {
    return 'T';
}

std::string Trawa::nazwa() const {
    return "Trawa";
}
