#pragma once
#include "Swiat.h"

class Gra {
public:
    Gra();
    void menu();

private:
    Swiat swiat;
    bool graTrwa;

    void start();
    void pokazOpcje();
    void zapiszDialog();
    void wczytajDialog();
    void dodajOrganizmyStartowe();
};
