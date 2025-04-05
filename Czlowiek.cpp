#pragma execution_character_set("utf-8")
#include "Czlowiek.h"
#include "Swiat.h"
#include "Organizm.h"
#include <iostream>
#include <cctype>
#include <vector>

Czlowiek::Czlowiek(Swiat* swiat, Punkt polozenie)
    : Zwierze(USE_EMOJI ? u8"🚹" : "@", swiat, polozenie, 5, 4),
    specjalnaAktywna(false), cooldown(0), kierunekRuchu(' '), zamrozWTejTurze(false) {
}

std::string Czlowiek::nazwa() const {
    return "Czlowiek";
}

void Czlowiek::ustawSterowanie() {
    do {
        std::cout << "[Czlowiek] Podaj kierunek ruchu (w/s/a/d): ";
        std::cin >> kierunekRuchu;
        kierunekRuchu = std::tolower(kierunekRuchu);
    } while (kierunekRuchu != 'w' && kierunekRuchu != 's' && kierunekRuchu != 'a' && kierunekRuchu != 'd');

    if (cooldown == 0) {
        char wybor;
        do {
            std::cout << "[Czlowiek] Uzyc umiejetnosci specjalnej (zamrozenie)? (t/n): ";
            std::cin >> wybor;
            wybor = std::tolower(wybor);
        } while (wybor != 't' && wybor != 'n');

        if (wybor == 't') {
            specjalnaAktywna = true;
            zamrozWTejTurze = true;
            cooldown = 5;
            swiat->dodajLog("Czlowiek aktywowal umiejetnosc: zamrozenie sasiadow ❄️");
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
                    swiat->dodajLog(o->nazwa() + " zostal zamrozony i nie wykonal akcji!");
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

    Punkt nowaPozycja(polozenie.x + dx, polozenie.y + dy);
    if (nowaPozycja.x < 0 || nowaPozycja.y < 0 ||
        nowaPozycja.x >= swiat->getSzerokosc() || nowaPozycja.y >= swiat->getWysokosc()) {
        swiat->dodajLog("Czlowiek chcial wyjsc poza mape!");
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
