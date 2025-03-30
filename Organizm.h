#pragma once

#include "Punkt.h"
#include <string>

class Swiat;

class Organizm {
protected:
    Swiat* swiat;
    Punkt polozenie;
    int sila;
    int inicjatywa;
    int wiek;

public:
    Organizm(Swiat* swiat, Punkt polozenie, int sila, int inicjatywa);
    virtual ~Organizm() = default;

    virtual void akcja() = 0;
    virtual void kolizja(Organizm* inny) = 0;
    virtual char rysowanie() const = 0;
    virtual std::string nazwa() const = 0;

    Punkt getPolozenie() const;
    int getSila() const;
    int getInicjatywa() const;
    int getWiek() const;

    void zwiekszWiek();
    void zwiekszSile(int ile);
};
