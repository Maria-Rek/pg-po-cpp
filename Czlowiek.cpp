#pragma execution_character_set("utf-8")
#include "Czlowiek.h"
#include "Swiat.h"
#include "Organizm.h"
#include <iostream>
#include <cctype>
#include <vector>
#include <conio.h>
#include <ostream>

Czlowiek::Czlowiek(Swiat* swiat, Punkt polozenie)
    : Zwierze(USE_EMOJI ? u8"🚹" : "@", swiat, polozenie, 5, 4),
    specjalnaAktywna(false), turyAktywne(0), turyCooldown(0), kierunekRuchu(' ') {
}

std::string Czlowiek::nazwa() const {
    return "Czlowiek";
}

int Czlowiek::getCooldown() const {
    return turyCooldown;
}

void Czlowiek::setCooldown(int aktywne, int cooldown) {
    this->turyAktywne = aktywne;
    this->turyCooldown = cooldown;
    this->specjalnaAktywna = aktywne > 0;
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

    if (turyAktywne == 0 && turyCooldown == 0) {
        std::cout << "[Człowiek] Czy chcesz użyć umiejętności specjalnej? (t/n): ";
        char wybor = '\0';
        while (true) {
            wybor = std::tolower(_getch());
            if (wybor == 't' || wybor == 'n')
                break;
        }

        std::cout << wybor << std::endl;

        if (wybor == 't') {
            specjalnaAktywna = true;
            turyAktywne = 5;
            turyCooldown = 0; // zacznie się po tych 5
            swiat->dodajLog("Człowiek użył umiejętności: całopalenie 🔥");
        }
    }
}

void Czlowiek::akcja() {
    ustawSterowanie();

    if (specjalnaAktywna) {
        std::vector<Punkt> sasiednie = swiat->getSasiedniePola(polozenie);
        for (const Punkt& p : sasiednie) {
            Organizm* o = swiat->getOrganizmNa(p);
            if (o && o != this) {
                swiat->dodajLog(o->nazwa() + " został spalony przez Człowieka 🔥");
                swiat->usunOrganizm(o);
            }
        }

        turyAktywne--;
        if (turyAktywne == 0) {
            specjalnaAktywna = false;
            turyCooldown = 5;
            swiat->dodajLog("Umiejętność Człowieka wygasła. Rozpoczęto 5-tur cooldown.");
        }
    }
    else if (turyCooldown > 0) {
        turyCooldown--;
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

    zwiekszWiek();
}

void Czlowiek::zapisz(std::ostream& out) const {
    out << nazwa() << " "
        << polozenie.getX() << " "
        << polozenie.getY() << " "
        << sila << " "
        << inicjatywa << " "
        << wiek << " "
        << turyAktywne << " "
        << turyCooldown << std::endl;
}
