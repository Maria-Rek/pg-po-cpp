#pragma once

#include "../Zwierze.h"

class Antylopa : public Zwierze {
public:
    Antylopa(Swiat* swiat, Punkt polozenie);
    virtual ~Antylopa() = default;

    virtual void akcja() override;
    virtual void kolizja(Organizm* inny) override;
    virtual std::string nazwa() const override;
};
