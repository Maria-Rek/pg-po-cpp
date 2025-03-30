#include "Owca.h"

Owca::Owca(Swiat* swiat, Punkt polozenie)
    : Zwierze(swiat, polozenie, 4, 4) {
}  // si³a 4, inicjatywa 4

char Owca::rysowanie() const {
    return 'O';
}

std::string Owca::nazwa() const {
    return "Owca";
}
