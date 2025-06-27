# Object-Oriented Programming (C++)

## Project Overview

Console-based 2D world simulator where various organisms live, move, fight, or reproduce according to individual rules.

The game is **turn-based**, with organisms acting based on initiative and age, displaying the board and event log in the console after each turn.  
Game state can be saved/loaded from a text file.

---

## Features

- `Swiat` class and abstract `Organism` class
- Derived `Animal` and `Plant` classes with polymorphism and encapsulation
- 6 animals:
  - Wolf
  - Sheep
  - Fox (avoids stronger organisms)
  - Turtle (25% move chance, blocks attacks <5)
  - Antelope (range 2, 50% escape chance)
  - CyberSheep (hunts Hogweed)
- 5 plants:
  - Grass
  - Dandelion (3 spread attempts)
  - Guarana (+3 strength)
  - Deadly Nightshade (poisonous)
  - Hogweed (kills surrounding organisms except CyberSheep)
- **Human**:
  - Controlled with ←↑↓→
  - Special ability “Firestorm”:
    - 5 turns active
    - 5 turns cooldown
    - Can be activated only when not active or on cooldown
- Collision handling and reproduction of same-species organisms
- Turn priority based on initiative and age
- 8-neighborhood movement and reproduction
- ASCII/emoji symbolic representation of organisms
- Save/load system using text files

---

## Directory Structure

- `Zwierzeta/` – animal classes
- `Rosliny/` – plant classes
- `Gra.*` – menu and gameplay
- `Swiat.*` – board management and game logic
- `Organizm.*` – base organism class
- `Zapis/` – save files

---

Project for the *Object-Oriented Programming* course (2024/2025) at Gdańsk University of Technology.
