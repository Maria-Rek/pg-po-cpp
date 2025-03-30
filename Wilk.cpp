#include "Wilk.h"

Wilk::Wilk(Swiat* swiat, Punkt polozenie)
    : Zwierze(swiat, polozenie, 9, 5) {
}  // przyk³adowe: si³a 9, inicjatywa 5

char Wilk::rysowanie() const {
    return 'W';
}

std::string Wilk::nazwa() const {
    return "Wilk";
}

void Wilk::akcja() {
    Zwierze::akcja();  // u¿yj domyœlnej akcji z klasy Zwierze
}
