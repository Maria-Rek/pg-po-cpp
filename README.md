# Programowanie Obiektowe  
Object Oriented Programming Project C++  
PO – Politechnika Gdańska, Informatyka  


## Opis projektu
Projekt to konsolowy symulator świata 2D, w którym różne organizmy żyją, poruszają się, walczą ze sobą albo się rozmnażają.
Każdy organizm działa na własnych zasadach – jedne poruszają się losowo, inne podejmują decyzje zależnie od otoczenia.

Głównym elementem gry jest Człowiek, którym steruje gracz za pomocą strzałek.
Dodatkowo posiada specjalną umiejętność – **całopalenie**, która pozwala mu spalić wszystko dookoła (cooldown 5 tur).

W grze pojawia się też specjalny organizm – **CyberOwca**, który ma za zadanie odnaleźć i zniszczyć niebezpieczną roślinę: **Barszcz Sosnowskiego**.

Gra działa turowo – organizmy wykonują swoje ruchy w kolejności zależnej od inicjatywy i wieku.
Każda tura kończy się wizualizacją planszy oraz wypisaniem wydarzeń w konsoli.
Gracz może zapisać lub wczytać stan gry do pliku tekstowego.


## Wymagania i funkcjonalności  
✅ Implementacja klasy `Swiat` oraz abstrakcyjnej klasy `Organizm`  
✅ Klasy pochodne `Zwierze`, `Roslina` z polimorfizmem i hermetyzacją  
✅ Implementacja 6 zwierząt:
- Wilk  
- Owca  
- Lis (unika silniejszych)  
- Żółw (25% szansy na ruch, odpiera ataki <5)  
- Antylopa (zasięg 2, 50% ucieczki)  
- CyberOwca (śledzi Barszcz Sosnowskiego)

✅ Implementacja 5 roślin:
- Trawa  
- Mlecz (3 próby rozsiania)  
- Guarana (zwiększa siłę o +3)  
- Wilcze Jagody (trujące)  
- Barszcz Sosnowskiego (zabija wszystko wokół oprócz CyberOwcy)

✅ Człowiek:  
- Porusza się strzałkami  
- Umiejętność specjalna: **całopalenie** (spala wszystkie organizmy wokół przez 1 turę, cooldown 5 tur)

✅ Obsługa kolizji i rozmnażania organizmów tego samego gatunku  
✅ Priorytet wykonania tury wg inicjatywy i wieku  
✅ Ośmiosąsiedztwo przy poruszaniu i rozmnażaniu  
✅ Symboliczna reprezentacja organizmów w ASCII/emoji  
✅ System zapisu i wczytywania stanu gry do pliku tekstowego  

## Struktura katalogów  
- `Zwierzeta/` – pliki klas zwierząt  
- `Rosliny/` – pliki klas roślin  
- `Gra.*` – obsługa menu i rozgrywki  
- `Swiat.*` – zarządzanie planszą i logiką gry  
- `Organizm.*` – bazowa klasa organizmu  
- `Zapis/` – domyślny folder zapisu plików stanu gry  
