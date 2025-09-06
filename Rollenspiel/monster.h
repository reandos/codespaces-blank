#ifndef MONSTER_H
#define MONSTER_H

// Datenstruktur für ein Monster
typedef struct
{
  char name[50]; // Monstername
  int health;    // Lebenspunkte
  int attack;    // Angriffskraft
} Monster;

// Monster mit Name, HP und ATK erstellen
void createMonster(Monster *monster, char name[], int health, int attack);

// Monsterwerte anzeigen
void displayMonster(const Monster *monster);

#endif
