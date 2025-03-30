#pragma once

#include "Roslina.h"

class Guarana : public Roslina {
public:
    Guarana(Swiat* swiat, Punkt polozenie);
    virtual ~Guarana() = default;

    virtual void kolizja(Organizm* inny) override;
    virtual char rysowanie() const override;
    virtual std::string nazwa() const override;
};
