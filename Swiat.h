#pragma once

#include <vector>
#include <string>
#include "Organizm.h"
#include "Punkt.h"

class Swiat {
private:
    int szerokosc;
    int wysokosc;
    int tura;
    std::vector<Organizm*> organizmy;
    std::vector<std::string> logi;

    void sortujOrganizmy();  // wed³ug inicjatywy i wieku

public:
    Swiat(int szerokosc = 20, int wysokosc = 20);
    ~Swiat();

    void wykonajTure();
    void rysujSwiat();

    Organizm* getOrganizmNa(const Punkt& p) const;
    std::vector<Punkt> getSasiedniePola(const Punkt& p) const;
    std::vector<Punkt> getWolnePolaObok(const Punkt& p) const;

    void stworzOrganizm(const std::type_info& typ, const Punkt& p);
    void dodajOrganizm(Organizm* org);
    void usunOrganizm(Organizm* org);

    void dodajLog(const std::string& tekst);

    int getSzerokosc() const;
    int getWysokosc() const;
};
