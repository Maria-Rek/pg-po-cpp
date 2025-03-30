#pragma once
#include "Roslina.h"

class Mlecz : public Roslina {
public:
    Mlecz(Swiat* swiat, Punkt polozenie);
    virtual ~Mlecz() = default;

    virtual void akcja() override;
    virtual char rysowanie() const override;
    virtual std::string nazwa() const override;
};
