#include "Swiat.h"
#include "Wilk.h"
#include "Owca.h"
#include "Lis.h"
#include "Zolw.h"
#include "Antylopa.h"
#include "Trawa.h"
#include "Guarana.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    Swiat swiat(10, 10);  // Plansza 10x10

    // Dodajemy organizmy
    swiat.dodajOrganizm(new Wilk(&swiat, Punkt(4, 4)));
    swiat.dodajOrganizm(new Owca(&swiat, Punkt(6, 4)));
    swiat.dodajOrganizm(new Lis(&swiat, Punkt(2, 2)));
    swiat.dodajOrganizm(new Zolw(&swiat, Punkt(3, 6)));
    swiat.dodajOrganizm(new Antylopa(&swiat, Punkt(7, 7)));
    swiat.dodajOrganizm(new Trawa(&swiat, Punkt(5, 1)));
    swiat.dodajOrganizm(new Guarana(&swiat, Punkt(4, 5)));  // Guarana do testów

    // Symulacja: 10 tur
    for (int i = 0; i < 10; ++i) {
        swiat.rysujSwiat();
        swiat.wykonajTure();
        std::cout << "\nNaciśnij Enter, aby przejść do następnej tury...";
        std::cin.get();
    }

    return 0;
}
