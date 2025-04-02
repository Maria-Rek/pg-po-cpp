#pragma once

#include "Zwierze.h"

class Lis : public Zwierze {
public:
    Lis(Swiat* swiat, Punkt polozenie);
    virtual ~Lis() = default;

    virtual void akcja() override;
    virtual std::string nazwa() const override;
};
