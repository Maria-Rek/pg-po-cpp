#pragma once

#include "Roslina.h"

class WilczeJagody : public Roslina {
public:
    WilczeJagody(Swiat* swiat, Punkt polozenie);
    virtual ~WilczeJagody() = default;

    virtual void kolizja(Organizm* inny) override;
    virtual char rysowanie() const override;
    virtual std::string nazwa() const override;
};
