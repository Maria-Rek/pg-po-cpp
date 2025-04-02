#include "Trawa.h"

Trawa::Trawa(Swiat* swiat, Punkt polozenie)
    : Roslina(USE_EMOJI ? u8"🌿" : "T", swiat, polozenie, 0) {
}  // siła 0 – nic nie robi w kolizji

std::string Trawa::nazwa() const {
    return "Trawa";
}
