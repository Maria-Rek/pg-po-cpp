#include "Owca.h"

Owca::Owca(Swiat* swiat, Punkt polozenie)
    : Zwierze(USE_EMOJI ? u8"🐑" : "O", swiat, polozenie, 4, 4) {
}

std::string Owca::nazwa() const {
    return "Owca";
}
