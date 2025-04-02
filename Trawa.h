#pragma once

#include "Roslina.h"

class Trawa : public Roslina {
public:
    Trawa(Swiat* swiat, Punkt polozenie);
    virtual ~Trawa() = default;

    virtual std::string nazwa() const override;
};
