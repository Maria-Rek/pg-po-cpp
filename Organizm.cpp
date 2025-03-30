#include "Organizm.h"

Organizm::Organizm(Swiat* swiat, Punkt polozenie, int sila, int inicjatywa)
    : swiat(swiat), polozenie(polozenie), sila(sila), inicjatywa(inicjatywa), wiek(0) {
}

Punkt Organizm::getPolozenie() const {
    return polozenie;
}

int Organizm::getSila() const {
    return sila;
}

int Organizm::getInicjatywa() const {
    return inicjatywa;
}

int Organizm::getWiek() const {
    return wiek;
}

void Organizm::zwiekszWiek() {
    wiek++;
}

void Organizm::zwiekszSile(int ile) {
    sila += ile;
}
