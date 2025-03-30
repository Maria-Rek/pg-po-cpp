#pragma once

#include "Zwierze.h"

class Zolw : public Zwierze {
private:
    int ostatniRuch;  // tura, w której ostatni raz siê poruszy³

public:
    Zolw(Swiat* swiat, Punkt polozenie);
    virtual ~Zolw() = default;

    virtual void akcja() override;
    virtual void kolizja(Organizm* inny) override;

    virtual char rysowanie() const override;
    virtual std::string nazwa() const override;
};
