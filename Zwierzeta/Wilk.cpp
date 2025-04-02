#include "Wilk.h"

Wilk::Wilk(Swiat* swiat, Punkt polozenie)
    : Zwierze(USE_EMOJI ? u8"🐺" : "W", swiat, polozenie, 9, 5) {
}

std::string Wilk::nazwa() const {
    return "Wilk";
}
