#include <stdio.h>
#include <string.h>
#include "monster.h"

// Erstellt ein Monster mit gegebenem Namen, Lebenspunkten und Angriffswert
void createMonster(Monster *monster, char name[], int health, int attack)
{
  strcpy(monster->name, name);
  monster->health = health;
  monster->attack = attack;
}

// Gibt die Werte eines Monsters aus
void displayMonster(const Monster *monster)
{
  printf("----Monster-----\n");
  printf("Name: %s\n", monster->name);
  printf("Gesundheit: %d\n", monster->health);
  printf("Angriffskraft: %d\n", monster->attack);
}
