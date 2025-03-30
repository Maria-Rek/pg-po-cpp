#pragma once

#include "Punkt.h"
#include <string>

class Swiat;  // forward declaration

class Organizm {
protected:
    int sila;
    int inicjatywa;
    int wiek;
    Punkt polozenie;
    Swiat* swiat;

public:
    Organizm(Swiat* swiat, Punkt polozenie, int sila, int inicjatywa);
    virtual ~Organizm() = default;

    virtual void akcja() = 0;
    virtual void kolizja(Organizm* inny) = 0;
    virtual char rysowanie() const = 0;
    virtual std::string nazwa() const = 0;

    // Gettery i settery
    int getSila() const;
    void setSila(int s);
    int getInicjatywa() const;
    int getWiek() const;
    void zwiekszWiek();
    Punkt getPolozenie() const;
    void setPolozenie(Punkt p);
    Swiat* getSwiat() const;
};
