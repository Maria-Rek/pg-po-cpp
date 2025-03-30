#pragma once
#include "Zwierze.h"

class Owca : public Zwierze {
public:
    Owca(Swiat* swiat, Punkt polozenie);
    virtual ~Owca() = default;

    virtual void akcja() override;
    virtual std::string nazwa() const override;
    virtual char rysowanie() const override;
};
