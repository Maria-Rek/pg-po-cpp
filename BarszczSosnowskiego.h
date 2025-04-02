#pragma once

#include "Roslina.h"

class BarszczSosnowskiego : public Roslina {
public:
    BarszczSosnowskiego(Swiat* swiat, Punkt polozenie);
    virtual ~BarszczSosnowskiego() = default;

    virtual void akcja() override;
    virtual void kolizja(Organizm* inny) override;
    virtual std::string nazwa() const override;
};
