#pragma once

#include "Zwierze.h"
#include <ostream>

class Czlowiek : public Zwierze {
private:
    bool specjalnaAktywna;
    int cooldown;
    char kierunekRuchu;

public:
    Czlowiek(Swiat* swiat, Punkt polozenie);
    virtual ~Czlowiek() = default;

    virtual void akcja() override;
    virtual std::string nazwa() const override;
    virtual void zapisz(std::ostream& out) const override;

    void ustawSterowanie();

    int getCooldown() const;
    void setCooldown(int cooldown);
};
