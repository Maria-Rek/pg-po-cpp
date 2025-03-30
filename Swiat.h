#pragma once

#include <vector>
#include <string>
#include <typeinfo>  // potrzebne do u¿ycia typeid()

#include "Organizm.h"
#include "Punkt.h"

using std::vector;
using std::string;
using std::type_info;

class Swiat {
private:
    int szerokosc;
    int wysokosc;
    int tura;
    vector<Organizm*> organizmy;
    vector<string> logi;

    void sortujOrganizmy();  // wg inicjatywy i wieku

public:
    Swiat(int szerokosc = 20, int wysokosc = 20);
    ~Swiat();

    void wykonajTure();
    void rysujSwiat();

    Organizm* getOrganizmNa(const Punkt& p) const;
    vector<Punkt> getSasiedniePola(const Punkt& p) const;
    vector<Punkt> getWolnePolaObok(const Punkt& p) const;

    void stworzOrganizm(const type_info& typ, const Punkt& p);
    void dodajOrganizm(Organizm* org);
    void usunOrganizm(Organizm* org);

    void dodajLog(const string& tekst);

    int getSzerokosc() const;
    int getWysokosc() const;
    int getTura() const; 
};
