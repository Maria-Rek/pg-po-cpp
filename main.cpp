#include "Swiat.h"
#include "Wilk.h"
#include "Owca.h"
#include "Lis.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    Swiat swiat(10, 10);

    // Dodajemy organizmy
    swiat.dodajOrganizm(new Wilk(&swiat, Punkt(4, 4)));
    swiat.dodajOrganizm(new Owca(&swiat, Punkt(6, 4)));
    swiat.dodajOrganizm(new Lis(&swiat, Punkt(2, 2)));

    // Symulacja
    for (int i = 0; i < 10; ++i) {
        swiat.rysujSwiat();
        swiat.wykonajTure();
        std::cout << "\nNaciœnij Enter, aby przejœæ do nastêpnej tury...";
        std::cin.get();
    }

    return 0;
}
