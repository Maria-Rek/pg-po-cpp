#pragma once

#include "Organizm.h"

class Roslina : public Organizm {
public:
    Roslina(Swiat* swiat, Punkt polozenie, int sila);

    virtual void akcja() override;
    virtual void kolizja(Organizm* inny) override;

    virtual char rysowanie() const = 0;
    virtual std::string nazwa() const = 0;
};
