#pragma execution_character_set("utf-8")
#include "Czlowiek.h"
#include "Swiat.h"
#include "Organizm.h"
#include <iostream>
#include <cctype>
#include <vector>
#include <conio.h>

Czlowiek::Czlowiek(Swiat* swiat, Punkt polozenie)
    : Zwierze(USE_EMOJI ? u8"🚹" : "@", swiat, polozenie, 5, 4),
    specjalnaAktywna(false), cooldown(0), kierunekRuchu(' '), zamrozWTejTurze(false) {
}

std::string Czlowiek::nazwa() const {
    return "Czlowiek";
}

void Czlowiek::ustawSterowanie() {
    std::cout << "[Człowiek] Wciśnij strzałkę kierunkową (↑ ↓ ← →): " << std::endl;

    int key = _getch();
    if (key == 224) {
        int arrow = _getch();
        switch (arrow) {
        case 72: kierunekRuchu = 'w'; break;
        case 80: kierunekRuchu = 's'; break;
        case 75: kierunekRuchu = 'a'; break;
        case 77: kierunekRuchu = 'd'; break;
        default:
            std::cout << "\n[!] Nieprawidłowy klawisz. Spróbuj ponownie.\n";
            ustawSterowanie();
            return;
        }
    }
    else {
        std::cout << "\n[!] Proszę użyć strzałek.\n";
        ustawSterowanie();
        return;
    }

    if (cooldown == 0) {
        char wybor;
        do {
            std::cout << "[Człowiek] Czy mam użyć umiejętności specjalnej (zamrożenie)? (t/n): ";
            std::cin >> wybor;
            wybor = std::tolower(wybor);
        } while (wybor != 't' && wybor != 'n');

        if (wybor == 't') {
            specjalnaAktywna = true;
            zamrozWTejTurze = true;
            cooldown = 5;
            swiat->dodajLog("Człowiek aktywował umiejętność: zamrożenie sąsiadów ❄️");
        }
    }
}

void Czlowiek::akcja() {
    ustawSterowanie();

    if (specjalnaAktywna && zamrozWTejTurze) {
        std::vector<Punkt> sasiednie = swiat->getSasiedniePola(polozenie);
        for (Organizm* o : swiat->getOrganizmy()) {
            for (const Punkt& p : sasiednie) {
                if (o->getPolozenie() == p) {
                    o->zwiekszWiek();
                    swiat->dodajLog(o->nazwa() + " został zamrożony i nie wykonał akcji!");
                }
            }
        }
        zamrozWTejTurze = false;
        specjalnaAktywna = false;
    }

    int dx = 0, dy = 0;
    switch (kierunekRuchu) {
    case 'w': dy = -1; break;
    case 's': dy = 1; break;
    case 'a': dx = -1; break;
    case 'd': dx = 1; break;
    }

    Punkt nowaPozycja(polozenie.getX() + dx, polozenie.getY() + dy);
    if (nowaPozycja.getX() < 0 || nowaPozycja.getY() < 0 ||
        nowaPozycja.getX() >= swiat->getSzerokosc() || nowaPozycja.getY() >= swiat->getWysokosc()) {
        swiat->dodajLog("Człowiek chciał wyjść poza mapę!");
    }
    else {
        Organizm* cel = swiat->getOrganizmNa(nowaPozycja);
        if (cel)
            kolizja(cel);
        else
            polozenie = nowaPozycja;
    }

    if (cooldown > 0)
        cooldown--;

    zwiekszWiek();
}
