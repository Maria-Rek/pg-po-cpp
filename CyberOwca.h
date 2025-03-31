#pragma once

#include "Zwierze.h"

class CyberOwca : public Zwierze {
public:
    CyberOwca(Swiat* swiat, Punkt polozenie);
    virtual ~CyberOwca() = default;

    virtual void akcja() override;
    virtual char rysowanie() const override;
    virtual std::string nazwa() const override;

private:
    Punkt znajdzNajblizszyBarszcz() const;
    int dystans(const Punkt& a, const Punkt& b) const;
};

