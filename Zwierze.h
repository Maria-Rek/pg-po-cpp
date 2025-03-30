#pragma once

#include "Organizm.h"

class Zwierze : public Organizm {
public:
    Zwierze(Swiat* swiat, Punkt polozenie, int sila, int inicjatywa);
    virtual ~Zwierze() = default;

    virtual void akcja() override;
    virtual void kolizja(Organizm* inny) override;
};
