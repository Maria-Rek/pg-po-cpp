#pragma once

#include "Zwierze.h"

class Zolw : public Zwierze {
private:
    int ostatniRuch;

public:
    Zolw(Swiat* swiat, Punkt polozenie);
    virtual ~Zolw() = default;

    virtual void akcja() override;
    virtual char rysowanie() const override;
    virtual std::string nazwa() const override;

    virtual bool czyOdbilAtak(Organizm* atakujacy) const override;
};
