# Virtual World (C++)

Console-based 2D world simulator where organisms live, move, fight, and reproduce according to individual behavior rules.
Game state is displayed in the console after every turn and can be saved/loaded from a text file.

---

## Core Concepts

- `Swiat` class managing the board and simulation flow
- Abstract `Organism` base class
- Polymorphic `Animal` and `Plant` hierarchies
- Turn order determined by initiative and age
- Collision handling and same-species reproduction
- 8-neighborhood movement model
- Text-based save/load system

---

## Organisms

### Animals
- Wolf
- Sheep
- Fox (avoids stronger organisms)
- Turtle (25% move chance, blocks weaker attacks)
- Antelope (extended movement, 50% escape chance)
- CyberSheep (actively hunts Hogweed)

### Plants
- Grass
- Dandelion (multiple spread attempts)
- Guarana (increases strength)
- Deadly Nightshade (poisonous)
- Hogweed (damages surrounding organisms)

### Human
- Controlled via arrow keys
- Special ability: **Firestorm**
  - 5 turns active
  - 5 turns cooldown

---

## Project Structure

- `Zwierzeta/` – animal classes
- `Rosliny/` – plant classes
- `Organizm.*` – base organism abstraction
- `Swiat.*` – board and simulation management
- `Gra.*` – menu and gameplay logic
- `Zapis/` – save files

---

Project for the *Object-Oriented Programming* course (2024/2025) at Gdańsk University of Technology.
