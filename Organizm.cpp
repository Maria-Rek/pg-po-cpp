#include "Organizm.h"
#include "Swiat.h"

Organizm::Organizm(Swiat* swiat, Punkt polozenie, int sila, int inicjatywa)
    : swiat(swiat), polozenie(polozenie), sila(sila), inicjatywa(inicjatywa), wiek(0) {
}

int Organizm::getSila() const {
    return sila;
}

void Organizm::setSila(int s) {
    sila = s;
}

int Organizm::getInicjatywa() const {
    return inicjatywa;
}

int Organizm::getWiek() const {
    return wiek;
}

void Organizm::zwiekszWiek() {
    ++wiek;
}

Punkt Organizm::getPolozenie() const {
    return polozenie;
}

void Organizm::setPolozenie(Punkt p) {
    polozenie = p;
}

Swiat* Organizm::getSwiat() const {
    return swiat;
}

bool Organizm::czyOdbilAtak(Organizm* /*atakujacy*/) const {
    return false;
}
