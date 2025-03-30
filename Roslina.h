#pragma once

#include "Organizm.h"

class Roslina : public Organizm {
public:
    Roslina(Swiat* swiat, Punkt polozenie, int sila);
    virtual ~Roslina() = default;

    virtual void akcja() override;
    virtual void kolizja(Organizm* inny) override;
};
