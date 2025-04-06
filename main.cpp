#pragma execution_character_set("utf-8")
#include "Swiat.h"
#include "Zwierzeta/Wilk.h"
#include "Zwierzeta/Owca.h"
#include "Zwierzeta/Lis.h"
#include "Zwierzeta/Zolw.h"
#include "Zwierzeta/Antylopa.h"
#include "Rosliny/Trawa.h"
#include "Rosliny/Guarana.h"
#include "Rosliny/Mlecz.h"
#include "Rosliny/WilczeJagody.h"
#include "Rosliny/BarszczSosnowskiego.h"
#include "Zwierzeta/CyberOwca.h"
#include "Czlowiek.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    system("chcp 65001");

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    Swiat swiat(10, 10);  // Plansza 10x10 (Człowiek na środku)

    // Dodajemy organizmy testowe
    swiat.dodajOrganizm(new Wilk(&swiat, Punkt(4, 4)));
    swiat.dodajOrganizm(new Owca(&swiat, Punkt(6, 4)));
    swiat.dodajOrganizm(new Lis(&swiat, Punkt(2, 2)));
    swiat.dodajOrganizm(new Zolw(&swiat, Punkt(3, 6)));
    swiat.dodajOrganizm(new Antylopa(&swiat, Punkt(7, 7)));
    swiat.dodajOrganizm(new Trawa(&swiat, Punkt(5, 1)));
    swiat.dodajOrganizm(new Guarana(&swiat, Punkt(4, 5)));
    swiat.dodajOrganizm(new Mlecz(&swiat, Punkt(5, 5)));
    swiat.dodajOrganizm(new WilczeJagody(&swiat, Punkt(6, 6)));
    swiat.dodajOrganizm(new BarszczSosnowskiego(&swiat, Punkt(2, 4)));
    swiat.dodajOrganizm(new CyberOwca(&swiat, Punkt(1, 1)));
    swiat.dodajOrganizm(new Czlowiek(&swiat, Punkt(swiat.getSzerokosc() / 2, swiat.getWysokosc() / 2)));


    // Symulacja 10 tur
    for (int i = 0; i < 10; ++i) {
        swiat.rysujSwiat();
        swiat.wykonajTure();
        std::cout << "\nNaciśnij Enter, aby przejść do następnej tury...";
        std::cin.get();
    }

    return 0;
}
