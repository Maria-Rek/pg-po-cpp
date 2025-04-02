#pragma once
#define USE_EMOJI 1

#include "Punkt.h"
#include <string>

class Swiat;

class Organizm {
protected:
    int sila;
    int inicjatywa;
    int wiek;
    Punkt polozenie;
    Swiat* swiat;
    std::string ikona;

public:
    Organizm(Swiat* swiat, Punkt polozenie, int sila, int inicjatywa);
    virtual ~Organizm() = default;

    virtual void akcja() = 0;
    virtual void kolizja(Organizm* inny) = 0;
    virtual std::string nazwa() const = 0;

    int getSila() const;
    void setSila(int s);
    int getInicjatywa() const;
    int getWiek() const;
    void zwiekszWiek();
    Punkt getPolozenie() const;
    void setPolozenie(Punkt p);
    Swiat* getSwiat() const;
    std::string getIkona() const;

    virtual bool czyOdbilAtak(Organizm* atakujacy) const;
};
