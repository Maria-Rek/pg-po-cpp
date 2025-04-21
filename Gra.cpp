#pragma execution_character_set("utf-8")
#include "Gra.h"
#include "Zwierzeta/Wilk.h"
#include "Zwierzeta/Owca.h"
#include "Zwierzeta/Lis.h"
#include "Zwierzeta/Zolw.h"
#include "Zwierzeta/Antylopa.h"
#include "Zwierzeta/CyberOwca.h"
#include "Rosliny/Trawa.h"
#include "Rosliny/Guarana.h"
#include "Rosliny/Mlecz.h"
#include "Rosliny/WilczeJagody.h"
#include "Rosliny/BarszczSosnowskiego.h"
#include "Czlowiek.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <limits>

Gra::Gra() {
    graTrwa = true;
    maksTury = -1;  // brak limitu
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Gra::menu() {
    std::string wybor;

    std::cout << "\nAutor: Maria Rek (203174)\n";
    std::cout << "============================\n";
    std::cout << "\t   MENU \n";
    std::cout << "=============================\n\n";
    std::cout << "1 – Nowa gra\n";
    std::cout << "2 – Wczytaj grę\n";
    std::cout << "3 – Wyjście\n\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, wybor);

        if (wybor == "1") {
            swiat = Swiat(10, 10);
            dodajOrganizmyStartowe();

            std::cout << "Podaj liczbę tur do wykonania: ";
            while (!(std::cin >> maksTury) || maksTury <= 0) {
                std::cout << "❌ Niepoprawna liczba. Podaj liczbę > 0: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cin.ignore();
            break;
        }
        else if (wybor == "2") {
            wczytajDialog();
            break;
        }
        else if (wybor == "3") {
            graTrwa = false;
            return;
        }
        else {
            std::cout << "\033[F\033[K";
        }
    }

    start();
}

void Gra::start() {
    while (graTrwa) {
        swiat.rysujSwiat();
        pokazOpcje();

        while (true) {
            std::string akcja;
            std::getline(std::cin, akcja);

            if (akcja.empty()) {
                swiat.wykonajTure();
                break;
            }
            else if (akcja == "z" || akcja == "Z") {
                zapiszDialog();
                break;
            }
            else if (akcja == "w" || akcja == "W") {
                wczytajDialog();
                break;
            }
            else if (akcja == "q" || akcja == "Q") {
                std::cout << "Gra zakończona\n";
                graTrwa = false;
                return;
            }
            else {
                std::cout << "\033[F\033[K";
            }
        }

        if (maksTury > 0 && swiat.getTura() > maksTury) {
            std::cout << "\n[!] Osiągnięto " << maksTury << " tur. Gra zakończona.\n";
            graTrwa = false;
            return;
        }
    }
}

void Gra::pokazOpcje() {
    std::cout << "\n[ENTER] – Następna tura\n";
    std::cout << "[Z] – zapisz\n";
    std::cout << "[W] – wczytaj\n";
    std::cout << "[Q] – wyjdź\n";
}

void Gra::zapiszDialog() {
    std::string nazwa;
    std::cout << "Podaj nazwę pliku do zapisu: ";
    std::getline(std::cin, nazwa);
    swiat.zapiszStanDoPliku("Zapis/" + nazwa);
}

void Gra::wczytajDialog() {
    std::string nazwa;

    while (true) {
        std::cout << "Podaj nazwę pliku do wczytania: ";
        std::getline(std::cin, nazwa);

        std::ifstream test("Zapis/" + nazwa);
        if (!test.good()) {
            std::cout << "❌ Plik \"Zapis/" << nazwa << "\" nie istnieje. Spróbuj ponownie.\n";
            continue;
        }

        swiat = Swiat(10, 10);
        swiat.wczytajStanZPliku("Zapis/" + nazwa);

        int dodatkoweTury;
        std::cout << "Podaj liczbę tur do wykonania od momentu wczytania: ";
        while (!(std::cin >> dodatkoweTury) || dodatkoweTury <= 0) {
            std::cout << "❌ Niepoprawna liczba. Podaj liczbę > 0: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore();

        maksTury = swiat.getTura() + dodatkoweTury;
        break;
    }
}

void Gra::dodajOrganizmyStartowe() {
    swiat.dodajOrganizm(new Trawa(&swiat, Punkt(1, 1)));
    swiat.dodajOrganizm(new Trawa(&swiat, Punkt(8, 2)));
    swiat.dodajOrganizm(new Mlecz(&swiat, Punkt(5, 5)));
    swiat.dodajOrganizm(new Guarana(&swiat, Punkt(3, 4)));
    swiat.dodajOrganizm(new WilczeJagody(&swiat, Punkt(2, 8)));
    swiat.dodajOrganizm(new BarszczSosnowskiego(&swiat, Punkt(6, 2)));

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
}