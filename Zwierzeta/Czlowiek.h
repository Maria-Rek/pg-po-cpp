#pragma once

#include "../Zwierze.h"

class Czlowiek : public Zwierze {
private:
    bool specjalnaAktywna;
    int cooldown;
    char kierunekRuchu;
    bool zamrozWTejTurze;

public:
    Czlowiek(Swiat* swiat, Punkt polozenie);
    virtual ~Czlowiek() = default;

    virtual void akcja() override;
    virtual std::string nazwa() const override;

    void ustawSterowanie();
};
