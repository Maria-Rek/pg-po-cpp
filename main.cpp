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
#include <string>

int main() {
    system("chcp 65001");
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    Swiat swiat;
    int wybor = 0;

    while (true) {
        std::cout << "\n\t=============================\n";
        std::cout << "\t\t   MENU \n";
        std::cout << "\t=============================\n\n";
        std::cout << "\t1 – Nowa gra\n";
        std::cout << "\t2 – Wczytaj grę\n";
        std::cout << "\t3 – Wyjście\n\n";
        std::cout << "\t";
        std::cin >> wybor;
        std::cin.ignore();

        if (wybor == 1) {
            swiat = Swiat(10, 10);

            // Rośliny
            swiat.dodajOrganizm(new Trawa(&swiat, Punkt(1, 1)));
            swiat.dodajOrganizm(new Trawa(&swiat, Punkt(8, 2)));
            swiat.dodajOrganizm(new Mlecz(&swiat, Punkt(5, 5)));
            swiat.dodajOrganizm(new Guarana(&swiat, Punkt(3, 4)));
            swiat.dodajOrganizm(new WilczeJagody(&swiat, Punkt(2, 8)));
            swiat.dodajOrganizm(new BarszczSosnowskiego(&swiat, Punkt(6, 2)));

            // Zwierzęta
            swiat.dodajOrganizm(new Wilk(&swiat, Punkt(4, 4)));
            swiat.dodajOrganizm(new Wilk(&swiat, Punkt(7, 3)));
            swiat.dodajOrganizm(new Owca(&swiat, Punkt(6, 4)));
            swiat.dodajOrganizm(new Owca(&swiat, Punkt(1, 5)));
            swiat.dodajOrganizm(new Lis(&swiat, Punkt(2, 2)));
            swiat.dodajOrganizm(new Zolw(&swiat, Punkt(3, 6)));
            swiat.dodajOrganizm(new Antylopa(&swiat, Punkt(7, 7)));
            swiat.dodajOrganizm(new Antylopa(&swiat, Punkt(6, 8)));
            swiat.dodajOrganizm(new CyberOwca(&swiat, Punkt(0, 9)));

            swiat.dodajOrganizm(new Czlowiek(&swiat, Punkt(swiat.getSzerokosc() / 2, swiat.getWysokosc() / 2)));
            break;
        }
        else if (wybor == 2) {
            std::string nazwaPliku;
            std::cout << "\tPodaj nazwę pliku do wczytania: ";
            std::getline(std::cin, nazwaPliku);
            swiat = Swiat(10, 10);
            swiat.wczytajStanZPliku("Zapis/" + nazwaPliku);
            break;
        }
        else if (wybor == 3) {
            std::cout << "\tZamykam program...\n";
            return 0;
        }
    }

    while (true) {
        swiat.rysujSwiat();

        std::cout << "\n[ENTER] – następna tura | [z] – zapisz | [w] – wczytaj | [q] – wyjdź\n";
        std::string akcja;
        std::getline(std::cin, akcja);

        if (akcja.empty()) {
            swiat.wykonajTure();
        }
        else if (akcja == "z" || akcja == "Z") {
            std::string nazwaPliku;
            std::cout << "Podaj nazwę pliku do zapisu: ";
            std::getline(std::cin, nazwaPliku);
            swiat.zapiszStanDoPliku("Zapis/" + nazwaPliku);
        }
        else if (akcja == "w" || akcja == "W") {
            std::string nazwaPliku;
            std::cout << "Podaj nazwę pliku do wczytania: ";
            std::getline(std::cin, nazwaPliku);
            swiat.wczytajStanZPliku("Zapis/" + nazwaPliku);
        }
        else if (akcja == "q" || akcja == "Q") {
            std::cout << "Zamykam grę...\n";
            break;
        }
    }

    return 0;
}
