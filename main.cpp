#include "Swiat.h"
#include "Wilk.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));  // inicjalizacja RNG

    Swiat swiat(10, 10);  // plansza 10x10

    // Dodajemy jednego wilka rêcznie
    Punkt pozycja(4, 4);
    Wilk* wilk = new Wilk(&swiat, pozycja);
    swiat.dodajOrganizm(wilk);

    // Pêtla symulacji – 5 tur
    for (int i = 0; i < 5; ++i) {
        swiat.rysujSwiat();
        swiat.wykonajTure();
        std::cout << "\nNaciœnij Enter, aby przejœæ do nastêpnej tury...";
        std::cin.get();
    }

    return 0;
}
