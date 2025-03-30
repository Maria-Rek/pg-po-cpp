#pragma once

#include "Zwierze.h"

class Owca : public Zwierze {
public:
    Owca(Swiat* swiat, Punkt polozenie);
    virtual ~Owca() = default;

    virtual char rysowanie() const override;
    virtual std::string nazwa() const override;
};
