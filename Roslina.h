#pragma once

#include "Organizm.h"

class Roslina : public Organizm {
public:
    Roslina(const std::string& ikona, Swiat* swiat, Punkt polozenie, int sila);

    virtual void akcja() override;
    virtual void kolizja(Organizm* inny) override;
    virtual std::string nazwa() const = 0;
};
