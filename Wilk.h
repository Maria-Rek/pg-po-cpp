#pragma once

#include "Zwierze.h"

class Wilk : public Zwierze {
public:
    Wilk(Swiat* swiat, Punkt polozenie);
    virtual ~Wilk() = default;

    virtual std::string nazwa() const override;
};
